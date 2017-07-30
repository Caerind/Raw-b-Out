#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

// Window
#define WINSIZEX 1024
#define WINSIZEY 768
#define WINTITLE "LudumDare39"

// Textures
#define TEXTURE_MINIKILLER "../Assets/robot-minikiller.png"
#define TEXTURE_KILLER "../Assets/robot-killer.png"
#define TEXTURE_MEGAKILLER "../Assets/robot-megakiller.png"
#define TEXTURE_PROJECTILES "../Assets/projectiles.png"
#define TEXTURE_GUI "../Assets/gui.png"
#define TEXTURE_WEAPONS "../Assets/weapons.png"
#define TEXTURE_PARTICLE "../Assets/particle.png"
#define TEXTURE_SCREEN "../Assets/screen.png"
#define TEXTURE_MENU "../Assets/menu.png"
#define TEXTURE_ATMOG "../Assets/atmog.png"

// Font
#define FONT_SANSATION "../Assets/font.ttf"

// Sounds
#define SOUND_AMMO "../Assets/Sounds/ammo.wav"
#define SOUND_BUTTON "../Assets/Sounds/button.wav"
#define SOUND_CHARGE "../Assets/Sounds/charge.wav"
#define SOUND_CHEST "../Assets/Sounds/chest.wav"
#define SOUND_CLICK "../Assets/Sounds/click.wav"
#define SOUND_DAMAGE "../Assets/Sounds/damage.wav"
#define SOUND_DIE "../Assets/Sounds/die.wav"
#define SOUND_ERROR "../Assets/Sounds/error.wav"
#define SOUND_EXPLOSION "../Assets/Sounds/explosion.wav"
#define SOUND_INFO "../Assets/Sounds/info.wav"
#define SOUND_LASER "../Assets/Sounds/laser.wav"
#define SOUND_LEVEL "../Assets/Sounds/level.wav"
#define SOUND_PLASMA "../Assets/Sounds/plasma.wav"
#define SOUND_TELEPORT "../Assets/Sounds/teleport.wav"
#define SOUND_ULTIME "../Assets/Sounds/ultime.wav"
#define SOUND_WALL "../Assets/Sounds/wall.wav"

// Musics
#define MUSIC_MAIN "../Assets/Musics/main.ogg"
#define MUSIC_FIGHT "../Assets/Musics/fight.ogg"

// Tileset
#define TILESETSOURCE "../Assets/tileset.png"
#define TILESETSIZEX 64
#define TILESETSIZEY 64
#define TILESETCOUNT 60
#define TILESETCOLUMNS 10

// Map
#define MAPPATH "../Assets/Map/map-"
#define MAPSIZEX 30
#define MAPSIZEY 30
#define MAPTILESIZEX 64
#define MAPTILESIZEY 64
#define MAPHEXSIDE 0

// Tile
#define TILE_NONE 1
#define TILE_TELEPORTER 2
#define TILE_BATTERY 3
#define TILE_ENEMY1 4
#define TILE_ENEMY2 5
#define TILE_ENEMY3 6
#define TILE_INFO 7
#define TILE_CHEST 8
#define TILE_CHEST_OPEN 9
#define TILE_UNDEFINED1 10
#define TILE_WALL 11
#define TILE_BREAKABLEWALL 12
#define TILE_WALL1 13
#define TILE_WALL2 14
#define TILE_WALL3 15
#define TILE_WALL4 16
#define TILE_WALL5 17
#define TILE_WALL6 18
#define TILE_WALL7 19
#define TILE_WALL8 20
#define TILE_GROUND 21
#define TILE_FAKEGROUND 22
#define TILE_GROUND1 23
#define TILE_GROUND2 24
#define TILE_GROUND3 25
#define TILE_GROUND4 26
#define TILE_GROUND5 27
#define TILE_GROUND6 28
#define TILE_GROUND7 29
#define TILE_GROUND8 30

// Robot properties
#define ROBOT_DEFAULT_BATTERY 100
#define ROBOT_DEFAULT_SPEED 200
#define ROBOT_DEFAULT_STRENGTH 100

// Distances
#define INFO_DISTANCE 200
#define CHARGER_DISTANCE 70
#define SPAWNER_DISTANCE 700
#define FOCUSGAIN_DISTANCE 500
#define FOCUSLOST_DISTANCE 700
#define TELEPORTER_DISTANCE 50
#define EXPLOSION_DISTANCE 200

// Save
#define SAVE_PATH "../Assets/save.xml"
#define SAVE_VERSION "1.0"

#endif // GAMECONFIG_HPP
