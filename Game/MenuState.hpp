#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../Engine/Application/StateManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class MenuState : public oe::State
{
	public:
		MenuState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

	private:
		sf::Texture mTextureBg;
		sf::Sprite mBackground;
};

#endif // MENUSTATE_HPP
