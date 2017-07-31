#include "RobotMegaKiller.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "Projectile.hpp"

RobotMegaKiller::RobotMegaKiller(oe::EntityManager& manager, const oe::Vector2& position)
	: Robot(manager, Robot::MegaKiller)
	, mSprite(*this)
	, mBar(*this)
{
	mFocusPlayer = false;

	mBatteryMax = 4000.0f;
	mBattery = 4000.0f;

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
}

void RobotMegaKiller::update(oe::Time dt)
{
	mWeaponCooldown += dt * 0.8f;
	mSpecialAttack += dt;

	const oe::Vector2 player = GameSingleton::player->getPosition();
	oe::Vector2 delta = player - getPosition();
	const F32 d = delta.getLength();
	if (!mFocusPlayer && d <= FOCUSGAIN_DISTANCE + 700)
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
		if (mSpecialAttack > oe::seconds(5.f))
		{
			mSpecialAttack = oe::Time::Zero;

			for (U32 i = 0; i < 6; i++)
			{
				oe::Vector2 v(1.f, 1.f);
				v.setPolarAngle(oe::Random::get<F32>(0.f, 360.f));
				v.setLength(1.f);
				getManager().createEntity<Projectile>(Projectile::Plasma, getPosition() + v * 200.f, v, mWeapon.getStrength() + mStrengthBonus, getId());
			}
		}
	}

	mBar.setValue(mBattery);
	mBar.setVisible(getBattery() != getBatteryMax());

	if (mBattery <= 0.0f)
	{
		kill();
	}
}


