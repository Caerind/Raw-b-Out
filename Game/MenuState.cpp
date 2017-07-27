#include "MenuState.hpp"

#include "GameSingleton.hpp"
#include "GameState.hpp" // Used to switch to
#include "PreState.hpp" // Used to switch to

#include "../Engine/Math/Math.hpp"
#include "../Engine/Math/Vector2.hpp"

MenuState::MenuState(oe::StateManager& manager)
	: oe::State(manager)
{
	mTextureBg.loadFromFile("Assets/menu.png");
	mBackground.setTexture(mTextureBg);
}

bool MenuState::handleEvent(const sf::Event& event)
{
	sf::Vector2f mpos = toSF(getApplication().getWindow().getCursorPosition());
	
	sf::FloatRect r1;
	sf::FloatRect r2;

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (r1.contains(mpos))
		{

		}
		if (r2.contains(mpos))
		{

		}
	}

	return false;
}

bool MenuState::update(oe::Time dt)
{
	return false;
}

void MenuState::render(sf::RenderTarget& target)
{
	target.draw(mBackground);
}
