#include "RobotMiniKiller.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "Projectile.hpp"

RobotMiniKiller::RobotMiniKiller(oe::EntityManager& manager)
	: Robot(manager, Robot::MiniKiller)
	, mSprite(*this)
	, mBar(*this)
{
	mFocusPlayer = false;

	mCollision.setSize(oe::Vector2(40, 40));

	setWeapon(GameSingleton::map->getEnemyWeapon());
	mBattery = GameSingleton::map->getEnemyBattery();
	mBatteryMax = GameSingleton::map->getEnemyBattery();

	mSprite.setTexture(GameSingleton::minikillerTexture);
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mSprite.setPosition(-32.0f, -57.0f);

	mBar.setSize(40, 5);
	mBar.setPosition(-20, -50);
	mBar.setPositionZ(20);
	mBar.setBackColor(sf::Color::Red);
	mBar.setBarColor(sf::Color::Green);
	mBar.setOutlineColor(sf::Color::Black);
	mBar.setOutlineThickness(1.2f);
	mBar.setValueMax(mBatteryMax);
	mBar.setValue(mBattery);
}

void RobotMiniKiller::update(oe::Time dt)
{
	//oe::DebugDraw::drawRect(getCollision());
	//oe::DebugDraw::drawPoint(getPosition());

	mWeaponCooldown += dt * 0.8f;

	const oe::Vector2 player = GameSingleton::player->getPosition();
	oe::Vector2 delta = player - getPosition();
	const F32 d = delta.getLength();
	delta.normalize();
	if (!mFocusPlayer && d <= GameSingleton::FocusGainDistance)
	{
		if (mSkipRay >= 2)
		{
			mSkipRay = 0;
			oe::Vector2 point(getPosition());
			U32 it = (U32)(GameSingleton::FocusGainDistance / 32);
			oe::Vector2i coords;
			oe::Vector2i oldCoords;
			bool found = true;
			for (U32 i = 0; i < it; i++)
			{
				point += delta * 32.f;
				coords = oe::MapUtility::worldToCoords(point, oe::MapUtility::Orthogonal, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY));
				if (oldCoords != coords)
				{
					oldCoords = coords;
					if (GameSingleton::map->collide(coords))
					{
						found = false;
						it = 0;
					}
				}
			}
			if (found)
			{
				mFocusPlayer = true;
				GameSingleton::enemyFocus++;
				if (GameSingleton::playingMainMusic)
				{
					GameSingleton::playFight();
				}
			}
		}
		else
		{
			mSkipRay++;
		}
	}
	else if (mFocusPlayer && d > GameSingleton::FocusLostDistance)
	{
		mFocusPlayer = false; 
		GameSingleton::enemyFocus--;
		if (GameSingleton::enemyFocus == 0 && !GameSingleton::playingMainMusic)
		{
			GameSingleton::playMain();
		}
	} 

	if (mFocusPlayer)
	{
		mSprite.setTextureRect(sf::IntRect(0, (delta.x >= 0.0f) ? 0 : 64, 64, 64));
		if (mWeaponCooldown > mWeapon.getCooldown() && mWeapon.getId() > 0)
		{
			mWeaponCooldown = oe::Time::Zero;
			getManager().createEntity<Projectile>(mWeapon.getProjType(), getPosition(), delta, mWeapon.getStrength() + mStrengthBonus, getId());
		}
	}

	mBar.setValue(mBattery);
	mBar.setVisible(getBattery() != getBatteryMax());

	if (mBattery <= 0.0f)
	{
		kill();
		if (mFocusPlayer)
		{
			GameSingleton::enemyFocus--;
			if (GameSingleton::enemyFocus == 0 && !GameSingleton::playingMainMusic)
			{
				GameSingleton::playMain();
			}
		}
	}
}
