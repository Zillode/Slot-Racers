#include "graphics.h"

Graphics::Graphics(Game *thegame):
	game(thegame),
	screen(NULL),
	font(NULL),
	yellowfont(NULL),
	mePreviousDirection(PLAYER_DIRECTION_NORMAL),
	otherplayerPreviousDirection(PLAYER_DIRECTION_NORMAL),
	background(NULL),
	meNormal(false), // Doens't stop animating on last frame
	meLeft(true),
	meRight(true),
	myBullet(false),
	otherplayerNormal(false),
	otherplayerLeft(true),
	otherplayerRight(true),
	otherplayerBullet(false)
{
	// Now we get ourself a widthxheightx32 surface...
	screen = SDL_SetVideoMode(VID_RESOLUTION_X,VID_RESOLUTION_Y, 16, SDL_SWSURFACE);
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
	delete background;
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

void Graphics::softstrech() {
	// Strech to the resolution
	uint block_width = VID_RESOLUTION_X / game->map->getwidth();
	uint block_height = VID_RESOLUTION_Y / game->map->getheight();
	game->me.width = block_width;
	game->me.height = block_height;
	game->otherplayer.width = block_width;
	game->otherplayer.height = block_height;
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
			delete background;
		background = new SDL_Surface();
		mapid = game->mapid;
		// Strech the images to the map <-> resolution
		//softstrech();
		// Draw everything on the background surface
		for(uint i(0); i < game->map->getwidth(); ++i) {
			for (uint j(0); j < game->map->getheight(); ++j) {
				switch (game->map->get(i,j)) {
					case MAP_CLEAR:
						// The Default white background
						break;
					case MAP_WALL:
						drawimg(mapWallSpriteBase.mAnim[0].image, background, 0, 0, mapWallSpriteBase.mW, mapWallSpriteBase.mH, i, j);
						break;
					default:
						printf("Fatal error: DrawBackground()");
						exit(1);
				}
			}
		}
	}
	drawimg(background, 0, 0, VID_RESOLUTION_X, VID_RESOLUTION_Y, 0, 0);
}

void Graphics::drawplayers()
{
	// If 3 seconds have passed since the player got hit then
	if(game->sdlgt - game->me.hittime>3000)	{
		// Stop the ships blinking animation
		meNormal.stopAnim();
		// Show the frame of animation with the ship on it
		meNormal.setFrame(0);
	}
	// If 3 seconds have passed since the other player got hit then
	if(game->sdlgt - game->otherplayer.hittime>3000) {
		// Stop the ships blinking animation
		otherplayerNormal.stopAnim();
		// Show the frame of animation with the ship on it
		otherplayerNormal.setFrame(0);
	}

	switch (game->me.directiongoal)
	{	case PLAYER_DIRECTION_NORMAL:
			if (mePreviousDirection != PLAYER_DIRECTION_NORMAL)	{
				mePreviousDirection = PLAYER_DIRECTION_NORMAL;
				meNormal.stopAnim();
				meNormal.setFrame(0);
			}
			meNormal.set(game->me.posx, game->me.posy);
			meNormal.draw();
			break;
		case PLAYER_DIRECTION_LEFT:
			if (mePreviousDirection != PLAYER_DIRECTION_LEFT) {
				mePreviousDirection = PLAYER_DIRECTION_LEFT;
				meLeft.setFrame(0);
				meLeft.startAnim();
			}
			meLeft.set(game->me.posx, game->me.posy);
			meLeft.draw();
			break;
		case PLAYER_DIRECTION_RIGHT:
			if(mePreviousDirection != PLAYER_DIRECTION_RIGHT) {
				mePreviousDirection = PLAYER_DIRECTION_RIGHT;
				meRight.setFrame(0);
				meRight.startAnim();
			}
			meRight.set(game->me.posx, game->me.posy);
			meRight.draw();
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
			otherplayerNormal.set(game->me.posx, game->me.posy);
			otherplayerNormal.draw();
			break;
		case PLAYER_DIRECTION_LEFT:
			if (otherplayerPreviousDirection != PLAYER_DIRECTION_LEFT) {
				otherplayerPreviousDirection = PLAYER_DIRECTION_LEFT;
				otherplayerLeft.setFrame(0);
				otherplayerLeft.startAnim();
			}
			otherplayerLeft.set(game->me.posx, game->me.posy);
			otherplayerLeft.draw();
			break;
		case PLAYER_DIRECTION_RIGHT:
			if(otherplayerPreviousDirection != PLAYER_DIRECTION_RIGHT) {
				otherplayerPreviousDirection = PLAYER_DIRECTION_RIGHT;
				otherplayerRight.setFrame(0);
				otherplayerRight.startAnim();
			}
			otherplayerRight.set(game->me.posx, game->me.posy);
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
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;
  SDL_BlitSurface(img, &dest2, destimg, &dest);
}


void Graphics::drawsettings()
{
	// TODO
}

void Graphics::moveplayer(uint nX, uint xY) {
	// TODO
}
