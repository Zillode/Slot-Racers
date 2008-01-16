#include "main.h"
#include "player.h"

Player::Player():
	score(0),
	hittime(0),
	directionmoving(PLAYER_DIRECTION_MOVING_UP),
	directiongoal(PLAYER_DIRECTION_NORMAL)
{ }

Player::~Player()
{ }

Player::left() {
	directiongoal = PLAYER_DIRECTION_LEFT;
}

Player::right() {
	directiongoal = PLAYER_DIRECTION_RIGHT;
}

Player::up() {
	if (speed < 3)
		++speed;
}

Player::down() {
	if (speed > 0)
		--speed;
}

