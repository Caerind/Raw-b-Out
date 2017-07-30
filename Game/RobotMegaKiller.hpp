#ifndef ROBOTMEGAKILLER_HPP
#define ROBOTMEGAKILLER_HPP

#include "Robot.hpp"

class RobotMegaKiller : public Robot
{
	public:
		RobotMegaKiller(oe::EntityManager& manager);

		virtual void update(oe::Time dt);

		virtual bool determineMovement(oe::Vector2& mvt);

	private:
		bool mAwake;
};

#endif // ROBOTMEGAKILLER_HPP
