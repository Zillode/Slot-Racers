#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "map.h"

class Game {
	public:
		Game();
		~Game();

		// == Functions ==
		bool stop();
		void check_events();
		void setmap(string mapname);

		// == Vars ==
		uint state;
		Player me;
		Player otherplayer;
		uint mapid;
		Map *map;

	private:
		Game(const Game &game);
		int td,td2;  // Used when checking the time difference
		float dt;    // The time that has elapsed since the previous frame
		float sdlgt; // Stores the time that has passed
		bool paused;
};

#endif
