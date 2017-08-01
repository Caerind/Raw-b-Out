#include "GameSingleton.hpp"

#include "GameConfig.hpp" // Used to load the tileset
#include "../Engine/Application/Application.hpp"

oe::Tileset GameSingleton::tileset;
oe::ResourceId GameSingleton::minikillerTexture;
oe::ResourceId GameSingleton::killerTexture;
oe::ResourceId GameSingleton::projectilesTexture;
oe::ResourceId GameSingleton::guiTexture;
oe::ResourceId GameSingleton::weaponsTexture;
oe::ResourceId GameSingleton::particleTexture;
oe::ResourceId GameSingleton::screenTexture;
oe::ResourceId GameSingleton::shadowTexture;
oe::ResourceId GameSingleton::headTexture;
oe::ResourceId GameSingleton::sansationFont;
oe::ResourceId GameSingleton::ammoSound;
oe::ResourceId GameSingleton::buttonSound;
oe::ResourceId GameSingleton::chargeSound;
oe::ResourceId GameSingleton::chestSound;
oe::ResourceId GameSingleton::clickSound;
oe::ResourceId GameSingleton::damageSound;
oe::ResourceId GameSingleton::dieSound;
oe::ResourceId GameSingleton::errorSound;
oe::ResourceId GameSingleton::explosionSound;
oe::ResourceId GameSingleton::infoSound;
oe::ResourceId GameSingleton::laserSound;
oe::ResourceId GameSingleton::levelSound;
oe::ResourceId GameSingleton::plasmaSound;
oe::ResourceId GameSingleton::teleportSound;
oe::ResourceId GameSingleton::ultimeSound;
oe::ResourceId GameSingleton::wallSound;
oe::ResourceId GameSingleton::mainMusic;
oe::ResourceId GameSingleton::fightMusic;
bool GameSingleton::playingMainMusic;
oe::AudioSystem::MusicPtr GameSingleton::musicHandle;
U32 GameSingleton::enemyFocus;
oe::Application* GameSingleton::application;
oe::EntityHandle GameSingleton::mapHandle;
GameMap* GameSingleton::map;
oe::EntityHandle GameSingleton::playerHandle;
RobotPlayer* GameSingleton::player;
std::string GameSingleton::name;
oe::Color GameSingleton::color;
oe::ActionInputKey GameSingleton::up;
oe::ActionInputKey GameSingleton::up2;
oe::ActionInputKey GameSingleton::left;
oe::ActionInputKey GameSingleton::left2;
oe::ActionInputKey GameSingleton::down;
oe::ActionInputKey GameSingleton::right;
oe::ActionInputMouse GameSingleton::shootInput;
oe::ActionInputMouse GameSingleton::pickupInput;
oe::EntityQuery GameSingleton::rQuery;
oe::EntityQuery GameSingleton::rpQuery;
oe::EntityQuery GameSingleton::repQuery;
std::map<WeaponId, WeaponData> GameSingleton::weaponData;
oe::ParserXml GameSingleton::loader;
F32 GameSingleton::BatteryPlayer;
F32 GameSingleton::SpeedPlayer;
U32 GameSingleton::ExperienceB;
U32 GameSingleton::ExperienceC;
U32 GameSingleton::PointsGain;
F32 GameSingleton::BatteryGain;
F32 GameSingleton::SpeedGain;
U32 GameSingleton::StrengthGain;
F32 GameSingleton::BatteryEnemy;
F32 GameSingleton::SpeedEnemy;
U32 GameSingleton::WeaponEnemy;
F32 GameSingleton::BatteryBoss;
F32 GameSingleton::SpeedBoss;
U32 GameSingleton::WeaponBoss;
F32 GameSingleton::InfoDistance;
F32 GameSingleton::ChargerDistance;
F32 GameSingleton::SpawnerDistance;
F32 GameSingleton::SpawnDistance;
F32 GameSingleton::FocusGainDistance;
F32 GameSingleton::FocusLostDistance;
F32 GameSingleton::TeleporterDistance;
F32 GameSingleton::TeleporterLostDistance;
F32 GameSingleton::ExplosionDistance;
U32 GameSingleton::ExperienceMiniKiller;
U32 GameSingleton::ExperienceKiller;
U32 GameSingleton::ExperienceMegaKiller;
F32 GameSingleton::PlasmaReduction;
U32 GameSingleton::ProjectileReduction;
F32 GameSingleton::ProjectileSpeed;
std::vector<U32> GameSingleton::visited;

void GameSingleton::loadTileset()
{
	tileset.setImageSource(TILESETSOURCE);
	tileset.setTileSize(oe::Vector2i(TILESETSIZEX, TILESETSIZEY));
	tileset.setTileCount(TILESETCOUNT);
	tileset.setColumns(TILESETCOLUMNS);
	tileset.getTexture(); // Used to load the texture now
}

void GameSingleton::loadResources(oe::Application& application)
{
	GameSingleton::application = &application;

	mainMusic = application.getAudio().createMusic("main", MUSIC_MAIN);
	fightMusic = application.getAudio().createMusic("fight", MUSIC_FIGHT);
	musicHandle = nullptr;
	playMain();
}

