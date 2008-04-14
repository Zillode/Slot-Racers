#ifndef GAME_H
#define GAME_H

class Graphics;

#include "graphics.h"
#include "map.h"
#include "player.h"
#include "main.h"

class Game {
	public:
		Game();
		~Game();

		// == Functions ==
		void start();
		bool stop();
		void check_events();
		void setmap(const char *mapname);
		void setgraphics(Graphics *thegraphics);

		// == Vars ==
		uint state;
		Player me;
		Player otherplayer;
		uint mapid;
		Map *map;
		float sdlgt;  // Stores the time that has passed
		uint resolution_x;
		uint resolution_y;
		uint block_width;
		uint block_height;
		uint bound_X_0; // left bound
		uint bound_X_y; // right bound
		uint bound_Y_0; // upper bound
		uint bound_Y_x; // lower bound

	private:
		Game(const Game &game);
		int td,td2;  // Used when checking the time difference
		float dt;    // The time that has elapsed since the previous frame
		unsigned long prevtime;
		Graphics *graphics;
		bool networkgame;

		void processgameplay(SDL_Event &event);
		void processgameplaynetworkenemy();
		void processgameplayplayer(SDL_Event &event);
		void processgameplayenemy(SDL_Event &event);
		void processgameplaystep(Player &player);
		bool trymoveup(Player &player, bool check = false);
		bool trymovedown(Player &player, bool check = false);
		bool trymoveleft(Player &player, bool check = false);
		bool trymoveright(Player &player, bool check = false);
		bool moveallowed(Player &player, int x, int y);
};

#endif
