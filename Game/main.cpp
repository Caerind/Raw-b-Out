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
	GameSingleton::minikillerTexture = application.getTextures().create("minikillerTexture", oe::TextureLoader::loadFromFile(TEXTURE_MINIKILLER));
	GameSingleton::killerTexture = application.getTextures().create("killerTexture", oe::TextureLoader::loadFromFile(TEXTURE_KILLER));
	GameSingleton::projectilesTexture = application.getTextures().create("projectilesTexture", oe::TextureLoader::loadFromFile(TEXTURE_PROJECTILES));
	GameSingleton::guiTexture = application.getTextures().create("guiTexture", oe::TextureLoader::loadFromFile(TEXTURE_GUI));
	GameSingleton::weaponsTexture = application.getTextures().create("weaponsTexture", oe::TextureLoader::loadFromFile(TEXTURE_WEAPONS));
	GameSingleton::sansationFont = application.getFonts().create("sansation", oe::FontLoader::loadFromFile(FONTSANSATION));
	GameSingleton::actionSound = application.getAudio().createSound("action", SOUNDACTION);
	GameSingleton::loadTileset();
	GameSingleton::loadAnimations();
	GameSingleton::loadInputs();
	GameSingleton::loadWeapons();

	GameSingleton::name = "RobotXV8";
	
	// Load Window
	oe::Window& window = application.getWindow();
	window.create(sf::VideoMode(WINSIZEX, WINSIZEY), WINTITLE, sf::Style::Close);
	//application.getWindow().setIcon("...");
	window.useCustomCursor("../Assets/cursor.png", sf::IntRect(0, 0, 48, 48), sf::Vector2f(24, 24));
	window.setScreenshotPath("../Screenshots/");
	window.setMainView(sf::View(sf::FloatRect(0.0f, 0.0f, WINSIZEX, WINSIZEY)));
	window.applyMainView();

	// Load State
	//application.start<IntroState>();
	application.start<GameState>();

	getchar();
	return 0;
}
