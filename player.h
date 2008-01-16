#ifndef PLAYER_H
#define PLAYER_H

class Player {
	public:
		Player();
		~Player();

		// == Vars ==
		uint score;
		uint directiongoal;
		uint directionmoving;
		uint speed;
		uint hittime;
		Bullet bullet;
		uint posx;
		uint posy;

		// == Functions ==
		void left();
		void right();
		void up();
		void down();
		void shoot();

	private:
		Player(const Player &player);
};

#endif
