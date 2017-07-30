#include "GameSingleton.hpp"

#include "GameConfig.hpp" // Used to load the tileset

oe::Tileset GameSingleton::tileset;
oe::ResourceId GameSingleton::minikillerTexture;
oe::ResourceId GameSingleton::killerTexture;
oe::ResourceId GameSingleton::projectilesTexture;
oe::ResourceId GameSingleton::guiTexture;
oe::ResourceId GameSingleton::weaponsTexture;
oe::ResourceId GameSingleton::sansationFont;
oe::ResourceId GameSingleton::actionSound;
oe::EntityHandle GameSingleton::mapHandle;
GameMap* GameSingleton::map;
oe::EntityHandle GameSingleton::playerHandle;
RobotPlayer* GameSingleton::player;
std::string GameSingleton::name;
oe::ActionInputKey GameSingleton::up;
oe::ActionInputKey GameSingleton::left;
oe::ActionInputKey GameSingleton::down;
oe::ActionInputKey GameSingleton::right;
oe::ActionInputMouse GameSingleton::shootInput;
oe::ActionInputMouse GameSingleton::pickupInput;
oe::Animation GameSingleton::rightMiniKillerMove;
oe::Animation GameSingleton::leftMiniKillerMove;
oe::Animation GameSingleton::rightMiniKillerIdle;
oe::Animation GameSingleton::leftMiniKillerIdle;
oe::Animation GameSingleton::rightKillerMove;
oe::Animation GameSingleton::leftKillerMove;
oe::Animation GameSingleton::rightKillerIdle;
oe::Animation GameSingleton::leftKillerIdle;
oe::Animation GameSingleton::rightMegaKillerMove;
oe::Animation GameSingleton::leftMegaKillerMove;
oe::Animation GameSingleton::rightMegaKillerIdle;
oe::Animation GameSingleton::leftMegaKillerIdle;
oe::EntityQuery GameSingleton::rQuery;
oe::EntityQuery GameSingleton::rpQuery;
oe::EntityQuery GameSingleton::repQuery;
std::map<WeaponId, WeaponData> GameSingleton::weaponData;

void GameSingleton::loadTileset()
{
	tileset.setImageSource(TILESETSOURCE);
	tileset.setTileSize(oe::Vector2i(TILESETSIZEX, TILESETSIZEY));
	tileset.setTileCount(TILESETCOUNT);
	tileset.setColumns(TILESETCOLUMNS);
	tileset.getTexture(); // Used to load the texture now
}

void GameSingleton::loadInputs()
{
	up.setKey(sf::Keyboard::Z);
	up.setType(oe::ActionType::Hold);
	left.setKey(sf::Keyboard::Q);
	left.setType(oe::ActionType::Hold);
	down.setKey(sf::Keyboard::S);
	down.setType(oe::ActionType::Hold);
	right.setKey(sf::Keyboard::D);
	right.setType(oe::ActionType::Hold);
	shootInput.setButton(sf::Mouse::Left);
	shootInput.setType(oe::ActionType::Pressed);
	shootInput.setButton(sf::Mouse::Right);
	shootInput.setType(oe::ActionType::Pressed);
}

