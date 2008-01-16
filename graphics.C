#include "graphics.h"

Graphics::Graphics(Game &thegame):
	game(&thegame),
	screen(NULL),
	font(NULL),
	yellowfont(NULL),
	mePreviousDirection(PLAYER_DIRECTION_NORMAL),
	otherplayerPreviousDirection(PLAYER_DIRECTION_NORMAL),
	background(NULL)
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
	playerNormalSpriteBase.init("data/playernormal");
	playerLeftSpriteBase.init("data/playerleft");
	playerRightSpriteBase.init("data/playerright");
	// Load the images for my bullet
	playerBulletSpriteBase.init("data/playerbullet");
	// Load the images for the other player
	otherplayerNormalSpriteBase.init("data/enemynormal");
	otherplayerLeftSpriteBase.init("data/enemyleft");
	otherplayerRightSpriteBase.init("data/enemyright");
	// Load the images for the other player's bullet
	otherplayerBulletSpriteBase.init("data/enemybullet");
	// My Sprites
	meNormal.init(&playerNormalSpriteBase,screen);
	meLeft.init(&playerLeftSpriteBase,screen);
	meRight.init(&playerRightSpriteBase,screen);
	myBullet.init(&playerBulletSpriteBase,screen);
	// Other player's sprites
	otherplayerNormal.init(&otherplayerNormalSpriteBase,screen);
	otherplayerLeft.init(&otherplayerLeftSpriteBase,screen);
	otherplayerRight.init(&otherplayerRightSpriteBase,screen);
	otherplayerBullet.init(&otherplayerBulletSpriteBase,screen);
}

Graphics::~Graphics()
{ }

void Graphics::draw()
{
	switch(game->state) {
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
	drawbackground();
	// Draw the players
	drawplayers();
	// Draw the scores
	drawscores();
	// Flip the screen
	SDL_Flip(screen);
}

void Graphics::drawbackground()
{
	uint mapwidth = game.map->width;
	uint mapheight = game.map->height;
	uint widthblock = VID_RESOLUTION_X / mapwidth;
	uint heightblock = VID_RESOLUTION_Y / mapheight;
	if (background == NULL || game.mapid != mapid) {
		mapid = game.mapid;
		for(uint i; i < mapwidth; ++i) {
			for (uint j; j < mapheight; ++j) {
				switch (game.map->get(i,j))
					case MAP_CLEAR:
						


	drawimg(background,0,0,VID_RESOLUTION_X,VID_RESOLUTION_Y,0,0);
}

void Graphics::drawplayers()
{
	switch (game->me.direction)
	{	case PLAYER_DIRECTION_NORMAL:
			if (mePreviousDirection != PLAYER_DIRECTION_NORMAL)	{
				meNormal.stopAnim();
				meNormal.setFrame(0);
			}
			meNormal.draw();
			break;
		case PLAYER_DIRECTION_LEFT:
			if (mePreviousDirection != PLAYER_DIRECTION_LEFT) {
				meLeft.setFrame(0);
				meLeft.startAnim();
			}
			meLeft.draw();
			break;
		case PLAYER_DIRECTION_RIGHT:
			if(mePreviousDirection != PLAYER_DIRECTION_RIGHT) {
				meRight.setFrame(0);
				meRight.startAnim();
			}
			meRight.draw();
			break;
		default:
			printf("Fatal Error: Drawplayers()");
			exit(1);
	}

	switch (game->otherplayer.direction)
	{	case PLAYER_DIRECTION_NORMAL:
			if (otherplayerPreviousDirection != PLAYER_DIRECTION_NORMAL)	{
				otherplayerNormal.stopAnim();
				otherplayerNormal.setFrame(0);
			}
			otherplayerNormal.draw();
			break;
		case PLAYER_DIRECTION_LEFT:
			if (otherplayerPreviousDirection != PLAYER_DIRECTION_LEFT) {
				otherplayerLeft.setFrame(0);
				otherplayerLeft.startAnim();
			}
			otherplayerLeft.draw();
			break;
		case PLAYER_DIRECTION_RIGHT:
			if(otherplayerPreviousDirection != PLAYER_DIRECTION_RIGHT) {
				otherplayerRight.setFrame(0);
				otherplayerRight.startAnim();
			}
			otherplayerRight.draw();
			break;
		default:
			printf("Fatal Error: Drawplayers()");
			exit(1);
	}
}

void Graphics::drawscores()
{
	drawString(screen, font, 5,5,"Score Player1:");
	drawString(screen, font, 80,5,"%u",game->me.score);
	drawString(screen, font, 200,5,"Score Player2:");
	drawString(screen, font, 280,5,"%u",game->otherplayer.score);
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

