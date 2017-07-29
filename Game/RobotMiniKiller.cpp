#include "RobotMiniKiller.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "Projectile.hpp"

RobotMiniKiller::RobotMiniKiller(oe::EntityManager& manager)
	: Robot(manager, Robot::MiniKiller)
	, mBar(*this)
{
	mFocusPlayer = false;

	// TODO : Modernize colors
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
	Robot::update(dt);

	if (mFocusPlayer)
	{
		shoot(GameSingleton::player->getPosition());
	}

	mBar.setValue(mBattery);
	mBar.setVisible(getBattery() != getBatteryMax());
}

bool RobotMiniKiller::determineMovement(oe::Vector2& mvt)
{
	const oe::Vector2 player = GameSingleton::player->getPosition();
	const oe::Vector2 delta = player - getPosition();
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
		// TODO : Move
	}

	return false;
}
