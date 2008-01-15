#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"
#include "game.h"
#include "CSprite.h"
#include "CSpriteBase.h"
#include "font.h"

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

		// == Vars ==
		// screen - our main surface, back - the scrolling background
		SDL_Surface *screen, *back;
		// keep a reference to the game (to ask the status for drawing / information)
		Game &game;
		// Fonts
		SDLFont *font, *yellowfont;
		// PlayerSprites for me
		CSprite menormal;
		CSprite meleft;
		CSprite meright;
		CSprite bullet;
		CSpriteBase playernormalSpriteBase;
		CSpriteBase playerleftSpriteBase;
		CSpriteBase playerrightSpriteBase;
		CSpriteBase bulletSpriteBase;
		// PlayerSprites for enemy
		CSprite otherplayernormal;
		CSprite otherplayerleft;
		CSprite otherplayerright;
		CSprite otherbullet;
		CSpriteBase otherplayernormalSpriteBase;
		CSpriteBase otherplayerleftSpriteBase;
		CSpriteBase otherplayerrightSpriteBase;
		CSpriteBase otherbulletSpriteBase;
};

#endif
