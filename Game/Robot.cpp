#include "Robot.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Application/Application.hpp"
#include "../Engine/Core/EntityManager.hpp"
#include "Projectile.hpp"

Robot::Robot(oe::EntityManager& manager, Robot::Type robotType)
	: oe::Entity(manager)
	, mCollision(*this)
	, mBattery(GameSingleton::BatteryEnemy)
	, mBatteryMax(GameSingleton::BatteryEnemy)
	, mSpeed(GameSingleton::SpeedEnemy)
	, mRobotType(robotType)
{
	mBatteryBonus = 0.0f;
	mSpeedBonus = 0.0f;
	mStrengthBonus = 0;
	mSkipRay = 0;
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
	if (amount >= 2.0f)
	{
		getApplication().getAudio().playSound(GameSingleton::damageSound);
	}

	bool alive = mBattery > 0.0f;
	mBattery -= amount;
	if (mBattery <= 0.0f)
	{
		mBattery = 0.0f;
		if (alive)
		{
			getApplication().getAudio().playSound(GameSingleton::dieSound);
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

		getManager().createEntity<Projectile>(mWeapon.getProjType(), mStrikePos, delta, mWeapon.getStrength() + mStrengthBonus, getId());

		mWeaponCooldown = oe::Time::Zero;

		return true;
	}
	return false;
}

void Robot::update(oe::Time dt)
{
	/*
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
	*/


	/*
	// AI are stronger with cooldown so make it harder for them
	if (getName() != "player")
	{
		mWeaponCooldown += dt * 0.8f;
	}
	else
	{
		mWeaponCooldown += dt;
	}
	*/

	/*
	if (mBattery <= 0.0f)
	{
		kill();
	}
	*/
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
			if (GameSingleton::player->getId() == getId() && GameSingleton::map->getTileId(coords) == TILE_PRESSUREPLATE)
			{
				GameSingleton::map->removeRemovableWalls();
			}
			mCoords = coords;
		}
	}
	if (!collision)
	{
		setPosition(nextPos);
	}
	else
	{
		mvt.makeZero();
	}

	return !collision;
}

oe::Time Robot::getWeaponCooldown() const
{
	return mWeaponCooldown;
}

const oe::Rect& Robot::getCollision() const
{
	return mCollision.getAABB();
}
