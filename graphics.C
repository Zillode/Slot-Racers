#include "graphics.h"

Graphics::Graphics(Game *thegame):
	game(thegame),
	meNormal(false), // Doesn't stop animating on last frame
	meLeft(true),
	meRight(true),
	myBullet(false),
	otherplayerNormal(false),
	otherplayerLeft(true),
	otherplayerRight(true),
	otherplayerBullet(false),
	screen(NULL),
	background(NULL),
	border_width(0),
	border_height(0),
	font(NULL),
	yellowfont(NULL),
	mePreviousDirection(PLAYER_DIRECTION_NORMAL),
	otherplayerPreviousDirection(PLAYER_DIRECTION_NORMAL)
{
	screen = SDL_SetVideoMode(VID_RESOLUTION_X,VID_RESOLUTION_Y, 16, SDL_SWSURFACE);
	if ( screen == NULL )
	{
		printf("Unable to set %ux%u video: %s\n", VID_RESOLUTION_X, VID_RESOLUTION_Y, SDL_GetError());
		exit(1);
	}
	// We first fill the entire screen with white
	SDL_FillRect(screen,0,0xFFFFFF);
	// Hide the cursor
	SDL_ShowCursor(0);
	// Load the font
	font = initFont("data/font", 255, 255, 255);
	yellowfont = initFont("data/font",1,1,0);
	// Load the wall image
	mapWallSpriteBase.init("data/wall");
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
{
	freeFont(font);
	freeFont(yellowfont);
	if (background != NULL)
		SDL_FreeSurface(background);
}

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
		case GAME_PAUSE:
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
	// Draw the background
	drawbackground();
	// Draw the players
	drawplayers();
	// Draw the bullets
	drawbullets();
	// Draw the scores
	drawscores();
	// Flip the screen
	SDL_Flip(screen);
}

void Graphics::softstrech() {
	// Strech to the resolution
	uint block_width = game->block_width;
	uint block_height = game->block_height;
	mapWallSpriteBase.softStrech(block_width, block_height);
	playerNormalSpriteBase.softStrech(block_width, block_height);
	playerLeftSpriteBase.softStrech(block_width, block_height);
	playerRightSpriteBase.softStrech(block_width, block_height);
	playerBulletSpriteBase.softStrech(block_width, block_height);
	otherplayerNormalSpriteBase.softStrech(block_width, block_height);
	otherplayerLeftSpriteBase.softStrech(block_width, block_height);
	otherplayerRightSpriteBase.softStrech(block_width, block_height);
	otherplayerBulletSpriteBase.softStrech(block_width, block_height);
}

void Graphics::drawbackground()
{
	if (background == NULL || game->mapid != mapid) {
		if (background != NULL)
			SDL_FreeSurface(background);
		background = SDL_DisplayFormat(screen);
		SDL_FillRect(background,NULL,0xFFFFFF);
		mapid = game->mapid;
		// Strech the images to the map <-> resolution
		softstrech();
		// Draw everything on the background surface
		for(uint i(0); i < game->map->getwidth(); ++i) {
			for (uint j(0); j < game->map->getheight(); ++j) {
				switch (game->map->get(i,j)) {
					case MAP_CLEAR:
						// The Default white background
						break;
					case MAP_WALL:
						drawimg(mapWallSpriteBase.mAnim[0].image, background, 0, 0, mapWallSpriteBase.mW, mapWallSpriteBase.mH, i*mapWallSpriteBase.mW, j*mapWallSpriteBase.mH);
						break;
					default:
						printf("Fatal error: DrawBackground()");
						exit(1);
				}
			}
		}
	}
	drawimg(background, 0, 0, VID_RESOLUTION_X, VID_RESOLUTION_Y, game->bound_X_0, game->bound_Y_0);
}

