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
	application.getAudio().playMusic(mainMusic);
	playingMainMusic = true;
}

void GameSingleton::loadResources2()
{
	minikillerTexture = application->getTextures().create("minikillerTexture", oe::TextureLoader::loadFromFile(TEXTURE_MINIKILLER));
	killerTexture = application->getTextures().create("killerTexture", oe::TextureLoader::loadFromFile(TEXTURE_KILLER));
	projectilesTexture = application->getTextures().create("projectilesTexture", oe::TextureLoader::loadFromFile(TEXTURE_PROJECTILES));
	guiTexture = application->getTextures().create("guiTexture", oe::TextureLoader::loadFromFile(TEXTURE_GUI));
	weaponsTexture = application->getTextures().create("weaponsTexture", oe::TextureLoader::loadFromFile(TEXTURE_WEAPONS));
	particleTexture = application->getTextures().create("particleTexture", oe::TextureLoader::loadFromFile(TEXTURE_PARTICLE));
	screenTexture = application->getTextures().create("screenTexture", oe::TextureLoader::loadFromFile(TEXTURE_SCREEN));

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
	}
	return sf::IntRect();
}

void GameSingleton::clear()
{
	map = nullptr;
	player = nullptr;
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
