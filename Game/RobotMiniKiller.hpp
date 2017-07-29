#ifndef ROBOTMINIKILLER_HPP
#define ROBOTMINIKILLER_HPP

#include "Robot.hpp"
#include "BarComponent.hpp"

class RobotMiniKiller : public Robot
{
	public:
		RobotMiniKiller(oe::EntityManager& manager);

		virtual void update(oe::Time dt);

		virtual bool determineMovement(oe::Vector2& mvt);

	private:
		BarComponent mBar;
		bool mFocusPlayer;
};

#endif // ROBOTMINIKILLER_HPP
