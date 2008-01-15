#include "graphics.h"

Graphics::Graphics(Game &thegame, uint width, uint height): game(thegame)
{
	// Now we get ourself a widthxheightx32 surface...
	screen=SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
	if ( screen == NULL )
	{
    	printf("Unable to set %ux%u video: %s\n", width, height, SDL_GetError());
		exit(1);
	}
	// Hide the cursor
	SDL_ShowCursor(0);

}

Graphics::~Graphics()
{
	// Clear graphics memory
	// TODO
}

void Graphics::draw()
{
	switch(game.state) {
		case GAME_MENU:
			drawmenu();
			break;
		case GAME_PLAY:
			drawplay();
			break;
		case GAME_SETTINGS:
			drawsettings();
			break;
		case GAME_STOP:
			break;
		default:
			printf("Fatal Error");
			exit(1);
	}
}

void Graphics::drawmenu()
{
	// TODO
}

void Graphics::drawplay()
{
	// TODO
}

void Graphics::drawsettings()
{
	// TODO
}

