#include "GameState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"
#include "MenuState.hpp"

#include "../Engine/System/ParserXml.hpp"

GameState::GameState(oe::StateManager& manager)
	: oe::State(manager)
	, mWorld(manager.getApplication())
{
	GameSingleton::clear();
	GameSingleton::loadQueries();

	mWorld.getRenderSystem().setBackgroundColor(oe::Color::DarkGray);
	mWorld.getRenderSystem().setView(oe::View(0, 0, WINSIZEX, WINSIZEY));
	mWorld.getEntityManager().addQuery(&GameSingleton::rQuery);
	mWorld.getEntityManager().addQuery(&GameSingleton::rpQuery);
	mWorld.getEntityManager().addQuery(&GameSingleton::repQuery);
	mWorld.play();

	mInfoText.setLettersPerSecond(48);
	mInfoText.setCharacterSize(30);
	mInfoText.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mInfoText.setFillColor(sf::Color::White);
	mInfoText.setOutlineColor(sf::Color::Black);
	mInfoText.setOutlineThickness(2.0f);
	mInfoText.setPosition(20.0f, 20.0f);
	mInfoText.setString("");
	mCurrentInfo = 0;

	GameSingleton::mapHandle = mWorld.getEntityManager().createEntity<GameMap>();
	GameSingleton::map = GameSingleton::mapHandle.getAs<GameMap>();

	GameSingleton::playerHandle = mWorld.getEntityManager().createEntity<RobotPlayer>();
	GameSingleton::player = GameSingleton::playerHandle.getAs<RobotPlayer>();

	load();

	mBarPlayerLevel.setSize(WINSIZEX / 2 - 20, 20);
	mBarPlayerLevel.setPosition(52, WINSIZEY - 40);
	mBarPlayerLevel.setBackColor(sf::Color(153, 217, 234));
	mBarPlayerLevel.setBarColor(sf::Color(0, 162, 232));
	mBarPlayerLevel.setOutlineColor(sf::Color::Black);
	mBarPlayerLevel.setOutlineThickness(1.2f);
	mBarPlayerLevel.setValueMax((F32)GameSingleton::player->getExperienceMax());
	mBarPlayerLevel.setValue((F32)GameSingleton::player->getExperience());

	mBarPlayerBattery.setSize(WINSIZEX, 20);
	mBarPlayerBattery.setPosition(0, WINSIZEY - 20);
	mBarPlayerBattery.setBackColor(sf::Color::Red);
	mBarPlayerBattery.setBarColor(sf::Color::Green);
	mBarPlayerBattery.setOutlineColor(sf::Color::Black);
	mBarPlayerBattery.setOutlineThickness(1.2f);
	mBarPlayerBattery.setValueMax(GameSingleton::player->getBatteryMaxWithBonus());
	mBarPlayerBattery.setValue(GameSingleton::player->getBattery());

	mPlayerLevelText.setCharacterSize(20);
	mPlayerLevelText.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mPlayerLevelText.setFillColor(sf::Color::White);
	mPlayerLevelText.setOutlineColor(sf::Color::Black);
	mPlayerLevelText.setOutlineThickness(1.2f);
	mPlayerLevelText.setPosition(26.0f, WINSIZEY - 35);
	mPlayerLevelText.setString("");
	mPlayerLevelText.setOrigin(mPlayerLevelText.getGlobalBounds().width * 0.5f, mPlayerLevelText.getGlobalBounds().height * 0.5f);

	mBarPlayerCooldown.setPosition(mBarPlayerLevel.getPosition().x + mBarPlayerLevel.getSize().x, WINSIZEY - 40);
	mBarPlayerCooldown.setSize(WINSIZEX - 384 - mBarPlayerCooldown.getPosition().x, 20);
	mBarPlayerCooldown.setBackColor(sf::Color(0, 0, 0, 96));
	mBarPlayerCooldown.setBarColor(sf::Color(0, 0, 0, 150));
	mBarPlayerCooldown.setOutlineColor(sf::Color::Black);
	mBarPlayerCooldown.setOutlineThickness(1.2f);
	mBarPlayerCooldown.setValueMax(GameSingleton::weaponData[GameSingleton::player->getWeapon()].cool);
	mBarPlayerCooldown.setValue(GameSingleton::player->getWeaponCooldown().asSeconds());

	mButtonM.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
	mButtonM.setPosition(WINSIZEX - 288, WINSIZEY - 20 - 96);
	mButtonR.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
	mButtonR.setPosition(WINSIZEX - 384, WINSIZEY - 20 - 96);
	mButtonI.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
	mButtonI.setPosition(WINSIZEX - 192, WINSIZEY - 20 - 96);
	mButtonO.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
	mButtonO.setPosition(WINSIZEX - 96, WINSIZEY - 20 - 96);

	mShadow.setTexture(getApplication().getTextures().get(GameSingleton::shadowTexture));
	mShadow.setTextureRect(sf::IntRect(85, 40, 563 - 85, 333 - 40));
	mShadow.setScale(WINSIZEX / mShadow.getGlobalBounds().width, WINSIZEY / mShadow.getGlobalBounds().height);

	mCurrentPopUp = 0;
	mPopUp = nullptr;
}

