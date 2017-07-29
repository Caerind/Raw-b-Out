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

	mBarPlayerLevel.setSize(WINSIZEX / 2 - 52, 20);
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
}

bool GameState::handleEvent(const sf::Event& event)
{
	OE_PROFILE_FUNCTION("GameState::handleEvent");

	mWorld.handleEvent(event);

	zoomView(event);

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == GameSingleton::pickupInput.getButton())
	{
		oe::Vector2 p(getWindow().getCursorPositionView(getView()));
		oe::Vector2i c(oe::MapUtility::worldToCoords(p, oe::MapUtility::Orthogonal, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY)));
		GameSingleton::map->openChest(c);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F7)
	{
		getWindow().screenshot();
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
	{
		GameSingleton::player->setWeapon(1);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X)
	{
		GameSingleton::player->setWeapon(2);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
	{
		GameSingleton::player->setWeapon(3);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V)
	{
		GameSingleton::player->setWeapon(4);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
	{
		GameSingleton::player->setWeapon(5);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
	{
		GameSingleton::player->setWeapon(6);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Comma)
	{
		GameSingleton::player->setWeapon(7);
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
	target.draw(mBarPlayerLevel);
	target.draw(mPlayerLevelText);
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
