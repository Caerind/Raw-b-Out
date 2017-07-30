#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

// Window
#define WINSIZEX 1024
#define WINSIZEY 768
#define WINTITLE "LudumDare39"

// Resources paths
#define TEXTURE_MINIKILLER "../Assets/robot-minikiller.png"
#define TEXTURE_KILLER "../Assets/robot-killer.png"
#define TEXTURE_MEGAKILLER "../Assets/robot-megakiller.png"
#define TEXTURE_PROJECTILES "../Assets/projectiles.png"
#define TEXTURE_GUI "../Assets/gui.png"
#define TEXTURE_WEAPONS "../Assets/weapons.png"
#define FONTSANSATION "../Assets/font.ttf"
#define SOUNDACTION "../Assets/select.wav"

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
#define TILE_FAKEWALL 12
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
#define ROBOT_DEFAULT_SPEED 100
#define ROBOT_DEFAULT_STRENGTH 100

// Distances
#define INFO_DISTANCE 200
#define CHARGER_DISTANCE 70
#define SPAWNER_DISTANCE 700
#define FOCUSGAIN_DISTANCE 500
#define FOCUSLOST_DISTANCE 700
#define TELEPORTER_DISTANCE 50

#endif // GAMECONFIG_HPP
