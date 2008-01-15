#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"
#include "game.h"

class Graphics {
	public:
		Graphics(uint width, uint height);
		~Graphics();
		void draw();
	private:
		// No copy allowed
		Graphics(const Graphics &g);

		// == Functions ==
		void drawmenu();
		void drawplay();
		void drawsettings();

		// == Vars ==
		// screen - our main surface, back - the scrolling background
		SDL_Surface *screen, *back;
		// keep a reference to the game (to ask the status for drawing / information)
		Game &game;
};

#endif
