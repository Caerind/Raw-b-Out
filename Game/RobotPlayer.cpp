#include "RobotPlayer.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"

#include "Fx.hpp"

RobotPlayer::RobotPlayer(oe::EntityManager& manager)
	: Robot(manager, Robot::Killer)
	, mAction(*this)
	, mWheel(*this)
	, mBody(*this)
	, mEyes(*this)
	, mWeaponSprite(*this)
{
	mRespawning = false;

	mBattery = GameSingleton::BatteryPlayer;
	mBatteryMax = GameSingleton::BatteryPlayer;
	mSpeed = GameSingleton::SpeedPlayer;

	mBatteryBonus = 0.0f;
	mSpeedBonus = 0.0f;
	mStrengthBonus = 0;

	mCollision.setSize(oe::Vector2(40, 40));

	oe::ActionId shootAction = mAction.addAction("shoot");
	mAction.setInput(shootAction, &GameSingleton::shootInput);
	mAction.addOutput(shootAction, [this]() { shoot(); });

	mWheel.setTexture(GameSingleton::killerTexture);
	mWheel.setTextureRect(sf::IntRect(64, 0, 21, 21));
	mWheel.setPosition(-11.f, -10.f);
	mWheel.setPositionZ(-1.0f);

	mBody.setTexture(GameSingleton::killerTexture);
	mBody.setPosition(-32.0f, -58.0f);
	mBody.setPositionZ(1.0f);

	mEyes.setTexture(GameSingleton::killerTexture);
	mEyes.setPositionZ(2.0f);

	mWeaponSprite.setTexture(GameSingleton::weaponsTexture);
	mWeaponSprite.setPositionZ(3.0f);

	setLookAt(1000);

	mLevel = 1;
	mExperience = 0;
	mPoints = 0;
}

void RobotPlayer::setLevel(U32 level)
{
	mLevel = level;
}

U32 RobotPlayer::getLevel() const
{
	return mLevel;
}

void RobotPlayer::gainLevel()
{
	getManager().createEntity<Fx>(Fx::Level, getPosition());
	getApplication().getAudio().playSound(GameSingleton::levelSound);
	mLevel++;
	for (U32 i = 0; i < GameSingleton::PointsGain; i++)
	{
		addPoint();
	}
}

void RobotPlayer::setExperience(U32 experience)
{
	mExperience = experience;
}

U32 RobotPlayer::getExperience() const
{
	return mExperience;
}

U32 RobotPlayer::getExperienceMax() const
{
	return GameSingleton::ExperienceC + mLevel * (GameSingleton::ExperienceB + mLevel);
}

void RobotPlayer::addExperience(U32 experience)
{
	mExperience += experience;
	U32 max = getExperienceMax();
	while (mExperience > max)
	{
		gainLevel();
		mExperience -= max;
		max = getExperienceMax();
	}
}

void RobotPlayer::setPoints(U32 points)
{
	mPoints = points;
}

U32 RobotPlayer::getPoints() const
{
	return mPoints;
}

void RobotPlayer::addPoint()
{
	mPoints++;
}

void RobotPlayer::spendPoint()
{
	if (mPoints > 0)
	{
		mPoints--;
	}
}

bool RobotPlayer::hasPoints() const
{
	return mPoints > 0;
}

void RobotPlayer::increaseBattery()
{
	if (hasPoints())
	{
		mBatteryBonus += GameSingleton::BatteryGain;
		mBattery += GameSingleton::BatteryGain;
		spendPoint();
	}
}

void RobotPlayer::increaseSpeed()
{
	if (hasPoints())
	{
		mSpeedBonus += GameSingleton::SpeedGain;
		spendPoint();
	}
}

void RobotPlayer::increaseStrength()
{
	if (hasPoints())
	{
		mStrengthBonus += GameSingleton::StrengthGain;
		spendPoint();
	}
}

void RobotPlayer::setBatteryBonus(F32 bonus)
{
	mBatteryBonus = bonus;
}

void RobotPlayer::setSpeedBonus(F32 bonus)
{
	mSpeedBonus = bonus;
}

void RobotPlayer::setStrengthBonus(U32 bonus)
{
	mStrengthBonus = bonus;
}

F32 RobotPlayer::getBatteryBonus() const
{
	return mBatteryBonus;
}

F32 RobotPlayer::getSpeedBonus() const
{
	return mSpeedBonus;
}

U32 RobotPlayer::getStrengthBonus() const
{
	return mStrengthBonus;
}

