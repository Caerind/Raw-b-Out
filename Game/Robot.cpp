#include "Robot.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "Projectile.hpp"

Robot::Robot(oe::EntityManager& manager, Robot::Type robotType)
	: oe::Entity(manager)
	, mAnimation(*this)
	, mBattery(ROBOT_DEFAULT_BATTERY)
	, mBatteryMax(ROBOT_DEFAULT_BATTERY)
	, mSpeed(ROBOT_DEFAULT_SPEED)
	, mRobotType(robotType)
{
	mBatteryBonus = 0.0f;
	mSpeedBonus = 0.0f;
	mStrengthBonus = 0;

	switch (robotType)
	{
		case MiniKiller:
			setWeapon(GameSingleton::map->getEnemyWeapon());
			mAnimation.setPosition(-32.0f, -57.0f);
			break;
		case Killer: 
			mAnimation.setPosition(-32.0f, -57.0f); 
			break;
		case MegaKiller: 
			break;
	}
	mAnimation.play(getRightAnimationIdle());
}

void Robot::setBattery(F32 battery)
{
	mBattery = battery;
	if (mBattery > getBatteryMaxWithBonus())
	{
		mBattery = getBatteryMaxWithBonus();
	}
}

F32 Robot::getBattery() const
{
	return mBattery;
}

bool Robot::consumeBattery(F32 amount)
{
	bool alive = mBattery > 0.0f;
	mBattery -= amount;
	if (mBattery <= 0.0f)
	{
		mBattery = 0.0f;
		if (alive)
		{
			return true;
		}
	}
	return false;
}

void Robot::setBatteryMax(F32 batteryMax)
{
	mBatteryMax = batteryMax;
}

F32 Robot::getBatteryMax() const
{
	return mBatteryMax;
}

F32 Robot::getBatteryMaxWithBonus() const
{
	return mBatteryMax + mBatteryBonus;
}

void Robot::setSpeed(F32 speed)
{
	mSpeed = speed;
}

F32 Robot::getSpeed() const
{
	return mSpeed;
}

F32 Robot::getSpeedWithBonus() const
{
	return mSpeed + mSpeedBonus;
}

void Robot::setWeapon(WeaponId id)
{
	mWeapon.setId(id);
}

WeaponId Robot::getWeapon() const
{
	return mWeapon.getId();
}

Robot::Type Robot::getRobotType() const
{
	return mRobotType;
}

bool Robot::shoot(const oe::Vector2& pos)
{
	if (mWeaponCooldown > mWeapon.getCooldown() && mWeapon.getId() > 0)
	{
		oe::Vector2 delta = pos - getPosition();
		delta.normalize();

		getManager().createEntity<Projectile>(mWeapon.getProjType(), getPosition(), delta, mWeapon.getStrength() + mStrengthBonus, getId());

		mWeaponCooldown = oe::Time::Zero;

		return true;
	}
	return false;
}

void Robot::update(oe::Time dt)
{
	oe::Vector2 mvt;
	bool moved = determineMovement(mvt);
	if (moved)
	{
		tryMove(dt, mvt);
	}
	else
	{
		notMoving();
	}

	// AI are stronger with cooldown so make it harder for them
	if (getName() != "player")
	{
		mWeaponCooldown += dt * 0.8f;
	}
	else
	{
		mWeaponCooldown += dt;
	}

	if (mBattery <= 0.0f)
	{
		kill();
	}
}

bool Robot::determineMovement(oe::Vector2& mvt)
{
	return false;
}

bool Robot::tryMove(oe::Time dt, oe::Vector2& mvt)
{
	mvt.setLength(dt.asSeconds() * getSpeedWithBonus());
	oe::Vector2 nextPos = getPosition() + mvt;
	oe::Vector2i coords = oe::MapUtility::worldToCoords(nextPos, oe::MapUtility::Orthogonal, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY));

	bool collision = false;
	if (coords != mCoords)
	{
		if (GameSingleton::map->collide(coords))
		{
			collision = true;
		}
		else
		{
			mCoords = coords;
		}
	}
	if (!collision)
	{
		setPosition(nextPos);

		bool vert = oe::Math::equals(mvt.x, 0.0f);
		if (!vert && mvt.x > 0.0f)
		{
			oe::Animation* a = getRightAnimationMove();
			if (!mAnimation.isPlaying(a))
			{
				mAnimation.play(a);
			}
		}
		else if (!vert && mvt.x < 0.0f)
		{
			oe::Animation* a = getLeftAnimationMove();
			if (!mAnimation.isPlaying(a))
			{
				mAnimation.play(a);
			}
		}
		else
		{
			if (mAnimation.isPlaying(getRightAnimationIdle()))
			{
				mAnimation.play(getRightAnimationMove());
			}
			if (mAnimation.isPlaying(getLeftAnimationIdle()))
			{
				mAnimation.play(getLeftAnimationMove());
			}
		}
	}
	else
	{
		mvt.makeZero();
		notMoving();
	}

	return !collision;
}

void Robot::notMoving()
{
	if (mAnimation.isPlaying(getRightAnimationMove()))
	{
		mAnimation.play(getRightAnimationIdle());
	}
	if (mAnimation.isPlaying(getLeftAnimationMove()))
	{
		mAnimation.play(getLeftAnimationIdle());
	}
}

oe::Animation* Robot::getRightAnimationMove()
{
	switch (mRobotType)
	{
		case MiniKiller: return &GameSingleton::rightMiniKillerMove; break;
		case Killer: return &GameSingleton::rightKillerMove; break;
		case MegaKiller: return &GameSingleton::rightMegaKillerMove; break;
	}
	return nullptr;
}

oe::Animation* Robot::getLeftAnimationMove()
{
	switch (mRobotType)
	{
		case MiniKiller: return &GameSingleton::leftMiniKillerMove; break;
		case Killer: return &GameSingleton::leftKillerMove; break;
		case MegaKiller: return &GameSingleton::leftMegaKillerMove; break;
	}
	return nullptr;
}

oe::Animation* Robot::getRightAnimationIdle()
{
	switch (mRobotType)
	{
		case MiniKiller: return &GameSingleton::rightMiniKillerIdle; break;
		case Killer: return &GameSingleton::rightKillerIdle; break;
		case MegaKiller: return &GameSingleton::rightMegaKillerIdle; break;
	}
	return nullptr;
}

oe::Animation* Robot::getLeftAnimationIdle()
{
	switch (mRobotType)
	{
		case MiniKiller: return &GameSingleton::leftMiniKillerIdle; break;
		case Killer: return &GameSingleton::leftKillerIdle; break;
		case MegaKiller: return &GameSingleton::leftMegaKillerIdle; break;
	}
	return nullptr;
}
