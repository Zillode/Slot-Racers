#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"
#include "CSprite.h"
#include "CSpriteBase.h"
#include "font.h"

class Game;

class Graphics {
	public:
		Graphics(Game *thegame);
		~Graphics();
		void draw();

		// keep a reference to the game (to ask the status for drawing / information)
		Game *game;

		// PlayerSprites for me
		CSprite meNormal;
		CSprite meLeft;
		CSprite meRight;
		CSprite myBullet;

		// PlayerSprites for enemy
		CSprite otherplayerNormal;
		CSprite otherplayerLeft;
		CSprite otherplayerRight;
		CSprite otherplayerBullet;

	private:
		// No copy allowed
		Graphics(const Graphics &g);

		// == Functions ==
		void drawmenu();
		void drawplay();
		void drawsettings();
		void drawimg(SDL_Surface *img, int x, int y, int w, int h, int x2, int y2);
		void drawimg(SDL_Surface *img, SDL_Surface *dest, int x, int y, int w, int h, int x2, int y2);
		void drawplayers();
		void drawbullets();
		void drawbackground();
		void drawscores();
		void softstrech();

		// == Vars ==
		// screen - our main surface and a background
		SDL_Surface *screen, *background;
		// Border (Black)
		uint border_width;
		uint border_height;
		// MapId so that the background is in sync with the map
		uint mapid;
		// Fonts
		SDLFont *font, *yellowfont;
		uint mePreviousDirection;
		uint otherplayerPreviousDirection;
		// Wall SpriteBase (for resizing)
		CSpriteBase mapWallSpriteBase;
		CSpriteBase playerNormalSpriteBase;
		CSpriteBase playerLeftSpriteBase;
		CSpriteBase playerRightSpriteBase;
		CSpriteBase playerBulletSpriteBase;
		CSpriteBase otherplayerNormalSpriteBase;
		CSpriteBase otherplayerLeftSpriteBase;
		CSpriteBase otherplayerRightSpriteBase;
		CSpriteBase otherplayerBulletSpriteBase;
};

#endif
