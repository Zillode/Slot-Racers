#ifndef MAIN_H
#define MAIN_H

// GAME PROPERTIES
#define MAX_PLAYERS 2

// MAP VALUES
#define MAP_CLEAR	0
#define MAP_WALL	1

// C++ stuff
#include <vector>
#include <string>
#include <assert.h>

// SDL stuff
#include "SDL/SDL.h"

// Game States
#define GAME_MENU		1
#define GAME_PLAY		2
#define GAME_SETTINGS	3
#define GAME_STOP		4
#define GAME_PAUSE		5

// Video Resolution
#define VID_RESOLUTION_X 320
#define VID_RESOLUTION_Y 240

// Player States
#define OBJECT_MAX_SPEED		3
#define PLAYER_DIRECTION_NORMAL	0
#define PLAYER_DIRECTION_LEFT	1
#define PLAYER_DIRECTION_RIGHT	2

// Player Moving States
#define PLAYER_DIRECTION_MOVING_UP		0
#define PLAYER_DIRECTION_MOVING_LEFT	1
#define PLAYER_DIRECTION_MOVING_RIGHT	2
#define PLAYER_DIRECTION_MOVING_DOWN	3

// Map States
#define MAP_ITEM_CLEAR	0
#define MAP_ITEM_WALL	1

#define uint unsigned int

using std::vector;
using std::string;

// Game stuff
#include "game.h"
#include "graphics.h"

#endif