bool GameState::handleEvent(const sf::Event& event)
{
	OE_PROFILE_FUNCTION("GameState::handleEvent");

	popUpEvent(event);

	if (mCurrentPopUp == 0)
	{
		mWorld.handleEvent(event);

		// Open Chest
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == GameSingleton::pickupInput.getButton())
		{
			oe::Vector2 p(getWindow().getCursorPositionView(getView()));
			oe::Vector2i c(oe::MapUtility::worldToCoords(p, oe::MapUtility::Orthogonal, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY)));
			GameSingleton::map->openChest(c);
		}
	}

	// Screenshot
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
	{
		getWindow().screenshot();
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
	{
		if (mProfiler.isVisible())
		{
			mProfiler.hide();
		}
		else
		{
			mProfiler.show();
		}
	}

	return false;
}

bool GameState::update(oe::Time dt)
{
	OE_PROFILE_FUNCTION("GameState::update");

	mDuration += dt;

	mInfoText.update(dt);

	if (mCurrentPopUp == 0)
	{
		mWorld.update(dt);

		Info* info = GameSingleton::map->getCurrentInfo();
		if (info != nullptr)
		{
			U32 current = info->getId();
			if (mCurrentInfo != current)
			{
				mCurrentInfo = current;
				mInfoText.setString(info->getString());
				getApplication().getAudio().playSound(GameSingleton::infoSound);
			}
		}
		else
		{
			mCurrentInfo = 0;
			mInfoText.setString("");
		}
	}

	mBarPlayerLevel.setValueMax((F32)GameSingleton::player->getExperienceMax());
	mBarPlayerLevel.setValue((F32)GameSingleton::player->getExperience());
	mBarPlayerBattery.setValueMax(GameSingleton::player->getBatteryMaxWithBonus());
	mBarPlayerBattery.setValue(GameSingleton::player->getBattery());
	mPlayerLevelText.setString(oe::toString(GameSingleton::player->getLevel()));
	mPlayerLevelText.setOrigin(mPlayerLevelText.getGlobalBounds().width * 0.5f, mPlayerLevelText.getGlobalBounds().height * 0.5f);
	mBarPlayerCooldown.setValueMax(GameSingleton::weaponData[GameSingleton::player->getWeapon()].cool);
	mBarPlayerCooldown.setValue(GameSingleton::weaponData[GameSingleton::player->getWeapon()].cool - GameSingleton::player->getWeaponCooldown().asSeconds());

	mProfiler.draw();

	return false;
}

void GameState::render(sf::RenderTarget& target)
{
	OE_PROFILE_FUNCTION("GameState::render");

	mWorld.render(target);

	target.draw(mShadow);

	target.draw(mInfoText);

	// Draw PopUp
	if (mCurrentPopUp != 0 && mPopUp != nullptr)
	{
		target.draw(*mPopUp);
	}

	target.draw(mBarPlayerLevel);
	target.draw(mPlayerLevelText);
	target.draw(mBarPlayerCooldown);

	target.draw(mButtonM);
	target.draw(mButtonR);
	target.draw(mButtonI);
	target.draw(mButtonO);
	target.draw(mBarPlayerBattery);
}

oe::Window& GameState::getWindow()
{
	return getApplication().getWindow();
}

oe::View& GameState::getView()
{
	return mWorld.getRenderSystem().getView();
}

