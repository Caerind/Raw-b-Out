#ifndef PRESTATE_HPP
#define PRESTATE_HPP

#include "../Engine/Application/StateManager.hpp"

#include "../Engine/System/ParserXml.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class PreState : public oe::State
{
	public:
		PreState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

		void generate();

	private:
		sf::Sprite mScreen;

		sf::Sprite mNew;

		sf::Text mTextName;
		sf::Text mTextDate;
		
		sf::Sprite mName;
		sf::Sprite mDate;
		sf::Sprite mLoad;

		sf::RectangleShape mSeparator;

		bool mLoaded;
};

#endif // PRESTATE_HPP
