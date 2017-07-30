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
}

void RobotMiniKiller::update(oe::Time dt)
{
	mWeaponCooldown += dt * 0.8f;

	const oe::Vector2 player = GameSingleton::player->getPosition();
	oe::Vector2 delta = player - getPosition();
	const F32 d = delta.getLength();
	if (mFocusPlayer && d > FOCUSLOST_DISTANCE)
	{
		mFocusPlayer = false;
	}
	else if (!mFocusPlayer && d <= FOCUSGAIN_DISTANCE)
	{
		mFocusPlayer = true;
	}

	if (mFocusPlayer)
	{
		mSprite.setTextureRect(sf::IntRect(0, (delta.x >= 0.0f) ? 0 : 64, 64, 64));
		if (mWeaponCooldown > mWeapon.getCooldown() && mWeapon.getId() > 0)
		{
			delta.normalize();
			mWeaponCooldown = oe::Time::Zero;
			getManager().createEntity<Projectile>(mWeapon.getProjType(), getPosition(), delta, mWeapon.getStrength() + mStrengthBonus, getId());
		}
	}

	mBar.setValue(mBattery);
	mBar.setVisible(getBattery() != getBatteryMax());

	if (mBattery <= 0.0f)
	{
		kill();
	}
}
