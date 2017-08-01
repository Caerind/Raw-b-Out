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
	mNew.setPosition(sf::Vector2f(194, 500));
	mName.setPosition(sf::Vector2f(688, 200));
	mDate.setPosition(sf::Vector2f(688, 350));
	mLoad.setPosition(sf::Vector2f(688, 500));

	mNameLabel.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mNameBack.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mColorLabel.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mColorBack.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mWheel.setTexture(getApplication().getTextures().get(GameSingleton::killerTexture));
	mRobot.setTexture(getApplication().getTextures().get(GameSingleton::killerTexture));
	mEyes.setTexture(getApplication().getTextures().get(GameSingleton::killerTexture));
	mNameLabel.setTextureRect(sf::IntRect(0, 480, 288, 96));
	mNameBack.setTextureRect(sf::IntRect(769, 288, 288, 96));
	mColorLabel.setTextureRect(sf::IntRect(288, 480, 288, 96));
	mColorBack.setTextureRect(sf::IntRect(769, 288, 288, 96));
	mWheel.setTextureRect(sf::IntRect(64, 0, 21, 21));
	mRobot.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mEyes.setTextureRect(sf::IntRect(64, 21, 14, 6));
	mNameLabel.setPosition(50, 200);
	mNameBack.setPosition(mNameLabel.getPosition().x + 288, mNameLabel.getPosition().y);
	mColorLabel.setPosition(50, 350);
	mColorBack.setPosition(mColorLabel.getPosition().x + 288, mColorLabel.getPosition().y);
	mRobot.setPosition(mColorBack.getPosition() + sf::Vector2f(144 - 32, 48 - 32));
	mWheel.setPosition(mRobot.getPosition() + sf::Vector2f(32.f - 10.5f, 56.f - 10.5f));
	mEyes.setPosition(mRobot.getPosition() + sf::Vector2f(30.f, 18.f));

	mTextName.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mTextDate.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mNameText.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mTextName.setFillColor(sf::Color(255, 127, 39));
	mTextDate.setFillColor(sf::Color(255, 127, 39));
	mNameText.setFillColor(sf::Color(255, 127, 39));
	mTextName.setCharacterSize(20);
	mTextDate.setCharacterSize(20);
	mNameText.setCharacterSize(20);
	mTextName.setPosition(688 + 144, 200 + 48);
	mTextDate.setPosition(688 + 144, 350 + 48);
	mNameText.setPosition(mNameBack.getPosition().x + 144, mNameBack.getPosition().y + 48);
	mTextName.setString("");
	mTextDate.setString("");
	mNameText.setString("Write your name");
	mTextName.setOrigin(mTextName.getGlobalBounds().width * 0.5f, mTextName.getGlobalBounds().height * 0.5f);
	mTextDate.setOrigin(mTextDate.getGlobalBounds().width * 0.5f, mTextDate.getGlobalBounds().height * 0.5f);
	mNameText.setOrigin(mNameText.getGlobalBounds().width * 0.5f, mNameText.getGlobalBounds().height * 0.5f);

	mSeparator.setPosition(655, 180);
	mSeparator.setSize(sf::Vector2f(4, 400));
	mSeparator.setFillColor(sf::Color(127, 127, 127));

	mRobot.setColor(randomColor());

	mLoaded = false;
	if (GameSingleton::loader.loadFromFile("Assets/save.xml"))
	{
		if (GameSingleton::loader.readNode("save"))
		{
			std::string version = "";
			GameSingleton::loader.getAttribute("version", version);
			if (version == SAVE_VERSION)
			{
				mLoaded = true;

				GameSingleton::name = "";

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

			if (mNameText.getString() == "Write your name")
			{
				GameSingleton::name = "XV9";
			}
			else
			{
				GameSingleton::name = mNameText.getString();
			}

			generate();

			clearStates();
			pushState<GameState>();
		}
		if (mColorBack.getGlobalBounds().contains(mpos))
		{
			GameSingleton::playSound(GameSingleton::clickSound);
			mRobot.setColor(randomColor());
		}
		if (mLoad.getGlobalBounds().contains(mpos))
		{
			GameSingleton::playSound(GameSingleton::clickSound);
			clearStates();
			pushState<GameState>();
		}
		if (cross.contains(mpos))
		{
			GameSingleton::playSound(GameSingleton::errorSound);
			popState();
		}
	}

	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == 13)
		{
		}
		else if (event.text.unicode == '\t')
		{
		}
		else if (event.text.unicode == '\b')
		{
			getApplication().getAudio().playSound(GameSingleton::buttonSound);
			std::string str = mNameText.getString();
			if (str.size() > 0)
			{
				str.pop_back();
				mNameText.setString(str);
				mNameText.setOrigin(mNameText.getGlobalBounds().width * 0.5f, mNameText.getGlobalBounds().height * 0.5f);
			}
		}
		else
		{
			getApplication().getAudio().playSound(GameSingleton::buttonSound);
			std::string str = mNameText.getString();
			if (str == "Write your name")
			{
				str.clear();
			}
			str.push_back((char)event.text.unicode);
			mNameText.setString(str);
			mNameText.setOrigin(mNameText.getGlobalBounds().width * 0.5f, mNameText.getGlobalBounds().height * 0.5f);
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

	target.draw(mNameLabel);
	target.draw(mNameBack);
	target.draw(mNameText);

	target.draw(mColorLabel);
	target.draw(mColorBack);
	target.draw(mWheel);
	target.draw(mRobot);
	target.draw(mEyes);
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
	node.append_attribute("previous") = 0;
	node.append_attribute("spawn") = "200,200";
	node.append_attribute("position") = "200,200";
	node = node.parent();

	node = node.append_child("weapons");
	node = node.parent();

	node = node.append_child("visited");
	node = node.parent();

	GameSingleton::loader.saveToFile("Assets/save.xml");
}

sf::Color PreState::randomColor()
{
	sf::Color c((U8)oe::Random::get<U32>(0, 255), (U8)oe::Random::get<U32>(0, 255), (U8)oe::Random::get<U32>(0, 255));
	GameSingleton::color = oe::toOE(c);

	return c;
}
