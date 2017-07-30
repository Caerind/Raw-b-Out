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
	GameSingleton::loadResources(application);

	GameSingleton::name = "RobotXV8";
	GameSingleton::color = oe::Color::Blue;
	
	// Load Window
	oe::Window& window = application.getWindow();
	window.create(sf::VideoMode(WINSIZEX, WINSIZEY), WINTITLE, sf::Style::Close);
	//application.getWindow().setIcon("...");
	window.useCustomCursor("../Assets/cursor.png", sf::IntRect(0, 0, 48, 48), sf::Vector2f(24, 24));
	window.setScreenshotPath("../Screenshots/");
	window.setMainView(sf::View(sf::FloatRect(0.0f, 0.0f, WINSIZEX, WINSIZEY)));
	window.applyMainView();
	window.closeOnClosed();

	// Load State
	application.start<IntroState>();

	getchar();
	return 0;
}
