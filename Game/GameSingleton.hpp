#ifndef GAMESINGLETON_HPP
#define GAMESINGLETON_HPP

#include "../Engine/Graphics/Tileset.hpp"
#include "../Engine/Graphics/SFMLResources.hpp"
#include "../Engine/Core/EntityHandle.hpp"

#include "GameMap.hpp"

class GameSingleton
{
	public:
		// Tileset
		static oe::Tileset tileset;
		static void loadTileset();

		// Fonts
		static oe::ResourceId sansationFont;

		// Sounds
		static oe::ResourceId actionSound;

		// Resources
		static oe::ResourceId objectsTexture;

		// Map
		static GameMap* map;

		// Clear the singleton before a new game
		static void clear();
};

#endif // GAMESINGLETON_HPP
