#include "GameMap.hpp"

#include "GameSingleton.hpp" // Used to get tileset
#include "GameConfig.hpp" // Used to get data

#include "../Engine/System/Compression.hpp"

GameMap::GameMap(oe::EntityManager& manager)
	: oe::Entity(manager)
	, mLayer(*this)
{
	setPosition(0, 0);
	setPositionZ(-100);

	mPreviousMapId = 0;
	mMapId = 0;
}

oe::TileId GameMap::getTileId(const oe::Vector2i& coords)
{
	return mLayer.getTileId(coords);
}

void GameMap::setTileId(const oe::Vector2i& coords, oe::TileId id)
{
	mLayer.setTileId(coords, id);
}

void GameMap::load(U32 mapId, const oe::Vector2& spawnPoint)
{
	// Clear layer ?
	mInfos.clear();
	mSpawners.clear();
	mChests.clear(); // TODO : Save opened chests
	mTeleporters.clear();
	mChargers.clear();
	mCurrentInfo = nullptr;

	mPreviousMapId = mMapId;
	mMapId = mapId;

	setSpawnPoint(spawnPoint);

	oe::ParserXml xml;
	if (!xml.loadFromFile(MAPPATH + oe::toString(mMapId) + ".tmx"))
	{
		printf("Cant read map");
		return;
	}

	// read map
	if (!xml.readNode("map"))
	{
		printf("Cant read map");
		return;
	}
	oe::Vector2i size;
	xml.getAttribute("width", size.x);
	xml.getAttribute("height", size.y);

	// read layer
	if (xml.readNode("layer"))
	{
		createLayer(size);
		updateAABB();
		readLayer(xml);
		xml.closeNode();
	}

	// read objects
	if (xml.readNode("objectgroup"))
	{
		if (xml.readNode("object"))
		{
			readObject(xml);
			while (xml.nextSibling("object"))
			{
				readObject(xml);
			}
			xml.closeNode();
		}
		xml.closeNode();
	}
}

U32 GameMap::getMapId() const
{
	return mMapId;
}

U32 GameMap::getPreviousMapId() const
{
	return mPreviousMapId;
}

void GameMap::setSpawnPoint(const oe::Vector2& point)
{
	mSpawnPoint = point;
}

const oe::Vector2& GameMap::getSpawnPoint() const
{
	return mSpawnPoint;
}

oe::LayerComponent& GameMap::getLayer()
{
	return mLayer;
}

void GameMap::setSize(const oe::Vector2i& size)
{
	mLayer.setSize(size);
}

const oe::Vector2i& GameMap::getSize() const
{
	return mLayer.getSize();
}

void GameMap::update(oe::Time dt)
{
	// Infos
	mCurrentInfo = nullptr;
	for (U32 i = 0; i < mInfos.size(); i++)
	{
		if (mInfos[i].update())
		{
			mCurrentInfo = &mInfos[i];
		}
	}

	// Chargers
	for (U32 i = 0; i < mChargers.size(); i++)
	{
		const oe::Vector2 delta = GameSingleton::player->getPosition() - mChargers[i];
		const F32 d = delta.getLength();
		if (d <= CHARGER_DISTANCE)
		{
			GameSingleton::player->setBattery(GameSingleton::player->getBatteryMaxWithBonus());
		}
	}

	// Spawners
	for (U32 i = 0; i < mSpawners.size(); i++)
	{
		mSpawners[i].update();
	}

	// Teleporters
	for (U32 i = 0; i < mTeleporters.size(); i++)
	{
		mTeleporters[i].update();
	}
}

bool GameMap::collide(const oe::Vector2i& coords)
{
	ASSERT(coords.x >= 0 && coords.y >= 0 && coords.x < mLayer.getSize().x && coords.y < mLayer.getSize().y);
	return mCollisions[coords.x + coords.y * mLayer.getSize().x];
}

Info* GameMap::getCurrentInfo()
{
	return mCurrentInfo;
}

void GameMap::openChest(const oe::Vector2i& coords)
{
	for (U32 i = 0; i < mChests.size(); i++)
	{
		if (coords == mChests[i].getPosition() && !mChests[i].isOpen())
		{
			mChests[i].setOpen(true);
		}
	}
}

void GameMap::createLayer(const oe::Vector2i& size)
{
	mLayer.create(&GameSingleton::tileset, size, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY), oe::MapUtility::Orthogonal);
	U32 max = size.x * size.y;
	mCollisions.resize(max);
	for (U32 i = 0; i < max; i++)
	{
		mCollisions[i] = false;
	}
}

