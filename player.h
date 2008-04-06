#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "CSprite.h"

class Player {
	public:
		Player(Game *thegame);
		~Player();

		// == Vars ==
		uint score;
		uint directiongoal;
		uint directionmoving;
		uint speed;
		uint speeddone;
		uint hittime;
		uint posx;
		uint posy;

		// == Functions ==
		void normal();
		void left();
		void right();
		void up();
		void down();
		void shoot();
		void move(uint x, uint y);
		void moveonmap(uint x, uint y, uint direction);

	private:
		Player(const Player &player);
		Game *game;
};

#endif
