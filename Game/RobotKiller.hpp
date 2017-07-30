#ifndef ROBOTKILLER_HPP
#define ROBOTKILLER_HPP

#include "Robot.hpp"

class RobotKiller : public Robot
{
	public:
		RobotKiller(oe::EntityManager& manager);

		virtual void update(oe::Time dt);

		virtual bool determineMovement(oe::Vector2& mvt);

	private:
		bool mFocusPlayer;
};

#endif // ROBOTKILLER_HPP
