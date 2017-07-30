#include "GameState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"
#include "PostState.hpp" // Used to switch to

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

	mInfoText.setCharacterSize(20);
	mInfoText.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mInfoText.setFillColor(sf::Color::White);
	mInfoText.setOutlineColor(sf::Color::Black);
	mInfoText.setOutlineThickness(1.2f);
	mInfoText.setPosition(20.0f, 20.0f);
	mInfoText.setString("");
	mCurrentInfo = 0;

	GameSingleton::mapHandle = mWorld.getEntityManager().createEntity<GameMap>();
	GameSingleton::map = GameSingleton::mapHandle.getAs<GameMap>();
	GameSingleton::map->setName("map");
	GameSingleton::map->load(0, oe::Vector2(200.0f, 200.0f));

	GameSingleton::playerHandle = mWorld.getEntityManager().createEntity<RobotPlayer>();
	GameSingleton::player = GameSingleton::playerHandle.getAs<RobotPlayer>();
	GameSingleton::player->setName("player");
	GameSingleton::player->setPosition(oe::Vector2(200.0f, 200.0f));
	GameSingleton::player->updateView();

	mBarPlayerLevel.setSize(WINSIZEX / 2 + 20, 20);
	mBarPlayerLevel.setPosition(52, WINSIZEY - 40);
	mBarPlayerLevel.setBackColor(sf::Color(153, 217, 234));
	mBarPlayerLevel.setBarColor(sf::Color(0, 162, 232));
	mBarPlayerLevel.setOutlineColor(sf::Color::Black);
	mBarPlayerLevel.setOutlineThickness(1.2f);
	mBarPlayerLevel.setValueMax((F32)GameSingleton::player->getExperienceMax());
	mBarPlayerLevel.setValue((F32)GameSingleton::player->getExperience());

	// TODO : Modernize colors
	mBarPlayerBattery.setSize(WINSIZEX, 20);
	mBarPlayerBattery.setPosition(0, WINSIZEY - 20);
	mBarPlayerBattery.setBackColor(sf::Color::Red);
	mBarPlayerBattery.setBarColor(sf::Color::Green);
	mBarPlayerBattery.setOutlineColor(sf::Color::Black);
	mBarPlayerBattery.setOutlineThickness(1.2f);
	mBarPlayerBattery.setValueMax(GameSingleton::player->getBatteryMax());
	mBarPlayerBattery.setValue(GameSingleton::player->getBattery());

	mPlayerLevelText.setCharacterSize(20);
	mPlayerLevelText.setFont(getApplication().getFonts().get(GameSingleton::sansationFont));
	mPlayerLevelText.setFillColor(sf::Color::White);
	mPlayerLevelText.setOutlineColor(sf::Color::Black);
	mPlayerLevelText.setOutlineThickness(1.2f);
	mPlayerLevelText.setPosition(26.0f, WINSIZEY - 35);
	mPlayerLevelText.setString("");
	mPlayerLevelText.setOrigin(mPlayerLevelText.getGlobalBounds().width * 0.5f, mPlayerLevelText.getGlobalBounds().height * 0.5f);

	mButtonR.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
	mButtonR.setPosition(WINSIZEX - 288, WINSIZEY - 20 - 96);
	mButtonI.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
	mButtonI.setPosition(WINSIZEX - 192, WINSIZEY - 20 - 96);
	mButtonO.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
	mButtonO.setPosition(WINSIZEX - 96, WINSIZEY - 20 - 96);

	mScreen.loadFromFile("../Assets/screen.png");
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

		//zoomView(event);

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == GameSingleton::pickupInput.getButton())
		{
			oe::Vector2 p(getWindow().getCursorPositionView(getView()));
			oe::Vector2i c(oe::MapUtility::worldToCoords(p, oe::MapUtility::Orthogonal, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY)));
			GameSingleton::map->openChest(c);
		}
	}

	// Screenshot
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F7)
	{
		getWindow().screenshot();
	}

	// Show/Hide Profiler
	#ifdef OE_IMGUI	
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F6)
	{
		if (mProfiler.isVisible())
		{
			mProfiler.hide();
			mDataViewer.hide();
		}
		else
		{
			mProfiler.show();
			mDataViewer.show();
		}
	}
	#endif

	return false;
}

