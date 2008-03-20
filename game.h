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

	private:
		Game(const Game &game);
		int td,td2;  // Used when checking the time difference
		float dt;     // The time that has elapsed since the previous frame
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
		bool moveallowed(Player &player, uint x, uint y);
};

#endif