void RobotPlayer::update(oe::Time dt)
{
	//oe::DebugDraw::drawPoint(getPosition(), oe::Color::Red, 5.f);
	//oe::DebugDraw::drawRect(getCollision());

	oe::Vector2 mvt;
	bool moved = determineMovement(mvt);
	if (moved)
	{
		moved = tryMove(dt, mvt);
		if (moved)
		{
			consumeBattery(dt.asSeconds() * 1.f);
			updateView();
		}
	}

	mWeaponCooldown += dt;

	if (mBattery <= 0.0f)
	{
		mRespawning = true;
		setPosition(GameSingleton::map->getRespawnPoint());
		updateView();
		charge();
	}

	updateLook();
}

void RobotPlayer::shoot()
{
	if (Robot::shoot(getApplication().getWindow().getCursorPositionView(getWorld().getRenderSystem().getView())) && mWeapon.getId() != 0)
	{
		consumeBattery(1.0f);
	}
}

void RobotPlayer::updateView()
{
	getWorld().getRenderSystem().getView().setCenter(getPosition());
}

void RobotPlayer::updateLook()
{
	setLookAt(getApplication().getWindow().getCursorPositionView(getWorld().getRenderSystem().getView()).x);
}

void RobotPlayer::setLookAt(F32 x)
{
	if (x - getPosition().x > 0.0f)
	{
		mBody.setTextureRect(sf::IntRect(0, 0, 64, 64));

		mEyes.setPosition(-2, -40);
		mEyes.setTextureRect(sf::IntRect(64, 21, 14, 7));

		mWeaponSprite.setPosition(-20, -40);
		mWeaponSprite.setTextureRect(GameSingleton::getTextureRectFromWeapon(mWeapon.getId()));
		mStrikePos.set(mWeaponSprite.getGlobalPosition().x + 56, mWeaponSprite.getGlobalPosition().y + 32);
	}
	else
	{
		mBody.setTextureRect(sf::IntRect(0, 64, 64, 64));

		mEyes.setPosition(-12, -40);
		mEyes.setTextureRect(sf::IntRect(64, 21, 14, 7));

		mWeaponSprite.setPosition(-40, -40);
		sf::IntRect r = GameSingleton::getTextureRectFromWeapon(mWeapon.getId());
		r.top += 192;
		mWeaponSprite.setTextureRect(r);
		mStrikePos.set(mWeaponSprite.getGlobalPosition().x, mWeaponSprite.getGlobalPosition().y + 32);
	}
}

void RobotPlayer::addWeapon(WeaponId id)
{
	if (!hasWeapon(id))
	{
		mWeapons.push_back(id);
	}
}

bool RobotPlayer::hasWeapon(WeaponId id) const
{
	for (U32 i = 0; i < mWeapons.size(); i++)
	{
		if ((WeaponId)mWeapons[i] == id)
		{
			return true;
		}
	}
	return false;
}

std::vector<WeaponId>& RobotPlayer::getWeapons()
{
	return mWeapons;
}

void RobotPlayer::charge()
{
	setBattery(getBatteryMaxWithBonus());
}

bool RobotPlayer::isCharged() const
{
	return mBattery + 2.0f >= mBatteryMax;
}

void RobotPlayer::setColor(const oe::Color& color)
{
	mBody.setColor(color);
}

oe::Color RobotPlayer::getColor() const
{
	return mBody.getColor();
}

void RobotPlayer::setRespawning(bool respawning)
{
	mRespawning = respawning;
}

bool RobotPlayer::isRespawning() const
{
	return mRespawning;
}

bool RobotPlayer::determineMovement(oe::Vector2& mvt)
{
	bool moved = false;

	bool left = (sf::Keyboard::isKeyPressed(GameSingleton::left.getKey()) || sf::Keyboard::isKeyPressed(GameSingleton::left2.getKey()));
	bool right = sf::Keyboard::isKeyPressed(GameSingleton::right.getKey());
	bool up = (sf::Keyboard::isKeyPressed(GameSingleton::up.getKey()) || sf::Keyboard::isKeyPressed(GameSingleton::up2.getKey()));
	bool down = sf::Keyboard::isKeyPressed(GameSingleton::down.getKey());

	if (left && !right)
	{
		mvt.x--;
		moved = true;
	}
	else if (right && !left)
	{
		mvt.x++;
		moved = true;
	}

	if (up && !down)
	{
		mvt.y--;
		moved = true;
	}
	else if (down && !up)
	{
		mvt.y++;
		moved = true;
	}

	return moved;
}
