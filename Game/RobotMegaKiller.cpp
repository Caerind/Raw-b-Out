#include "RobotMegaKiller.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "Projectile.hpp"

RobotMegaKiller::RobotMegaKiller(oe::EntityManager& manager)
	: Robot(manager, Robot::MegaKiller)
{
	mAwake = false;
}

void RobotMegaKiller::update(oe::Time dt)
{
	Robot::update(dt);
}

bool RobotMegaKiller::determineMovement(oe::Vector2& mvt)
{
	return false;
}
