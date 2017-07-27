#include "GameState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"
#include "PostState.hpp" // Used to switch to

GameState::GameState(oe::StateManager& manager)
	: oe::State(manager)
	, mWorld(manager.getApplication())
{
	GameSingleton::clear();

	mWorld.getRenderSystem().setBackgroundColor(oe::Color::DarkGray);
}

bool GameState::handleEvent(const sf::Event& event)
{
	OE_PROFILE_FUNCTION("GameState::handleEvent");

	mWorld.handleEvent(event);

	return false;
}

bool GameState::update(oe::Time dt)
{
	OE_PROFILE_FUNCTION("GameState::update");

	mWorld.update(dt);

	return false;
}

void GameState::render(sf::RenderTarget& target)
{
	OE_PROFILE_FUNCTION("GameState::render");

	mWorld.render(target);
}

oe::Window& GameState::getWindow()
{
	return getApplication().getWindow();
}

oe::View& GameState::getView()
{
	return mWorld.getRenderSystem().getView();
}