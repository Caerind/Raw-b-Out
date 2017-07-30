#include "PreState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Application/Application.hpp"

#include "GameState.hpp"

PreState::PreState(oe::StateManager& manager)
	: oe::State(manager)
{
	mScreen.setTexture(getApplication().getTextures().get(GameSingleton::screenTexture));
	mScreen.setTextureRect(sf::IntRect(0, 0, 960, 600));
	mScreen.setPosition(32, 84);

	mNew.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mName.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mDate.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mLoad.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mNew.setTextureRect(sf::IntRect(576, 384, 287, 96));
	mName.setTextureRect(sf::IntRect(769, 288, 288, 96));
	mDate.setTextureRect(sf::IntRect(769, 288, 288, 96));
	mLoad.setTextureRect(sf::IntRect(0, 384, 288, 96));
	mNew.setPosition(sf::Vector2f(100, 500));
	mName.setPosition(sf::Vector2f(600, 200));
	mDate.setPosition(sf::Vector2f(600, 350));
	mLoad.setPosition(sf::Vector2f(600, 500));

	mTextName.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mTextDate.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mTextName.setFillColor(sf::Color(255, 127, 39));
	mTextDate.setFillColor(sf::Color(255, 127, 39));
	mTextName.setCharacterSize(20);
	mTextDate.setCharacterSize(20);
	mTextName.setPosition(600 + 144, 200 + 48);
	mTextDate.setPosition(600 + 144, 350 + 48);
	mTextName.setString("");
	mTextDate.setString("");
	mTextName.setOrigin(mTextName.getGlobalBounds().width * 0.5f, mTextName.getGlobalBounds().height * 0.5f);
	mTextDate.setOrigin(mTextDate.getGlobalBounds().width * 0.5f, mTextDate.getGlobalBounds().height * 0.5f);

	mSeparator.setPosition(510, 180);
	mSeparator.setSize(sf::Vector2f(4, 400));
	mSeparator.setFillColor(sf::Color(127, 127, 127));

	mLoaded = false;
	if (GameSingleton::loader.loadFromFile("../Assets/save.xml"))
	{
		if (GameSingleton::loader.readNode("save"))
		{
			std::string version = "";
			GameSingleton::loader.getAttribute("version", version);
			if (version == SAVE_VERSION)
			{
				mLoaded = true;

				GameSingleton::name = "";
				GameSingleton::color = oe::Color::White;

				GameSingleton::loader.getAttribute("date", GameSingleton::name);
				oe::Date date;
				date.fromString(GameSingleton::name);
				GameSingleton::loader.getAttribute("name", GameSingleton::name);

				mTextName.setString(GameSingleton::name);
				mTextDate.setString(date.toString("%d/%m/%Y"));

				mTextName.setOrigin(mTextName.getGlobalBounds().width * 0.5f, mTextName.getGlobalBounds().height * 0.5f);
				mTextDate.setOrigin(mTextDate.getGlobalBounds().width * 0.5f, mTextDate.getGlobalBounds().height * 0.5f);
			}
		}
	}

	if (!mLoaded)
	{
		mLoaded = false;
		mName.setPosition(-200, -200);
		mTextDate.setString("No game found");
		mTextDate.setOrigin(mTextDate.getGlobalBounds().width * 0.5f, mTextDate.getGlobalBounds().height * 0.5f);
		mLoad.setPosition(-200, -200);
	}
}

bool PreState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		static sf::FloatRect cross(30, 80, 40, 40);
		sf::Vector2f mpos((F32)event.mouseButton.x, (F32)event.mouseButton.y);
		if (mNew.getGlobalBounds().contains(mpos))
		{
			GameSingleton::playSound(GameSingleton::clickSound);
			
			GameSingleton::name = "TestRobot";
			GameSingleton::color = oe::Color::LightOrange;
			generate();

			pushState<GameState>();
		}
		if (mLoad.getGlobalBounds().contains(mpos))
		{
			GameSingleton::playSound(GameSingleton::clickSound);
			pushState<GameState>();
		}
		if (cross.contains(mpos))
		{
			GameSingleton::playSound(GameSingleton::errorSound);
			popState();
		}
	}
	return false;
}

bool PreState::update(oe::Time dt)
{
	return false;
}

void PreState::render(sf::RenderTarget& target)
{
	target.draw(mScreen);

	target.draw(mNew);

	target.draw(mSeparator);

	target.draw(mName);
	target.draw(mDate);
	target.draw(mLoad);

	target.draw(mTextName);
	target.draw(mTextDate);
}

void PreState::generate()
{
	GameSingleton::loader.newFile();

	auto& node = GameSingleton::loader.mCurrentNode;

	node = node.append_child("save");
	node.append_attribute("version") = std::string(SAVE_VERSION).c_str();
	node.append_attribute("name") = GameSingleton::name.c_str();
	node.append_attribute("color") = GameSingleton::color.toString().c_str();
	node.append_attribute("date") = oe::Date().toString().c_str();

	node = node.append_child("stats");
	node.append_attribute("level") = 1;
	node.append_attribute("exp") = 0;
	node.append_attribute("points") = 0;
	node.append_attribute("battery") = 0;
	node.append_attribute("batteryB") = 0;
	node.append_attribute("speedB") = 0;
	node.append_attribute("strengthB") = 0;
	node = node.parent();

	node = node.append_child("map");
	node.append_attribute("id") = 0;
	node.append_attribute("spawn") = "200,200";
	node.append_attribute("position") = "200,200";
	node = node.parent();

	node = node.append_child("weapons");
	node = node.parent();

	GameSingleton::loader.saveToFile("../Assets/save.xml");
}