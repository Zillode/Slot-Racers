#include "main.h"
#include "player.h"

Player::Player():
	score(0),
	hittime(0),
	graphics(NULL),
	currentsprite(NULL),
	spritenormal(NULL),
	spriteleft(NULL),
	spriteright(NULL),
	spritebullet(NULL),
	directionmoving(PLAYER_DIRECTION_MOVING_UP),
	directiongoal(PLAYER_DIRECTION_NORMAL)
{ }

Player::~Player()
{ }

void Player::normal() {
	directiongoal = PLAYER_DIRECTION_NORMAL;
	updatecurrentsprite();
}

void Player::left() {
	directiongoal = PLAYER_DIRECTION_LEFT;
	updatecurrentsprite();
}

void Player::right() {
	directiongoal = PLAYER_DIRECTION_RIGHT;
	updatecurrentsprite();
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
	currentsprite->xset(nX);
	currentsprite->yset(nY);
}

void Player::updatecurrentsprite() {
	switch (directionmoving) {
	case PLAYER_DIRECTION_NORMAL:
		currentsprite = spritenormal;
		break;
	case PLAYER_DIRECTION_LEFT:
		currentsprite = spriteleft;
		break;
	case PLAYER_DIRECTION_RIGHT:
		currentsprite = spriteright;
		break;
	}
}


void Player::setgraphics(Graphics *thegraphics, CSprite *myspritenormal, CSprite *myspriteleft, CSprite *myspriteright, CSprite *myspritebullet) {
	graphics = thegraphics;
	spritenormal = myspritenormal;
	spriteleft = myspriteleft;
	spriteright = myspriteright;
	spritebullet = myspritebullet;
	currentsprite = spritenormal;
}

