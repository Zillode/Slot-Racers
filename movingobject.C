#include "main.h"
#include "movingobject.h"

MovingObject::MovingObject(Game *thegame):
	directiongoal(PLAYER_DIRECTION_NORMAL),
	directionmoving(PLAYER_DIRECTION_MOVING_UP),
	speed(0),
	speeddone(0),
	posx(0),
	posy(0),
	game(thegame)
{ }

MovingObject::~MovingObject()
{ }

void MovingObject::normal() {
	directiongoal = PLAYER_DIRECTION_NORMAL;
}

void MovingObject::left() {
	directiongoal = PLAYER_DIRECTION_LEFT;
}

void MovingObject::right() {
	directiongoal = PLAYER_DIRECTION_RIGHT;
}

void MovingObject::move(uint nX, uint nY) {
	if (nX < posx)
		directionmoving = PLAYER_DIRECTION_MOVING_LEFT;
	if (nX > posx)
		directionmoving = PLAYER_DIRECTION_MOVING_RIGHT;
	if (nY < posy)
		directionmoving = PLAYER_DIRECTION_MOVING_UP;
	if (nY > posy)
		directionmoving = PLAYER_DIRECTION_MOVING_DOWN;
	posx = nX;
	posy = nY;
}

void MovingObject::moveonmap(uint nX, uint nY, uint direction) {
	posx = game->bound_X_0 + (nX * game->block_width) + (game->block_width / 2);
	posy = game->bound_Y_0 + (nY * game->block_height) + (game->block_height / 2);
	directionmoving = direction;
}

