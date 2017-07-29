#include "RobotPlayer.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/World.hpp"
#include "../Engine/Application/Application.hpp"

RobotPlayer::RobotPlayer(oe::EntityManager& manager)
	: Robot(manager, Robot::Killer)
	, mAction(*this)
{
	// TODO : Player specific stats
	// TODO : Remove temp stat
	setSpeed(300);

	oe::ActionId shootAction = mAction.addAction("shoot");
	mAction.setInput(shootAction, &GameSingleton::shootInput);
	mAction.addOutput(shootAction, [this]() { shoot(); });

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
	mLevel++;
	addPoint();
	addPoint();
	addPoint();
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
	return 100 + mLevel * 20; // TODO : Good formula ?
}

void RobotPlayer::addExperience(U32 experience)
{
	mExperience += experience;
	U32 x = 100;
	if (experience > getExperienceMax())
	{
		gainLevel();
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
		mBatteryBonus += 1.0f;
		spendPoint();
	}
}

void RobotPlayer::increaseSpeed()
{
	if (hasPoints())
	{
		mSpeedBonus += 1.0f;
		spendPoint();
	}
}

void RobotPlayer::increaseStrength()
{
	if (hasPoints())
	{
		mStrengthBonus++;
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
	else
	{
		notMoving();
	}

	mWeaponCooldown += dt;

	if (mBattery <= 0.0f)
	{
		setPosition(120, 120);
		setBattery(getBatteryMax());
		updateView();
	}
}

void RobotPlayer::shoot()
{
	if (Robot::shoot(getApplication().getWindow().getCursorPositionView(getWorld().getRenderSystem().getView())) && mWeapon.getId() != 0)
	{
		consumeBattery(1.0f); // TODO : Battery consumtion
	}
}

void RobotPlayer::updateView()
{
	getWorld().getRenderSystem().getView().setCenter(getPosition());
}

void RobotPlayer::addWeapon(WeaponId id)
{
	mWeapons.push_back(id);
}

bool RobotPlayer::determineMovement(oe::Vector2& mvt)
{
	bool moved = false;

	bool left = sf::Keyboard::isKeyPressed(GameSingleton::left.getKey());
	bool right = sf::Keyboard::isKeyPressed(GameSingleton::right.getKey());
	bool up = sf::Keyboard::isKeyPressed(GameSingleton::up.getKey());
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