void GameMap::readLayer(oe::ParserXml& parser)
{
	if (parser.readNode("data"))
	{
		std::string code;
		parser.getValue(code);
		oe::Vector2i size = mLayer.getSize();
		oe::Vector2i coords;
		std::string data;
		std::stringstream ss;
		ss << code;
		ss >> data;
		if (!oe::Compression::decompress64(data))
		{
			return;
		}
		std::vector<U8> byteVector;
		byteVector.reserve(size.x * size.y * 4);
		for (std::string::iterator i = data.begin(); i != data.end(); ++i)
		{
			byteVector.push_back(*i);
		}
		mLayer.ensureUpdateGeometry();
		for (U32 i = 0; i < byteVector.size() - 3; i += 4)
		{
			oe::TileId gid = byteVector[i] | byteVector[i + 1] << 8 | byteVector[i + 2] << 16 | byteVector[i + 3] << 24;

			mLayer.setTileId(coords, gid);

			switch (gid)
			{
				case TILE_WALL:
				case TILE_FAKEWALL:
				case TILE_WALL1:
				case TILE_WALL2:
				case TILE_WALL3:
				case TILE_WALL4:
				case TILE_WALL5:
				case TILE_WALL6:
				case TILE_WALL7:
				case TILE_WALL8:
					mCollisions[coords.x + coords.y * size.x] = true; break;
				case TILE_CHEST:
					mCollisions[coords.x + coords.y * size.x] = true;
					mChests.push_back(Chest(coords, 0));
					break;
				case TILE_BATTERY: mChargers.push_back(oe::Vector2(coords.x * 64 + 32.f, coords.y * 64 + 32.f)); break;
				case TILE_ENEMY1: mSpawners.push_back(Spawner(getManager(), oe::Vector2(coords.x * 64 + 32.f, coords.y * 64 + 32.f), 1)); break;
				case TILE_ENEMY2: mSpawners.push_back(Spawner(getManager(), oe::Vector2(coords.x * 64 + 32.f, coords.y * 64 + 32.f), 2)); break;
				case TILE_ENEMY3: mSpawners.push_back(Spawner(getManager(), oe::Vector2(coords.x * 64 + 32.f, coords.y * 64 + 32.f), 3)); break;
				default: break;
			}

			coords.x = (coords.x + 1) % size.x;
			if (coords.x == 0)
			{
				coords.y++;
			}
		}
		parser.closeNode();
	}
}

void GameMap::readObject(oe::ParserXml& parser)
{
	std::string name;
	parser.getAttribute("name", name);
	if (name == "I") // Infos
	{
		readInfo(parser);
	}
	if (name == "C") // Chest
	{
		readChest(parser);
	}
	if (name == "T") // Teleporter
	{
		readTeleporter(parser);
	}
}

void GameMap::readInfo(oe::ParserXml& parser)
{
	mInfos.push_back(Info());

	U32 id = 0;
	oe::Vector2 pos;
	std::string str = "Empty string";

	parser.getAttribute("id", id);
	parser.getAttribute("x", pos.x);
	parser.getAttribute("y", pos.y);
	if (parser.readNode("properties"))
	{
		if (parser.readNode("property"))
		{
			parser.getValue(str);
			parser.closeNode();
		}
		parser.closeNode();
	}

	printf("Info %d %s %f %f\n", id, str.c_str(), pos.x, pos.y);

	mInfos.back().setId(id);
	mInfos.back().setPosition(pos);
	mInfos.back().setString(str);

}

void GameMap::readChest(oe::ParserXml& parser)
{
	U32 weaponId = 0;
	oe::Vector2 pos;
	parser.getAttribute("x", pos.x);
	parser.getAttribute("y", pos.y);

	if (parser.readNode("properties"))
	{
		if (parser.readNode("property"))
		{
			oe::Vector2i coords = oe::MapUtility::worldToCoords(pos, oe::MapUtility::Orthogonal, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY));
			parser.getAttribute("value", weaponId);
			for (U32 i = 0; i < mChests.size(); i++)
			{
				if (mChests[i].getPosition() == coords)
				{
					mChests[i].setWeapon(weaponId);
				}
			}
			parser.closeNode();
		}
		parser.closeNode();
	}

	printf("Chest %f %f %d\n", pos.x, pos.y, weaponId);
}

void GameMap::readTeleporter(oe::ParserXml& parser)
{
	oe::Vector2 pos, target;
	U32 mapId;
	std::string pname;

	parser.getAttribute("x", pos.x);
	parser.getAttribute("y", pos.y);
	if (parser.readNode("properties"))
	{
		if (parser.readNode("property"))
		{
			parser.getAttribute("name", pname);
			if (pname == "map")
			{
				parser.getAttribute("value", mapId);
			}
			if (pname == "x")
			{
				parser.getAttribute("value", target.x);
			}
			if (pname == "y")
			{
				parser.getAttribute("value", target.y);
			}

			while (parser.nextSibling("property"))
			{
				parser.getAttribute("name", pname);
				if (pname == "map")
				{
					parser.getAttribute("value", mapId);
				}
				if (pname == "x")
				{
					parser.getAttribute("value", target.x);
				}
				if (pname == "y")
				{
					parser.getAttribute("value", target.y);
				}
			}

			parser.closeNode();
		}
		parser.closeNode();
	}

	mTeleporters.push_back(Teleporter(pos, mapId, target));

	printf("Teleporter %f %f %d %f %f\n", pos.x, pos.y, mapId, target.x, target.y);
}
