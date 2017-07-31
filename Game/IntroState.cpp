#include "IntroState.hpp"

#include "../Engine/Application/Application.hpp"

#include "GameConfig.hpp"
#include "GameSingleton.hpp"

#include "MenuState.hpp" // Used to switch to

IntroState::IntroState(oe::StateManager& manager)
	: oe::State(manager)
{
	mAtmogTexture.loadFromFile(TEXTURE_ATMOG);
	mAtmogSprite.setTexture(mAtmogTexture);
}

bool IntroState::handleEvent(const sf::Event& event)
{
	return false;
}

bool IntroState::update(oe::Time dt)
{
	GameSingleton::loadResources2();
	GameSingleton::loadTileset();
	GameSingleton::loadInputs();
	GameSingleton::loadWeapons();

	static const oe::Time duration = oe::seconds(1.0f);

	mElapsed += dt;
	if (mElapsed > duration)
	{
		popState();
		pushState<MenuState>();
	}
	return false;
}

void IntroState::render(sf::RenderTarget& target)
{
	target.draw(mAtmogSprite);
}
