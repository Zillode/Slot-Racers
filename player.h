#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "movingobject.h"
#include "bullet.h"
#include "CSprite.h"

class Player : public MovingObject {
	public:
		Player(Game *thegame);
		~Player();

		// == Vars ==
		uint score;
		uint hittime;
		bool hittable;
		Bullet bullet;

		// == Functions ==
		void up();
		void down();
		void shoot();
		void hit(Bullet &bullet);

	private:
		Player(const Player &player);
		Game *game;
};

#endif
