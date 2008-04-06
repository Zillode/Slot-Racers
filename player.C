#include "main.h"
#include "player.h"

Player::Player(Game *thegame):
	score(0),
	directiongoal(PLAYER_DIRECTION_NORMAL),
	directionmoving(PLAYER_DIRECTION_MOVING_UP),
	speed(0),
	speeddone(0),
	hittime(0),
	posx(0),
	posy(0),
	game(thegame)
{ }

Player::~Player()
{ }

void Player::normal() {
	directiongoal = PLAYER_DIRECTION_NORMAL;
}

void Player::left() {
	directiongoal = PLAYER_DIRECTION_LEFT;
}

void Player::right() {
	directiongoal = PLAYER_DIRECTION_RIGHT;
}

void Player::up() {
	if (speed < 3)
		++speed;
}

void Player::down() {
	if (speed > 0)
		--speed;
}

void Player::shoot() {
	// TODO
}

void Player::move(uint nX, uint nY) {
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

void Player::moveonmap(uint nX, uint nY, uint direction) {
	posx = game->bound_X_0 + (nX * game->block_width) + (game->block_width / 2);
	posy = game->bound_Y_0 + (nY * game->block_height) + (game->block_height / 2);
	directionmoving = direction;
}

