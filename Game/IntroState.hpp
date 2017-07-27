#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "../Engine/Application/StateManager.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class IntroState : public oe::State
{
	public:
		IntroState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

	private:
		oe::Time mElapsed;
		sf::Texture mAtmogTexture;
		sf::Sprite mAtmogSprite;
};

#endif // INTROSTATE_HPP
