#include "main.h"

int main(int argc, const char* argv[]) {
	// Initalize the random number generator
	srand(time(NULL));
	// Initalize the SDL Video, Audio and Joystick subsystems.
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	// Make sure SDL quits on exit
	atexit(SDL_Quit);

	// We need the game controller
	Game game;
	// We need Graphics
	Graphics graphics(&game);
	// Make a link from game to graphics
	game.setgraphics(&graphics);
	// TODO: move this to the menu
	game.start();

	// Main loop
	while(!game.stop()) {
		game.check_events();
		graphics.draw();
	    SDL_Delay(1);
	}

	// Clean exit
	SDL_Quit();
	return 0;
}
