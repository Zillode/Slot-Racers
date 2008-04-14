#include "main.h"
#include "player.h"

Player::Player(Game *thegame):
	MovingObject(thegame),
	score(0),
	hittime(0),
	bullet(thegame),
	game(thegame)
{ }

Player::~Player()
{ }

void Player::up() {
	if (speed < PLAYER_MAX_SPEED)
		++speed;
}

void Player::down() {
	if (speed > 0)
		--speed;
}

void Player::shoot() {
	bullet.start(posx, posy, directiongoal, directionmoving);
}

