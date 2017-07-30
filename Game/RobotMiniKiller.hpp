#ifndef ROBOTMINIKILLER_HPP
#define ROBOTMINIKILLER_HPP

#include "Robot.hpp"
#include "BarComponent.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

class RobotMiniKiller : public Robot
{
	public:
		RobotMiniKiller(oe::EntityManager& manager);

		virtual void update(oe::Time dt);

	private:
		oe::SpriteComponent mSprite;
		BarComponent mBar;
		bool mFocusPlayer;
};

#endif // ROBOTMINIKILLER_HPP
