#ifndef GAMESINGLETON_HPP
#define GAMESINGLETON_HPP

#include "../Engine/Graphics/Animation.hpp"
#include "../Engine/Graphics/Tileset.hpp"
#include "../Engine/Graphics/SFMLResources.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/Systems/ActionSystem.hpp"
#include "../Engine/Core/EntityQuery.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "GameMap.hpp"
#include "RobotPlayer.hpp"

struct WeaponData
{
	WeaponId id;
	std::string name;
	F32 cool;
	U32 stre;
	U32 proj;
};

class GameSingleton
{
	public:
		// Tileset
		static oe::Tileset tileset;
		static void loadTileset();

		// Resources
		static oe::ResourceId minikillerTexture;
		static oe::ResourceId killerTexture;
		static oe::ResourceId projectilesTexture;
		static oe::ResourceId sansationFont;
		static oe::ResourceId actionSound;

		// Map & Player
		static oe::EntityHandle mapHandle;
		static GameMap* map;
		static oe::EntityHandle playerHandle;
		static RobotPlayer* player;

		// Inputs
		static oe::ActionInputKey up;
		static oe::ActionInputKey left;
		static oe::ActionInputKey down;
		static oe::ActionInputKey right;
		static oe::ActionInputMouse shootInput;
		static oe::ActionInputMouse pickupInput;
		static void loadInputs();

		// Animations
		static oe::Animation rightMiniKillerMove;
		static oe::Animation leftMiniKillerMove;
		static oe::Animation rightMiniKillerIdle;
		static oe::Animation leftMiniKillerIdle;
		static oe::Animation rightKillerMove;
		static oe::Animation leftKillerMove;
		static oe::Animation rightKillerIdle;
		static oe::Animation leftKillerIdle;
		static oe::Animation rightMegaKillerMove;
		static oe::Animation leftMegaKillerMove;
		static oe::Animation rightMegaKillerIdle;
		static oe::Animation leftMegaKillerIdle;
		static void loadAnimations();

		// Robots
		static oe::EntityQuery rQuery;
		static oe::EntityQuery rpQuery;
		static oe::EntityQuery repQuery;
		static void loadQueries();

		// Weapons
		static std::map<WeaponId, WeaponData> weaponData;
		static void loadWeapons();

		// Clear the singleton before a new game
		static void clear();

};

#endif // GAMESINGLETON_HPP