void GameState::popUpEvent(const sf::Event& event)
{
	sf::Vector2f mpos((F32)event.mouseButton.x, (F32)event.mouseButton.y); // WARNING : Use only if type = mouseButton

	static const sf::FloatRect closeRect(WINSIZEX - 960, WINSIZEY - 20 - 600, 40.0f, 40.0f);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && mCurrentPopUp == 0)
	{
		GameSingleton::click();
		if (mPopUp != nullptr)
		{
			delete mPopUp;
		}
		mPopUp = new OptionsPopUp(getApplication().getTextures().get(GameSingleton::screenTexture), getApplication().getTextures().get(GameSingleton::guiTexture), getApplication().getAudio());
		mCurrentPopUp = 3;
		mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
		mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
		mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
		mButtonO.setTextureRect(sf::IntRect(192, 96, 96, 96));
	}
	else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && mCurrentPopUp != 0) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && closeRect.contains(mpos) && mCurrentPopUp != 0)) // Clic sur la croix
	{
		getApplication().getAudio().playSound(GameSingleton::errorSound);

		if (mPopUp != nullptr)
		{
			delete mPopUp;
		}
		mPopUp = nullptr;
		mCurrentPopUp = 0;
		mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
		mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
		mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
		mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
	}
	else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mButtonR.getGlobalBounds().contains(mpos)))
	{
		if (mCurrentPopUp == 1)
		{
			getApplication().getAudio().playSound(GameSingleton::errorSound);

			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = nullptr;
			mCurrentPopUp = 0;
			mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
		else
		{
			GameSingleton::click();

			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = new RobotPopUp(getApplication().getTextures().get(GameSingleton::screenTexture), getApplication().getTextures().get(GameSingleton::guiTexture), getApplication().getFonts().get(GameSingleton::sansationFont));
			mCurrentPopUp = 1;
			mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
			mButtonR.setTextureRect(sf::IntRect(0, 96, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
	}
	else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mButtonI.getGlobalBounds().contains(mpos)))
	{
		if (mCurrentPopUp == 2)
		{
			getApplication().getAudio().playSound(GameSingleton::errorSound);

			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = nullptr;
			mCurrentPopUp = 0;
			mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
		else
		{
			GameSingleton::click();

			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = new InventoryPopUp(getApplication().getTextures().get(GameSingleton::screenTexture), getApplication().getTextures().get(GameSingleton::guiTexture), getApplication().getFonts().get(GameSingleton::sansationFont), getApplication().getTextures().get(GameSingleton::weaponsTexture));
			mCurrentPopUp = 2;
			mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 96, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
	}
	else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mButtonO.getGlobalBounds().contains(mpos)))
	{
		if (mCurrentPopUp == 3)
		{
			getApplication().getAudio().playSound(GameSingleton::errorSound);

			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = nullptr;
			mCurrentPopUp = 0;
			mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
		else
		{
			GameSingleton::click();

			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = new OptionsPopUp(getApplication().getTextures().get(GameSingleton::screenTexture), getApplication().getTextures().get(GameSingleton::guiTexture), getApplication().getAudio());
			mCurrentPopUp = 3;
			mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 96, 96, 96));
		}
	}
	else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mButtonM.getGlobalBounds().contains(mpos)))
	{
		if (mCurrentPopUp == 4)
		{
			getApplication().getAudio().playSound(GameSingleton::errorSound);

			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = nullptr;
			mCurrentPopUp = 0;
			mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
		else
		{
			GameSingleton::click();

			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = new MapPopUp(getApplication().getTextures().get(GameSingleton::screenTexture), getApplication().getTextures().get(GameSingleton::guiTexture), getApplication().getTextures().get(GameSingleton::headTexture));
			mCurrentPopUp = 4;
			mButtonM.setTextureRect(sf::IntRect(864, 480, 96, 96));
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
	}

	if (mCurrentPopUp != 0)
	{
		if (mPopUp != nullptr)
		{
			mPopUp->handleEvent(event);
			if (mPopUp != nullptr && !mPopUp->isOpen())
			{
				delete mPopUp;
				mPopUp = nullptr;
				mCurrentPopUp = 0;
				mButtonM.setTextureRect(sf::IntRect(864, 384, 96, 96));
				mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
				mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
				mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
			}
			if (mPopUp != nullptr && mPopUp->isExit())
			{
				delete mPopUp;
				mPopUp = nullptr;

				save();

				clearStates();
				pushState<MenuState>();

				if (!GameSingleton::playingMainMusic)
				{
					GameSingleton::playMain();
				}
			}
		}
	}
}

void GameState::load()
{
	// READ

	std::string color;

	U32 level;
	U32 exp;
	U32 points;
	U32 battery;
	U32 batteryB;
	U32 speedB;
	U32 strengthB;

	U32 mapId = 0;
	U32 previousId = 0;
	std::string spawn;
	std::string pos;

	U32 wId = 0;
	std::string equiped = "";
	U32 mId = 0;

	// We start from "save"

	GameSingleton::loader.getAttribute("name", GameSingleton::name);
	GameSingleton::loader.getAttribute("color", color);
	GameSingleton::color = oe::fromString<oe::Color>(color);

	GameSingleton::loader.readNode("stats");
	GameSingleton::loader.getAttribute("level", level);
	GameSingleton::loader.getAttribute("exp", exp);
	GameSingleton::loader.getAttribute("points", points);
	GameSingleton::loader.getAttribute("battery", battery);
	GameSingleton::loader.getAttribute("batteryB", batteryB);
	GameSingleton::loader.getAttribute("speedB", speedB);
	GameSingleton::loader.getAttribute("strengthB", strengthB);
	GameSingleton::loader.closeNode();
	GameSingleton::loader.readNode("map");
	GameSingleton::loader.getAttribute("id", mapId);
	GameSingleton::loader.getAttribute("previous", previousId);
	GameSingleton::loader.getAttribute(std::string("spawn"), spawn);
	GameSingleton::loader.getAttribute(std::string("position"), pos);
	GameSingleton::loader.closeNode();

	GameSingleton::loader.readNode("weapons");
	if (GameSingleton::loader.readNode("weapon"))
	{
		GameSingleton::loader.getAttribute("id", wId);
		GameSingleton::loader.getAttribute("equiped", equiped);

		if (wId > 0 && wId < 50)
		{
			static const std::string ts = "true";
			GameSingleton::player->addWeapon(wId);
			if (equiped == ts && GameSingleton::player->hasWeapon(wId))
			{
				GameSingleton::player->setWeapon(wId);
			}
		}

		wId = 0;
		if (equiped.size() > 0)
		{
			equiped.clear();
		}

		while (GameSingleton::loader.nextSibling("weapon"))
		{
			GameSingleton::loader.getAttribute("id", wId);
			GameSingleton::loader.getAttribute("equiped", equiped);

			if (wId > 0 && wId < 50)
			{
				static const std::string ts = "true";
				GameSingleton::player->addWeapon(wId);
				if (equiped == ts && GameSingleton::player->hasWeapon(wId))
				{
					GameSingleton::player->setWeapon(wId);
				}
			}

			wId = 0;
			if (equiped.size() > 0)
			{
				equiped.clear();
			}
		}
		GameSingleton::loader.closeNode();
	}
	GameSingleton::loader.closeNode();


	GameSingleton::visited.clear();
	GameSingleton::loader.readNode("visited");
	if (GameSingleton::loader.readNode("map"))
	{
		GameSingleton::loader.getAttribute("id", mId);
		GameSingleton::visited.push_back(mId);

		while (GameSingleton::loader.nextSibling("map"))
		{
			GameSingleton::loader.getAttribute("id", mId);
			GameSingleton::visited.push_back(mId);
		}
		GameSingleton::loader.closeNode();
	}
	GameSingleton::loader.closeNode();

	// LOAD

	GameSingleton::player->setColor(GameSingleton::color);
	GameSingleton::player->setLevel(level);
	GameSingleton::player->setExperience(exp);
	GameSingleton::player->setPoints(points);
	if (battery == 0)
	{
		GameSingleton::player->charge();
	}
	else
	{
		GameSingleton::player->setBattery((F32)battery);
	}
	GameSingleton::player->setBatteryBonus((F32)batteryB);
	GameSingleton::player->setSpeedBonus((F32)speedB);
	GameSingleton::player->setStrengthBonus(strengthB);
	GameSingleton::player->setPosition(oe::fromString<oe::Vector2>(pos));
	GameSingleton::player->updateView();

	// Load after to ensure the chest will be opened if necesary
	GameSingleton::map->load(mapId, oe::fromString<oe::Vector2>(spawn), previousId);
}

void GameState::save()
{
	oe::ParserXml xml;
	xml.newFile();

	auto& node = xml.mCurrentNode;

	node = node.append_child("save");
	node.append_attribute("version") = std::string(SAVE_VERSION).c_str();
	node.append_attribute("name") = GameSingleton::name.c_str();
	node.append_attribute("color") = GameSingleton::color.toString().c_str();
	node.append_attribute("date") = oe::Date().toString().c_str();

	node = node.append_child("stats");
	node.append_attribute("level") = GameSingleton::player->getLevel();
	node.append_attribute("exp") = GameSingleton::player->getExperience();
	node.append_attribute("points") = GameSingleton::player->getPoints();
	node.append_attribute("battery") = GameSingleton::player->getBattery();
	node.append_attribute("batteryB") = GameSingleton::player->getBatteryBonus();
	node.append_attribute("speedB") = GameSingleton::player->getSpeedBonus();
	node.append_attribute("strengthB") = GameSingleton::player->getStrengthBonus();
	node = node.parent();

	node = node.append_child("map");
	node.append_attribute("id") = GameSingleton::map->getMapId();
	node.append_attribute("previous") = GameSingleton::map->getPreviousMapId();
	node.append_attribute("spawn") = oe::toString(GameSingleton::map->getRespawnPoint()).c_str();
	node.append_attribute("position") = oe::toString(GameSingleton::player->getPosition()).c_str();
	node = node.parent();

	node = node.append_child("weapons");
	U32 size = GameSingleton::player->getWeapons().size();
	for (U32 i = 0; i < size; i++)
	{
		node = node.append_child("weapon");
		node.append_attribute("id") = GameSingleton::player->getWeapons()[i];
		if (GameSingleton::player->getWeapon() == GameSingleton::player->getWeapons()[i])
		{
			node.append_attribute("equiped") = "true";
		}
		node = node.parent();
	}
	node = node.parent();

	node = node.append_child("visited");
	size = GameSingleton::visited.size();
	for (U32 i = 0; i < size; i++)
	{
		node.append_child("map").append_attribute("id") = GameSingleton::visited[i];
	}
	node = node.parent();

	xml.saveToFile("Assets/save.xml");


	// TODO : Post-LD Debug
	/*
	if (xml.createChild("save"))
	{
		printf("XW a\n");

		xml.setAttribute("version", std::string(SAVE_VERSION));
		xml.setAttribute("name", GameSingleton::name);
		xml.setAttribute("color", GameSingleton::color.toString());
		xml.setAttribute("date", oe::Date().toString());

		if (xml.createChild("map"))
		{
			printf("XW b\n");

			xml.setAttribute("id", oe::toString(GameSingleton::map->getMapId()));
			xml.setAttribute("spawn", oe::toString(GameSingleton::map->getRespawnPoint()));
			xml.setAttribute("position", oe::toString(GameSingleton::player->getPosition()));
			xml.closeNode();

			if (xml.createChild("stats"))
			{
				printf("XW c\n");

				xml.setAttribute("level", oe::toString(GameSingleton::player->getLevel()));
				xml.setAttribute("exp", oe::toString(GameSingleton::player->getExperience()));
				xml.setAttribute("points", oe::toString(GameSingleton::player->getPoints()));
				xml.setAttribute("battery", oe::toString(GameSingleton::player->getBattery()));
				xml.setAttribute("batteryB", oe::toString(GameSingleton::player->getBatteryBonus()));
				xml.setAttribute("speedB", oe::toString(GameSingleton::player->getSpeedBonus()));
				xml.setAttribute("strengthB", oe::toString(GameSingleton::player->getStrengthBonus()));
				xml.closeNode();

				if (xml.createChild("weapons"))
				{
					printf("XW d\n");

					U32 size = GameSingleton::player->getWeapons().size();
					for (U32 i = 0; i < size; i++)
					{
						if (xml.createChild("weapon"))
						{
							xml.setAttribute("id", oe::toString(GameSingleton::player->getWeapons()[i]));
							xml.closeNode();
						}
					}
					xml.closeNode();
				}
			}
		}
		xml.closeNode();
	}
	xml.saveToFile("Assets/save.xml");
	*/
}
