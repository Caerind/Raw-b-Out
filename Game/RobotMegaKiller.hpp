#ifndef ROBOTMEGAKILLER_HPP
#define ROBOTMEGAKILLER_HPP

#include "Robot.hpp"
#include "BarComponent.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

class RobotMegaKiller : public Robot
{
	public:
		RobotMegaKiller(oe::EntityManager& manager, const oe::Vector2& position);

		virtual void update(oe::Time dt);

	private:
		oe::SpriteComponent mSprite;
		BarComponent mBar;
		bool mFocusPlayer;

		oe::Time mSpecialAttack;
};

#endif // ROBOTMEGAKILLER_HPP
