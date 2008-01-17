#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "CSprite.h"

class Player {
	public:
		Player();
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
		uint width;
		uint height;

		// == Functions ==
		void normal();
		void left();
		void right();
		void up();
		void down();
		void shoot();
		void move(uint x, uint y);
		void setgraphics(Graphics *thegraphics, CSprite *myspritenormal, CSprite *myspriteleft, CSprite *myspriteright, CSprite *myspritebullet);

	private:
		Player(const Player &player);
		void updatecurrentsprite();
		Graphics *graphics;
		CSprite *currentsprite;
		CSprite *spritenormal;
		CSprite *spriteleft;
		CSprite *spriteright;
		CSprite *spritebullet;
};

#endif
