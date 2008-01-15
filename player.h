#ifndef "PLAYER_H"
#define "PLAYER_H"

#include "main.h"

class Player {
	public:
		Player();
		~Player();

		// == Vars ==
		uint score;
		uint posx;
		uint posy;
	private:
		Player(const Player &player);
};

#endif