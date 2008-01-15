#ifndef GAME_H
#define GAME_H

class Game {
	public:
		Game();
		~Game();

		// == Functions ==
		bool stop();
		void check_events();

		// == Vars ==
		uint state;
		Player me;
		Player otherplayer;

	private:
		Game(const Game &game);
};

#endif
