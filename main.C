#include "main.h"

int main(int argc, const char* argv[]) {
	// Initalize the random number generator
	srand(time(NULL));
	// Initalize the SDL Video, Audio and Joystick subsystems.
	if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0) {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	// Make sure SDL quits on exit
	atexit(SDL_Quit);

	// We need the game controller
	Game game;
	// We need Graphics
	Graphics graphics(game);

	while(!game.stop()) {
		game.check_events();
		graphics.draw();
	    SDL_Delay(1);
	}




	return 0;
}
