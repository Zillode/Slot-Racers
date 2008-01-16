#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"
#include "CSprite.h"
#include "CSpriteBase.h"
#include "font.h"

class Game;

class Graphics {
	public:
		Graphics(Game &thegame);
		~Graphics();
		void draw();
	private:
		// No copy allowed
		Graphics(const Graphics &g);

		// == Functions ==
		void drawmenu();
		void drawplay();
		void drawsettings();
		void drawimg(SDL_Surface *img, int x, int y, int w, int h, int x2, int y2);
		void drawplayers();
		void drawbackground();
		void drawscores();

		// == Vars ==
		// screen - our main surface and a background
		SDL_Surface *screen, *background;
		// MapId so that the background is in sync with the map
		uint mapid;
		// keep a reference to the game (to ask the status for drawing / information)
		Game *game;
		// Fonts
		SDLFont *font, *yellowfont;
		uint mePreviousDirection;
		uint otherplayerPreviousDirection;
		// PlayerSprites for me
		CSprite meNormal;
		CSprite meLeft;
		CSprite meRight;
		CSprite myBullet;
		CSpriteBase playerNormalSpriteBase;
		CSpriteBase playerLeftSpriteBase;
		CSpriteBase playerRightSpriteBase;
		CSpriteBase playerBulletSpriteBase;
		// PlayerSprites for enemy
		CSprite otherplayerNormal;
		CSprite otherplayerLeft;
		CSprite otherplayerRight;
		CSprite otherplayerBullet;
		CSpriteBase otherplayerNormalSpriteBase;
		CSpriteBase otherplayerLeftSpriteBase;
		CSpriteBase otherplayerRightSpriteBase;
		CSpriteBase otherplayerBulletSpriteBase;
};

#endif