void Graphics::drawplayers()
{
	uint block_half_width = game->block_width / 2;
	uint block_half_height = game->block_height / 2;
	switch (game->me.directiongoal)
	{	case PLAYER_DIRECTION_NORMAL:
			if (mePreviousDirection != PLAYER_DIRECTION_NORMAL)	{
				mePreviousDirection = PLAYER_DIRECTION_NORMAL;
				meNormal.stopAnim();
				meNormal.setFrame(0);
			}
			meNormal.set(game->me.posx - block_half_width, game->me.posy - block_half_height);
			meNormal.draw(game->me.directionmoving);
			break;
		case PLAYER_DIRECTION_LEFT:
			if (mePreviousDirection != PLAYER_DIRECTION_LEFT) {
				mePreviousDirection = PLAYER_DIRECTION_LEFT;
				meLeft.setFrame(0);
				meLeft.startAnim();
			}
			meLeft.set(game->me.posx - block_half_width, game->me.posy - block_half_height);
			meLeft.draw(game->me.directionmoving);
			break;
		case PLAYER_DIRECTION_RIGHT:
			if(mePreviousDirection != PLAYER_DIRECTION_RIGHT) {
				mePreviousDirection = PLAYER_DIRECTION_RIGHT;
				meRight.setFrame(0);
				meRight.startAnim();
			}
			meRight.set(game->me.posx - block_half_width, game->me.posy - block_half_height);
			meRight.draw(game->me.directionmoving);
			break;
		default:
			printf("Fatal Error: Drawplayers()");
			exit(1);
	}

	switch (game->otherplayer.directiongoal)
	{	case PLAYER_DIRECTION_NORMAL:
			if (otherplayerPreviousDirection != PLAYER_DIRECTION_NORMAL)	{
				otherplayerPreviousDirection = PLAYER_DIRECTION_NORMAL;
				otherplayerNormal.stopAnim();
				otherplayerNormal.setFrame(0);
			}
			otherplayerNormal.set(game->otherplayer.posx - block_half_width, game->otherplayer.posy - block_half_height);
			otherplayerNormal.draw(game->otherplayer.directionmoving);
			break;
		case PLAYER_DIRECTION_LEFT:
			if (otherplayerPreviousDirection != PLAYER_DIRECTION_LEFT) {
				otherplayerPreviousDirection = PLAYER_DIRECTION_LEFT;
				otherplayerLeft.setFrame(0);
				otherplayerLeft.startAnim();
			}
			otherplayerLeft.set(game->otherplayer.posx - block_half_width, game->otherplayer.posy - block_half_height);
			otherplayerLeft.draw(game->otherplayer.directionmoving);
			break;
		case PLAYER_DIRECTION_RIGHT:
			if(otherplayerPreviousDirection != PLAYER_DIRECTION_RIGHT) {
				otherplayerPreviousDirection = PLAYER_DIRECTION_RIGHT;
				otherplayerRight.setFrame(0);
				otherplayerRight.startAnim();
			}
			otherplayerRight.set(game->otherplayer.posx - block_half_width, game->otherplayer.posy - block_half_height);
			otherplayerRight.draw(game->otherplayer.directionmoving);
			break;
		default:
			printf("Fatal Error: Drawplayers()");
			exit(1);
	}
}

void Graphics::drawbullets()
{
	if (game->me.bullet.shot) {
		uint block_half_width = game->block_width / 2;
		uint block_half_height = game->block_height / 2;
		myBullet.stopAnim();
		myBullet.setFrame(0);
		myBullet.set(game->me.bullet.posx - block_half_width, game->me.bullet.posy - block_half_height);
		myBullet.draw();
	}
	if (game->otherplayer.bullet.shot) {
		uint block_half_width = game->block_width / 2;
		uint block_half_height = game->block_height / 2;
		otherplayerBullet.stopAnim();
		otherplayerBullet.setFrame(0);
		otherplayerBullet.set(game->otherplayer.bullet.posx - block_half_width, game->otherplayer.bullet.posy - block_half_height);
		otherplayerBullet.draw();
	}
}


void Graphics::drawscores()
{
	drawString(screen, font, 5,5,"Score Player1:");
	drawString(screen, font, 110,5,"%u",game->me.score);
	drawString(screen, font, 200,5,"Score Player2:");
	drawString(screen, font, 305,5,"%u",game->otherplayer.score);
}

void Graphics::drawimg(SDL_Surface *img, int x, int y, int w, int h, int x2, int y2)
{
	drawimg(img, screen, x, y, w, h, x2, y2);
}

void Graphics::drawimg(SDL_Surface *img, SDL_Surface *destimg, int x, int y, int w, int h, int x2, int y2)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;
  SDL_BlitSurface(img, &dest, destimg, &dest2);
}


void Graphics::drawsettings()
{
	// TODO
}

