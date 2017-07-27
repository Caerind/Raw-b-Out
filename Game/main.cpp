#include "../Engine/Application/Application.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "GameState.hpp"
#include "IntroState.hpp"
#include "MenuState.hpp"

int main()
{
	oe::Application application;

	// Load Resources
	GameSingleton::loadTileset();
	GameSingleton::objectsTexture = application.getTextures().create("objects", oe::TextureLoader::loadFromFile("Assets/objects.png"));
	GameSingleton::sansationFont = application.getFonts().create("sansation", oe::FontLoader::loadFromFile("Assets/sansation.ttf"));
	GameSingleton::actionSound = application.getAudio().createSound("action", "Assets/action.wav");
	
	// Load Window
	oe::Window& window = application.getWindow();
	window.create(sf::VideoMode(WINSIZEX, WINSIZEY), WINTITLE, sf::Style::Close);
	window.setMainView(sf::View(sf::FloatRect(0.0f, 0.0f, WINSIZEX, WINSIZEY)));
	window.applyMainView();

	// Load State
	//application.start<IntroState>();
	application.start<GameState>();

	getchar();
	return 0;
}