void GameSingleton::loadResources2()
{
	minikillerTexture = application->getTextures().create("minikillerTexture", oe::TextureLoader::loadFromFile(TEXTURE_ENEMY));
	killerTexture = application->getTextures().create("killerTexture", oe::TextureLoader::loadFromFile(TEXTURE_ROBOT));
	projectilesTexture = application->getTextures().create("projectilesTexture", oe::TextureLoader::loadFromFile(TEXTURE_PROJECTILES));
	guiTexture = application->getTextures().create("guiTexture", oe::TextureLoader::loadFromFile(TEXTURE_GUI));
	weaponsTexture = application->getTextures().create("weaponsTexture", oe::TextureLoader::loadFromFile(TEXTURE_WEAPONS));
	particleTexture = application->getTextures().create("particleTexture", oe::TextureLoader::loadFromFile(TEXTURE_PARTICLE));
	screenTexture = application->getTextures().create("screenTexture", oe::TextureLoader::loadFromFile(TEXTURE_SCREEN));
	shadowTexture = application->getTextures().create("shadowTexture", oe::TextureLoader::loadFromFile(TEXTURE_SHADOW));
	headTexture = application->getTextures().create("headTexture", oe::TextureLoader::loadFromFile(ICON_48));

	sansationFont = application->getFonts().create("sansation", oe::FontLoader::loadFromFile(FONT_SANSATION));

	ammoSound = application->getAudio().createSound("ammo", SOUND_AMMO);
	buttonSound = application->getAudio().createSound("button", SOUND_BUTTON);
	chargeSound = application->getAudio().createSound("charge", SOUND_CHARGE);
	chestSound = application->getAudio().createSound("chest", SOUND_CHEST);
	clickSound = application->getAudio().createSound("click", SOUND_CLICK);
	damageSound = application->getAudio().createSound("damage", SOUND_DAMAGE);
	dieSound = application->getAudio().createSound("die", SOUND_DIE);
	errorSound = application->getAudio().createSound("error", SOUND_ERROR);
	explosionSound = application->getAudio().createSound("explosion", SOUND_EXPLOSION);
	infoSound = application->getAudio().createSound("info", SOUND_INFO);
	laserSound = application->getAudio().createSound("laser", SOUND_LASER);
	levelSound = application->getAudio().createSound("level", SOUND_LEVEL);
	plasmaSound = application->getAudio().createSound("plasma", SOUND_PLASMA);
	teleportSound = application->getAudio().createSound("teleport", SOUND_TELEPORT);
	ultimeSound = application->getAudio().createSound("ultime", SOUND_ULTIME);
	wallSound = application->getAudio().createSound("wall", SOUND_WALL);
}

void GameSingleton::loadInputs()
{
	up.setKey(sf::Keyboard::Z);
	up.setType(oe::ActionType::Hold);
	up2.setKey(sf::Keyboard::W);
	up2.setType(oe::ActionType::Hold);
	left.setKey(sf::Keyboard::Q);
	left.setType(oe::ActionType::Hold);
	left2.setKey(sf::Keyboard::A);
	left2.setType(oe::ActionType::Hold);
	down.setKey(sf::Keyboard::S);
	down.setType(oe::ActionType::Hold);
	right.setKey(sf::Keyboard::D);
	right.setType(oe::ActionType::Hold);
	shootInput.setButton(sf::Mouse::Right);
	shootInput.setType(oe::ActionType::Pressed);
	pickupInput.setButton(sf::Mouse::Left);
	pickupInput.setType(oe::ActionType::Pressed);
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
		if (entity->getId() != GameSingleton::player->getId() && fast_dynamic_cast<Robot*>(entity) != nullptr)
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
	if (xml.loadFromFile("Assets/data.xml"))
	{
		if (xml.readNode("weapons"))
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
		xml.closeNode();
	}
}

sf::IntRect GameSingleton::getTextureRectFromWeapon(WeaponId id)
{
	if (id == 0 || id > 50)
	{
		return sf::IntRect();
	}
	Projectile::Type t = (Projectile::Type)GameSingleton::weaponData[id].proj;
	switch (t)
	{
		case Projectile::Ammo: return sf::IntRect(0, 0, 64, 64); break;
		case Projectile::Plasma: return sf::IntRect(0, 64, 64, 64); break;
		case Projectile::Laser: return sf::IntRect(0, 128, 64, 64); break;
		case Projectile::Ultime: return sf::IntRect(256, 0, 64, 64); break;
		default: break;
	}
	return sf::IntRect();
}

void GameSingleton::clear()
{
	map = nullptr;
	player = nullptr;
	enemyFocus = 0;
	visited.clear();
}