void GameSingleton::loadAnimations()
{
	// MiniKiller
	rightMiniKillerMove.addFrame(minikillerTexture, oe::Rect(0, 0, 64, 64), oe::seconds(0.15f));
	rightMiniKillerMove.addFrame(minikillerTexture, oe::Rect(64, 0, 64, 64), oe::seconds(0.15f));
	rightMiniKillerMove.addFrame(minikillerTexture, oe::Rect(128, 0, 64, 64), oe::seconds(0.15f));
	rightMiniKillerMove.addFrame(minikillerTexture, oe::Rect(192, 0, 64, 64), oe::seconds(0.15f));
	leftMiniKillerMove.addFrame(minikillerTexture, oe::Rect(0, 64, 64, 64), oe::seconds(0.15f));
	leftMiniKillerMove.addFrame(minikillerTexture, oe::Rect(64, 64, 64, 64), oe::seconds(0.15f));
	leftMiniKillerMove.addFrame(minikillerTexture, oe::Rect(128, 64, 64, 64), oe::seconds(0.15f));
	leftMiniKillerMove.addFrame(minikillerTexture, oe::Rect(192, 64, 64, 64), oe::seconds(0.15f));
	rightMiniKillerIdle.addFrame(minikillerTexture, oe::Rect(0, 0, 64, 64), oe::seconds(2.0f));
	leftMiniKillerIdle.addFrame(minikillerTexture, oe::Rect(0, 64, 64, 64), oe::seconds(2.0f));

	// Killer
	rightKillerMove.addFrame(killerTexture, oe::Rect(0, 0, 64, 64), oe::seconds(0.2f));
	rightKillerMove.addFrame(killerTexture, oe::Rect(64, 0, 64, 64), oe::seconds(0.2f));
	rightKillerMove.addFrame(killerTexture, oe::Rect(128, 0, 64, 64), oe::seconds(0.2f));
	rightKillerMove.addFrame(killerTexture, oe::Rect(192, 0, 64, 64), oe::seconds(0.2f));
	leftKillerMove.addFrame(killerTexture, oe::Rect(0, 64, 64, 64), oe::seconds(0.2f));
	leftKillerMove.addFrame(killerTexture, oe::Rect(64, 64, 64, 64), oe::seconds(0.2f));
	leftKillerMove.addFrame(killerTexture, oe::Rect(128, 64, 64, 64), oe::seconds(0.2f));
	leftKillerMove.addFrame(killerTexture, oe::Rect(192, 64, 64, 64), oe::seconds(0.2f));
	rightKillerIdle.addFrame(killerTexture, oe::Rect(0, 0, 64, 64), oe::seconds(2.0f));
	leftKillerIdle.addFrame(killerTexture, oe::Rect(0, 64, 64, 64), oe::seconds(2.0f));

	// MegaKiller
}
void GameSingleton::loadQueries()
{
	rQuery.setSelector([](oe::Entity* entity) -> bool
	{
		return fast_dynamic_cast<Robot*>(entity) != nullptr;
	});

	rpQuery.setSelector([](oe::Entity* entity) -> bool
	{
		if (fast_dynamic_cast<Robot*>(entity) != nullptr)
		{
			return true;
		}
		else
		{
			return fast_dynamic_cast<Projectile*>(entity) != nullptr;
		}
	});

	repQuery.setSelector([](oe::Entity* entity) -> bool
	{
		if (entity->getName() != "player" && fast_dynamic_cast<Robot*>(entity) != nullptr)
		{
			return true;
		}
		else
		{
			return fast_dynamic_cast<Projectile*>(entity) != nullptr;
		}
	});
}

void GameSingleton::loadWeapons()
{
	oe::ParserXml xml;
	if (xml.loadFromFile("../Assets/weapons.xml"))
	{
		if (xml.readNode("weapon"))
		{
			U32 id = 0;
			xml.getAttribute("id", id);
			weaponData[id].id = id;
			xml.getAttribute("name", weaponData[id].name);
			xml.getAttribute("cool", weaponData[id].cool);
			xml.getAttribute("stre", weaponData[id].stre);
			xml.getAttribute("proj", weaponData[id].proj);
			while (xml.nextSibling("weapon"))
			{
				xml.getAttribute("id", id);
				weaponData[id].id = id;
				xml.getAttribute("name", weaponData[id].name);
				xml.getAttribute("cool", weaponData[id].cool);
				xml.getAttribute("stre", weaponData[id].stre);
				xml.getAttribute("proj", weaponData[id].proj);
			}
		}
		xml.closeNode();
	}
}

void GameSingleton::clear()
{
	map = nullptr;
	player = nullptr;
}
