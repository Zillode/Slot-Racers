#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "game.h"

class MovingObject {
	public:
		MovingObject(Game *thegame);
		~MovingObject();

		// == Vars ==
		uint directiongoal;
		uint directionmoving;
		uint speed;
		uint speeddone;
		uint posx;
		uint posy;

		// == Functions ==
		void normal();
		void left();
		void right();
		void up();
		void down();
		void move(uint x, uint y);
		void moveonmap(uint x, uint y, uint direction);

	private:
		MovingObject(const MovingObject &movingobject);
		Game *game;
};

#endif
