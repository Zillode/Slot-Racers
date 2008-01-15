#include "graphics.h"

Graphics::Graphics(Game &thegame):
	game(thegame)
{
	// Now we get ourself a widthxheightx32 surface...
	screen=SDL_SetVideoMode(VID_RESOLUTION_X,VID_RESOLUTION_Y, 16, SDL_SWSURFACE);
	if ( screen == NULL )
	{
    	printf("Unable to set %ux%u video: %s\n", VID_RESOLUTION_X, VID_RESOLUTION_Y, SDL_GetError());
		exit(1);
	}
	// Hide the cursor
	SDL_ShowCursor(0);
	// Load the font
	font = initFont("data/font");
	yellowfont = initFont("data/font",1,1,0);
	// Load the images for me
	playerSpriteBase.init("data/player");
	playerLeftSpriteBase.init("data/playerleft");
	playerRightSpriteBase.init("data/playerright");
	// Load the images for my bullet
	bulletSpriteBase.init("data/bullet");
	// Load the images for the other player
	otherplayerSpriteBase.init("data/enemy");
	otherplayerSpriteBase.init("data/enemyleft");
	otherplayerSpriteBase.init("data/enemyright");
	// Load the images for the other player's bullet
	otherbulletSpriteBase.init("data/enemybullet");
	SDL_SetColorKey(gameoverimg, SDL_SRCCOLORKEY, SDL_MapRGB(gameoverimg->format, 0, 255, 0));
	me.init(&playerSpriteBase,screen);
	bullet.init(&bulletSpriteBase,screen);
	otherplayer.init(&otherplayerSpriteBase,screen);
	otherbullet.init(&otherbulletSpriteBase,screen);
	me.setSpeed(1);
	otherplayer.setSpeed(1);
}

Graphics::~Graphics()
{ }

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
			// Do nothing
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
	// We first fill the entire screen with black
	SDL_FillRect(screen,0,0);
	// Draw the background
	drawimg(background,0,0,VID_RESOLUTION_X,VID_RESOLUTION_Y,0,0)
	// Draw the players
	drawplayers();
	// Draw the scores
	drawscores();
	// Flip the screen
	SDL_Flip(screen);
}

void Graphics::drawplayers()
{
	meSprite.draw();
	otherplayerSprite.draw();
}

void Graphics::drawscores()
{
	drawString(screen, font, 5,5,"Score Player1:");
	drawString(screen, font, 80,5,"%u",game.me.score);
	drawString(screen, font, 200,5,"Score Player2:");
	drawString(screen, font, 280,5,"%u",otherplayer.score)
}

void Graphics::drawimg(SDL_Surface *img, int x, int y, int w, int h, int x2, int y2)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;
  SDL_BlitSurface(img, &dest2, screen, &dest);
}

void Graphics::drawsettings()
{
	// TODO
}

