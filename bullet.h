#ifndef BULLET_H
#define BULLET_H

#include "game.h"
#include "bullet.h"
#include "CSprite.h"

class Bullet : public MovingObject {
	public:
		Bullet(Game *thegame);
		~Bullet();
		bool shot;
		void start(uint nx, uint ny, uint ngoal, uint nmoving);
		void stop();

	private:
		Bullet(const Bullet &bullet);
		Game *game;
};

#endif
