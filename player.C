#include "main.h"
#include "player.h"

Player::Player(Game *thegame):
	MovingObject(thegame),
	score(0),
	hittime(0),
	hittable(false),
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

void Player::hit(Bullet &bullet) {
	hittime = SDL_GetTicks();
	speed = OBJECT_MAX_SPEED_DEFAULT;
	directionmoving = bullet.directionmoving;
	hittable = false;
}
