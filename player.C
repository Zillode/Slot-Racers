#include "main.h"
#include "player.h"

Player::Player():
	score(0),
	posx(0),
	posy(0),
	direction(PLAYER_DIRECTION_NORMAL)
{ }

Player::~Player()
{ }

