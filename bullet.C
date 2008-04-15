#include "main.h"
#include "player.h"

Bullet::Bullet(Game *thegame):
	MovingObject(thegame),
	shot(false),
	game(thegame)
{
	speed = 4;
}

Bullet::~Bullet()
{ }

void Bullet::start(uint nx, uint ny, uint ngoal, uint nmoving) {
	posx = nx;
	posy = ny;
	directiongoal = ngoal;
	directionmoving = nmoving;
	shot = true;
}

void Bullet::stop() {
	shot = false;
}
