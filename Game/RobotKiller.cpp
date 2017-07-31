#include "RobotKiller.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "Projectile.hpp"

RobotKiller::RobotKiller(oe::EntityManager& manager, const oe::Vector2& position)
	: Robot(manager, Robot::Killer)
	, mSprite(*this)
	, mBar(*this)
{
	mFocusPlayer = false;

	mBattery = GameSingleton::map->getBossBattery();
	mBatteryMax = GameSingleton::map->getBossBattery();
	setWeapon(GameSingleton::map->getBossWeapon());

	mCollision.setSize(oe::Vector2(200, 200));
	mCollision.setOrigin(oe::Vector2(30, 30));

	setWeapon(GameSingleton::map->getEnemyWeapon());

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

	setPosition(position);

	setScale(6.0f);

	mCounter = 0;
}

void RobotKiller::update(oe::Time dt)
{
	//oe::DebugDraw::drawRect(getCollision());
	//oe::DebugDraw::drawPoint(getPosition(), oe::Color::Red, 5.f);
	
	mWeaponCooldown += dt * 0.8f;

	const oe::Vector2 player = GameSingleton::player->getPosition();
	oe::Vector2 delta = player - getPosition();
	const F32 d = delta.getLength();
	if (!mFocusPlayer && d <= GameSingleton::FocusGainDistance + 700)
	{
		mFocusPlayer = true;
		GameSingleton::enemyFocus++;
		if (GameSingleton::playingMainMusic)
		{
			GameSingleton::playFight();
		}
	}

	if (mFocusPlayer)
	{
		mSprite.setTextureRect(sf::IntRect(0, (delta.x >= 0.0f) ? 0 : 64, 64, 64));
		if (mWeaponCooldown > mWeapon.getCooldown() && mWeapon.getId() > 0)
		{
			delta.normalize();
			mWeaponCooldown = oe::Time::Zero;
			mCounter++;
			if (mCounter > 5)
			{
				getManager().createEntity<Projectile>(Projectile::Plasma, getPosition() + delta * 60.f, delta, mWeapon.getStrength() + mStrengthBonus, getId());
				mCounter = 0;
			}
			else
			{
				getManager().createEntity<Projectile>(mWeapon.getProjType(), getPosition() + delta * 60.f, delta, mWeapon.getStrength() + mStrengthBonus, getId());
			}
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

