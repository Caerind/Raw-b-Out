#include "RobotKiller.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "Projectile.hpp"

RobotKiller::RobotKiller(oe::EntityManager& manager)
	: Robot(manager, Robot::Killer)
{
	mFocusPlayer = false;
}

void RobotKiller::update(oe::Time dt)
{
	Robot::update(dt);

	if (mFocusPlayer)
	{
		shoot(GameSingleton::player->getPosition());
	}
}

bool RobotKiller::determineMovement(oe::Vector2& mvt)
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