void GameSingleton::loadStats()
{
	BatteryPlayer = 400.f;
	SpeedPlayer = 300.f;
	ExperienceB = 15;
	ExperienceC = 10;
	PointsGain = 3;
	BatteryGain = 5;
	SpeedGain = 3.f;
	StrengthGain = 2;

	BatteryEnemy = 200.f;
	SpeedEnemy = 100.f;
	WeaponEnemy = 50;

	BatteryBoss = 2000.f;
	SpeedBoss = 100.f;
	WeaponBoss = 13;

	InfoDistance = 200.f;
	ChargerDistance = 70.f;
	SpawnerDistance = 700.f;
	SpawnDistance = 100.f;
	FocusGainDistance = 500.f;
	FocusLostDistance = 600.f;
	TeleporterDistance = 50.f;
	TeleporterLostDistance = 100.f;
	ExplosionDistance = 200.f;

	ExperienceMiniKiller = 10;
	ExperienceKiller = 100;
	ExperienceMegaKiller = 400;

	PlasmaReduction = 0.5f;
	ProjectileReduction = 5;
	ProjectileSpeed = 500.f;

	oe::ParserXml xml;
	if (xml.loadFromFile("Assets/data.xml"))
	{
		if (xml.readNode("stats"))
		{
			xml.readNode("BatteryPlayer"); xml.getAttribute("value", BatteryPlayer); xml.closeNode();
			xml.readNode("SpeedPlayer"); xml.getAttribute("value", SpeedPlayer); xml.closeNode();
			xml.readNode("ExperienceC"); xml.getAttribute("value", ExperienceC); xml.closeNode();
			xml.readNode("ExperienceB"); xml.getAttribute("value", ExperienceB); xml.closeNode();
			xml.readNode("PointsGain"); xml.getAttribute("value", PointsGain); xml.closeNode();
			xml.readNode("BatteryGain"); xml.getAttribute("value", BatteryGain); xml.closeNode();
			xml.readNode("SpeedGain"); xml.getAttribute("value", SpeedGain); xml.closeNode();
			xml.readNode("StrengthGain"); xml.getAttribute("value", StrengthGain); xml.closeNode();
			xml.readNode("BatteryEnemy"); xml.getAttribute("value", BatteryEnemy); xml.closeNode();
			xml.readNode("SpeedEnemy"); xml.getAttribute("value", SpeedEnemy); xml.closeNode();
			xml.readNode("WeaponEnemy"); xml.getAttribute("value", WeaponEnemy); xml.closeNode();
			xml.readNode("BatteryBoss"); xml.getAttribute("value", BatteryBoss); xml.closeNode();
			xml.readNode("SpeedBoss"); xml.getAttribute("value", SpeedBoss); xml.closeNode();
			xml.readNode("WeaponBoss"); xml.getAttribute("value", WeaponBoss); xml.closeNode();
			xml.readNode("InfoDistance"); xml.getAttribute("value", InfoDistance); xml.closeNode();
			xml.readNode("ChargerDistance"); xml.getAttribute("value", ChargerDistance); xml.closeNode();
			xml.readNode("SpawnerDistance"); xml.getAttribute("value", SpawnerDistance); xml.closeNode();
			xml.readNode("SpawnDistance"); xml.getAttribute("value", SpawnDistance); xml.closeNode();
			xml.readNode("FocusGainDistance"); xml.getAttribute("value", FocusGainDistance); xml.closeNode();
			xml.readNode("FocusLostDistance"); xml.getAttribute("value", FocusLostDistance); xml.closeNode();
			xml.readNode("TeleporterDistance"); xml.getAttribute("value", TeleporterDistance); xml.closeNode();
			xml.readNode("TeleporterLostDistance"); xml.getAttribute("value", TeleporterLostDistance); xml.closeNode();
			xml.readNode("ExplosionDistance"); xml.getAttribute("value", ExplosionDistance); xml.closeNode();
			xml.readNode("ExperienceMiniKiller"); xml.getAttribute("value", ExperienceMiniKiller); xml.closeNode();
			xml.readNode("ExperienceKiller"); xml.getAttribute("value", ExperienceKiller); xml.closeNode();
			xml.readNode("ExperienceMegaKiller"); xml.getAttribute("value", ExperienceMegaKiller); xml.closeNode();
			xml.readNode("PlasmaReduction"); xml.getAttribute("value", PlasmaReduction); xml.closeNode();
			xml.readNode("ProjectileReduction"); xml.getAttribute("value", ProjectileReduction); xml.closeNode();
			xml.readNode("ProjectileSpeed"); xml.getAttribute("value", ProjectileSpeed); xml.closeNode();
		}
		xml.closeNode();
	}
}

void GameSingleton::visit(U32 mapId)
{
	for (U32 i = 0; i < visited.size(); i++)
	{
		if (visited[i] == mapId)
		{
			return;
		}
	}
	visited.push_back(mapId);
}

void GameSingleton::playSound(oe::ResourceId sound)
{
	if (application != nullptr)
	{
		application->getAudio().playSound(sound);
	}
}

void GameSingleton::click()
{
	playSound(clickSound);
}

void GameSingleton::playMain()
{
	if (musicHandle != nullptr)
	{
		musicHandle->stop();
	}
	musicHandle = application->getAudio().playMusic(mainMusic);
	playingMainMusic = true;
}

void GameSingleton::playFight()
{
	if (musicHandle != nullptr)
	{
		musicHandle->stop();
	}
	musicHandle = application->getAudio().playMusic(fightMusic);
	playingMainMusic = false;
}
