#ifndef GAMESINGLETON_HPP
#define GAMESINGLETON_HPP

#include "../Engine/Graphics/Animation.hpp"
#include "../Engine/Graphics/Tileset.hpp"
#include "../Engine/Graphics/SFMLResources.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/Systems/ActionSystem.hpp"
#include "../Engine/Core/EntityQuery.hpp"
#include "../Engine/System/ParserXml.hpp"

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

		// Textures
		static oe::ResourceId minikillerTexture;
		static oe::ResourceId killerTexture;
		static oe::ResourceId projectilesTexture;
		static oe::ResourceId guiTexture;
		static oe::ResourceId weaponsTexture;
		static oe::ResourceId particleTexture;
		static oe::ResourceId screenTexture;

		// Font
		static oe::ResourceId sansationFont;

		// Sounds
		static oe::ResourceId ammoSound;
		static oe::ResourceId buttonSound;
		static oe::ResourceId chargeSound;
		static oe::ResourceId chestSound;
		static oe::ResourceId clickSound;
		static oe::ResourceId damageSound;
		static oe::ResourceId dieSound;
		static oe::ResourceId errorSound;
		static oe::ResourceId explosionSound;
		static oe::ResourceId infoSound;
		static oe::ResourceId laserSound;
		static oe::ResourceId levelSound;
		static oe::ResourceId plasmaSound;
		static oe::ResourceId teleportSound;
		static oe::ResourceId ultimeSound;
		static oe::ResourceId wallSound;

		// Musics
		static oe::ResourceId mainMusic;
		static oe::ResourceId fightMusic;
		static bool playingMainMusic;

		static oe::Application* application;

		// Resources
		static void loadResources(oe::Application& application);
		static void loadResources2();

		// Map & Player
		static oe::EntityHandle mapHandle;
		static GameMap* map;
		static oe::EntityHandle playerHandle;
		static RobotPlayer* player;
		static std::string name;
		static oe::Color color;

		// Inputs
		static oe::ActionInputKey up;
		static oe::ActionInputKey left;
		static oe::ActionInputKey down;
		static oe::ActionInputKey right;
		static oe::ActionInputMouse shootInput;
		static oe::ActionInputMouse pickupInput;
		static void loadInputs();

		// Robots
		static oe::EntityQuery rQuery;
		static oe::EntityQuery rpQuery;
		static oe::EntityQuery repQuery;
		static void loadQueries();

		// Weapons
		static std::map<WeaponId, WeaponData> weaponData;
		static void loadWeapons();
		static sf::IntRect getTextureRectFromWeapon(WeaponId id);

		// Clear the singleton before a new game
		static void clear();

		// Loader
		static oe::ParserXml loader;

		// Sound
		static void playSound(oe::ResourceId sound);
		static void click();

};

#endif // GAMESINGLETON_HPP
