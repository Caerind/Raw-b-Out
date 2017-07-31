#ifndef ROBOTKILLER_HPP
#define ROBOTKILLER_HPP

#include "Robot.hpp"
#include "BarComponent.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

class RobotKiller : public Robot
{
	public:
		RobotKiller(oe::EntityManager& manager, const oe::Vector2& position);

		virtual void update(oe::Time dt);

	private:
		oe::SpriteComponent mSprite;
		BarComponent mBar;
		U32 mCounter;
		bool mFocusPlayer;
};

#endif // ROBOTKILLER_HPP
