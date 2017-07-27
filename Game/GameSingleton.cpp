#include "GameSingleton.hpp"

#include "GameConfig.hpp" // Used to load the tileset

oe::Tileset GameSingleton::tileset;
oe::ResourceId GameSingleton::sansationFont;
oe::ResourceId GameSingleton::actionSound;
oe::ResourceId GameSingleton::objectsTexture;
GameMap* GameSingleton::map;

void GameSingleton::loadTileset()
{
	tileset.setImageSource(TILESETSOURCE);
	tileset.setTileSize(oe::Vector2i(TILESETSIZEX, TILESETSIZEY));
	tileset.setTileCount(TILESETCOUNT);
	tileset.setColumns(TILESETCOLUMNS);
	tileset.getTexture(); // Used to load the texture now
}

void GameSingleton::clear()
{
	map = nullptr;
}
