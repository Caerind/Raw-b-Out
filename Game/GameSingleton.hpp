#ifndef GAMESINGLETON_HPP
#define GAMESINGLETON_HPP

#include "../Engine/Graphics/Animation.hpp"
#include "../Engine/Graphics/Tileset.hpp"
#include "../Engine/Graphics/SFMLResources.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/Systems/ActionSystem.hpp"
#include "../Engine/Core/EntityQuery.hpp"
#include "../Engine/System/ParserXml.hpp"
#include "../Engine/Application/AudioSystem.hpp"

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
		static oe::ResourceId shadowTexture;
		static oe::ResourceId headTexture;

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
		static void playSound(oe::ResourceId sound);
		static void click();

		// Musics
		static oe::ResourceId mainMusic;
		static oe::ResourceId fightMusic;
		static bool playingMainMusic;
		static void playMain();
		static void playFight();
		static oe::AudioSystem::MusicPtr musicHandle;
		static U32 enemyFocus;

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
		static oe::ActionInputKey up2;
		static oe::ActionInputKey left;
		static oe::ActionInputKey left2;
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


		// Stats
		static F32 BatteryPlayer;
		static F32 SpeedPlayer;
		static U32 ExperienceB;
		static U32 ExperienceC;
		static U32 PointsGain;
		static F32 BatteryGain;
		static F32 SpeedGain;
		static U32 StrengthGain;
		static F32 BatteryEnemy;
		static F32 SpeedEnemy;
		static U32 WeaponEnemy;
		static F32 BatteryBoss;
		static F32 SpeedBoss;
		static U32 WeaponBoss;
		static F32 InfoDistance;
		static F32 ChargerDistance;
		static F32 SpawnerDistance;
		static F32 SpawnDistance;
		static F32 FocusGainDistance;
		static F32 FocusLostDistance;
		static F32 TeleporterDistance;
		static F32 TeleporterLostDistance;
		static F32 ExplosionDistance;
		static U32 ExperienceMiniKiller;
		static U32 ExperienceKiller;
		static U32 ExperienceMegaKiller;
		static F32 PlasmaReduction;
		static U32 ProjectileReduction;
		static F32 ProjectileSpeed;
		static void loadStats();

		static std::vector<U32> visited;
		static void visit(U32 mapId);

};

#endif // GAMESINGLETON_HPP