bool GameState::update(oe::Time dt)
{
	OE_PROFILE_FUNCTION("GameState::update");

	mDuration += dt;

	if (mCurrentPopUp == 0)
	{
		mWorld.update(dt);

		oe::Time gameDt = mWorld.getUpdateTime();

		mBarPlayerLevel.setValueMax((F32)GameSingleton::player->getExperienceMax());
		mBarPlayerLevel.setValue((F32)GameSingleton::player->getExperience());
		mBarPlayerBattery.setValue(GameSingleton::player->getBattery());
		mPlayerLevelText.setString(oe::toString(GameSingleton::player->getLevel()));
		mPlayerLevelText.setOrigin(mPlayerLevelText.getGlobalBounds().width * 0.5f, mPlayerLevelText.getGlobalBounds().height * 0.5f);

		Info* info = GameSingleton::map->getCurrentInfo();
		if (info != nullptr)
		{
			U32 current = info->getId();
			if (mCurrentInfo != current)
			{
				mCurrentInfo = current;
				mInfoText.setString(info->getString());
			}
		}
		else
		{
			mCurrentInfo = 0;
			mInfoText.setString("");
		}
	}

	#ifdef OE_IMGUI
	oe::Vector2 p(getWindow().getCursorPositionView(getView()));
	oe::Vector2i c(oe::MapUtility::worldToCoords(p, oe::MapUtility::Orthogonal, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY)));

	getApplication().getData().setData("MousePos", oe::toString(p));
	getApplication().getData().setData("MouseCoords", oe::toString(c));
	getApplication().getData().setData("MouseTile", oe::toString(GameSingleton::map->getTileId(c)));

	getApplication().getData().setData("WeaponId", oe::toString(GameSingleton::player->getWeapon()));

	mProfiler.draw();
	mDataViewer.draw();
	#endif

	return false;
}

void GameState::render(sf::RenderTarget& target)
{
	OE_PROFILE_FUNCTION("GameState::render");

	mWorld.render(target);

	target.draw(mInfoText);

	// Draw PopUp
	if (mCurrentPopUp != 0 && mPopUp != nullptr)
	{
		target.draw(*mPopUp);
	}

	target.draw(mBarPlayerLevel);
	target.draw(mPlayerLevelText);
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

void GameState::zoomView(const sf::Event& event)
{
	if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		oe::Vector2 wSize = getWindow().getSize();
		oe::View& view = getView();
		if (event.mouseWheelScroll.delta < 1)
		{
			if (view.getZoom() < 3.0f)
			{
				view.zoom(2.0f);
			}
		}
		else
		{
			if (view.getZoom() > 1.5f)
			{
				view.zoom(0.5f);
			}
		}
	}
}

void GameState::popUpEvent(const sf::Event& event)
{
	sf::Vector2f mpos((F32)event.mouseButton.x, (F32)event.mouseButton.y); // WARNING : Use only if type = mouseButton

	static const sf::FloatRect closeRect(WINSIZEX - 960, WINSIZEY - 20 - 600, 40.0f, 40.0f);

	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && mCurrentPopUp != 0) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && closeRect.contains(mpos) && mCurrentPopUp != 0)) // Clic sur la croix
	{
		if (mPopUp != nullptr)
		{
			delete mPopUp;
		}
		mPopUp = nullptr;
		mCurrentPopUp = 0;
		mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
		mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
		mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
	}
	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mButtonR.getGlobalBounds().contains(mpos)))
	{
		if (mCurrentPopUp == 1)
		{
			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = nullptr;
			mCurrentPopUp = 0;
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
		else
		{
			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = new RobotPopUp(mScreen, getApplication().getTextures().get(GameSingleton::guiTexture), getApplication().getFonts().get(GameSingleton::sansationFont));
			mCurrentPopUp = 1;
			mButtonR.setTextureRect(sf::IntRect(0, 96, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
	}
	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mButtonI.getGlobalBounds().contains(mpos)))
	{
		if (mCurrentPopUp == 2)
		{
			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = nullptr;
			mCurrentPopUp = 0;
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
		else
		{
			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = new InventoryPopUp(mScreen, getApplication().getTextures().get(GameSingleton::guiTexture), getApplication().getFonts().get(GameSingleton::sansationFont), getApplication().getTextures().get(GameSingleton::weaponsTexture));
			mCurrentPopUp = 2;
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 96, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
	}
	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O) || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mButtonO.getGlobalBounds().contains(mpos)))
	{
		if (mCurrentPopUp == 3)
		{
			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = nullptr;
			mCurrentPopUp = 0;
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
		}
		else
		{
			if (mPopUp != nullptr)
			{
				delete mPopUp;
			}
			mPopUp = new OptionsPopUp(mScreen, getApplication().getTextures().get(GameSingleton::guiTexture), getApplication().getAudio());
			mCurrentPopUp = 3;
			mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
			mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
			mButtonO.setTextureRect(sf::IntRect(192, 96, 96, 96));
		}
	}

	if (mCurrentPopUp != 0)
	{
		if (mPopUp != nullptr)
		{
			mPopUp->handleEvent(event);
			if (!mPopUp->isOpen())
			{
				delete mPopUp;
				mPopUp = nullptr;
				mCurrentPopUp = 0;
				mButtonR.setTextureRect(sf::IntRect(0, 0, 96, 96));
				mButtonI.setTextureRect(sf::IntRect(96, 0, 96, 96));
				mButtonO.setTextureRect(sf::IntRect(192, 0, 96, 96));
			}
		}
	}
}
