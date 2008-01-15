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

// Game stuff
#include "game.h"
#include "graphics.h"
#include "map.h"

// Game Statusses
#define GAME_MENU		1
#define GAME_PLAY		2
#define GAME_SETTINGS	3
#define GAME_STOP		4

// Video Resolution
#define VID_RESOLUTION_X 320
#define VID_RESOLUTION_Y 240

#define uint unsigned int

using std::vector;
using std::string;

#endif
