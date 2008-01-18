#include "main.h"
#include "game.h"

Game::Game(): state(GAME_PLAY),
	me(this),
	otherplayer(this),
	networkgame(false),
	graphics(NULL),
	map(NULL)
{
	map = new Map(this, 50,50);
	mapid = 0;
	map->put(20,20,MAP_WALL); // TODO
}

Game::~Game()
{
	if (map)
		delete map;
}

void Game::start() {
	state = GAME_PLAY;
	map->setplayers();
}

bool Game::stop()
{
	return (state == GAME_STOP);
}

void Game::setmap(string mapname)
{
	if (map)
		delete map;
	mapid += 1;
	printf("TODO");
	exit(1);
}

void Game::check_events()
{
	// With the following block of code we check how much time has passed
    // between two frames. We store that time in millisecodns in 'dt', divided
    // by 10. If we move some thing dt units in some direction every frame,
    // then after 1 second, the thing has moved 100 pixels.
    // If we move it 2.5*dt units, after 1 second it has moved 250 pixels, etc
    // In order to have frame-rate independent movement, everything must
    // move x*dt pixels.
    td2=SDL_GetTicks();
    dt=((float)(td2-td))*0.1;
    td=td2;

    // We will not use the function SDL_GetTicks() in any other part of the game,
    // but we'll use a simple variable sdlgt instead. We do that because with it
    // the rest of the game won't know whether the game has been paused or not
    // and everything will be updated accordingly
    // If the game isn't paused then we increase the value of sdlgt.
    // Basically sdlgt tells of how many milliseconds the game has been played
    // (w/o being paused)
    if (state != GAME_PAUSE)
    {
      sdlgt+=dt*10;
    }

	// Check if we have some interesting events...
    SDL_Event event;
	SDL_PollEvent(&event);
	// If we must quit, then do so
	if(event.type == SDL_QUIT) { state = GAME_STOP; }

	// Has a key been pressed down?
	if(event.type == SDL_KEYDOWN) {
		// If it was escape then quit
		if(event.key.keysym.sym == SDLK_ESCAPE)
		{
			state = GAME_STOP;
		}

		if(event.key.keysym.sym == SDLK_p)
		{
			if (state == GAME_PAUSE) {
				state = GAME_PLAY;
			} else {
				state = GAME_PAUSE;
			}
		}
	}

	switch (state)
	{
	case GAME_MENU:
		// TODO
		break;
	case GAME_PLAY:
		sdlgt+=dt*10;
		processgameplay(event);
		break;
	case GAME_PAUSE:
		// Do nothing
		// TODO: show pause ?
		break;
	case GAME_STOP:
		return;
	default:
		printf("Fatal error: CheckEvents()");
		exit(1);
	}
}

void Game::processgameplay(SDL_Event &event) {
	processgameplayplayer(event);
	if (networkgame) {
		processgameplaynetworkenemy();
	} else {
		processgameplayenemy(event);
	}
	processgameplaystep(me);
	processgameplaystep(otherplayer);
}

void Game::processgameplaynetworkenemy() {
	// TODO
	printf("Fatal Error: processgameplaynetworkenemy()");
	exit(1);
}

void Game::setgraphics(Graphics *thegraphics) {
	graphics = thegraphics;
}

bool Game::trymoveup(Player &player) {
	uint nposx = player.posx;
	uint nposy = player.posy - 1;
	uint mapblockwidth = VID_RESOLUTION_X / map->getwidth();
	uint mapblockheight = VID_RESOLUTION_Y / map->getheight();
	uint newblockposx = (nposx / mapblockwidth);
	uint newblockposy = (nposy / mapblockheight);
	if (map->get(newblockposx, newblockposy) == MAP_CLEAR) {
		player.move(nposx, nposy);
		return true;
	} else {
		return false;
	}
}

bool Game::trymovedown(Player &player) {
	uint nposx = player.posx;
	uint nposy = player.posy + 1;
	uint mapblockwidth = VID_RESOLUTION_X / map->getwidth();
	uint mapblockheight = VID_RESOLUTION_Y / map->getheight();
	uint newblockposx = (nposx / mapblockwidth);
	uint newblockposy = ((nposy + player.height) / mapblockheight);
	if (map->get(newblockposx, newblockposy) == MAP_CLEAR) {
		player.move(nposx, nposy);
		return true;
	} else {
		return false;
	}
}

bool Game::trymoveleft(Player &player) {
	uint nposx = player.posx - 1;
	uint nposy = player.posy;
	uint mapblockwidth = VID_RESOLUTION_X / map->getwidth();
	uint mapblockheight = VID_RESOLUTION_Y / map->getheight();
	uint newblockposx = (nposx / mapblockwidth);
	uint newblockposy = (nposy / mapblockheight);
	if (map->get(newblockposx, newblockposy) == MAP_CLEAR) {
		player.move(nposx, nposy);
		return true;
	} else {
		return false;
	}
}

bool Game::trymoveright(Player &player) {
	uint nposx = player.posx + 1;
	uint nposy = player.posy;
	uint mapblockwidth = VID_RESOLUTION_X / map->getwidth();
	uint mapblockheight = VID_RESOLUTION_Y / map->getheight();
	uint newblockposx = ((nposx + player.width) / mapblockwidth);
	uint newblockposy = (nposy / mapblockheight);
	if (map->get(newblockposx, newblockposy) == MAP_CLEAR) {
		player.move(nposx, nposy);
		return true;
	} else {
		return false;
	}
}

void Game::processgameplaystep(Player &player) {
	if (player.speeddone > OBJECT_MAX_SPEED)
		player.speeddone = 0;
	// If his speed is high enough to move at this point, make a move!
	if (player.speed > player.speeddone) {
		switch (player.directiongoal) {
			// ================= DIRECTION NORMAL =================
			// When the player doesn't wants to turn
		case PLAYER_DIRECTION_NORMAL:
			// If it's possible, just go in the same direction
			switch (player.directionmoving) {
			case PLAYER_DIRECTION_MOVING_UP:
				// Try to move up
				if (player.speed > 0)
					// When player has speed > 0, he can move
					if (!trymoveup(player))
						// If move up failed, do random right/left
						if ((rand() % 2) == 0) {
							if (!trymoveright(player))
								// If move right also failed, try left
								trymoveleft(player);
						} else {
							if (!trymoveleft(player))
								// If move right also failed, try left
								trymoveright(player);
						}
				break;
			case PLAYER_DIRECTION_MOVING_LEFT:
				if (player.speed > 0)
					if (!trymoveleft(player))
						if ((rand() % 2) == 0) {
							if (!trymoveup(player))
								trymovedown(player);
						} else {
							if (!trymovedown(player))
								trymoveup(player);
						}
				break;
			case PLAYER_DIRECTION_MOVING_RIGHT:
				if (player.speed > 0)
					if (!trymoveright(player))
						if ((rand() % 2) == 0) {
							if (!trymoveup(player))
								trymovedown(player);
						} else {
							if (!trymovedown(player))
								trymoveup(player);
						}
				break;
			case PLAYER_DIRECTION_MOVING_DOWN:
				if (player.speed > 0)
					if (!trymovedown(player))
						if ((rand() % 2) == 0) {
							if (!trymoveleft(player))
								trymoveright(player);
						} else {
							if (!trymoveright(player))
								trymoveleft(player);
						}
				break;
			default:
				printf("Fatal error: processgameplaystep()");
				exit(1);
			}
			// ================= DIRECTION LEFT =================
			// When the player wants to turn to left
		case PLAYER_DIRECTION_LEFT:
			switch (player.directionmoving) {
			case PLAYER_DIRECTION_MOVING_UP:
				if (player.speed > 0)
					// When player has speed > 0, he can move
					if (!trymoveleft(player))
						// If move left fails when going up, continue to go up
						if (!trymoveup(player))
							// If move up failed, do left
							trymoveright(player);
				break;
			case PLAYER_DIRECTION_MOVING_LEFT:
				if (player.speed > 0)
					if (!trymovedown(player))
						if (!trymoveleft(player))
							trymoveup(player);
				break;
			case PLAYER_DIRECTION_MOVING_RIGHT:
				if (player.speed > 0)
					if (!trymoveup(player))
						if (!trymoveright(player))
							trymovedown(player);
				break;

			case PLAYER_DIRECTION_MOVING_DOWN:
				if (player.speed > 0)
					if (!trymoveright(player))
						if (!trymovedown(player))
							trymoveleft(player);
				break;

			default:
				printf("Fatal error: processgameplaystep()");
				exit(1);
			}
			break;
			// ================= DIRECTION RIGHT =================
			// When the player wants to turn to right
		case PLAYER_DIRECTION_RIGHT:
			switch (player.directionmoving) {
			case PLAYER_DIRECTION_MOVING_UP:
				if (player.speed > 0)
					// When player has speed > 0, he can move
					if (!trymoveright(player))
						// If move right fails when going up, continue to go up
						if (!trymoveup(player))
							trymoveleft(player);
				break;
			case PLAYER_DIRECTION_MOVING_LEFT:
				if (player.speed > 0)
					if (!trymoveup(player))
						if (!trymoveleft(player))
							trymovedown(player);
				break;
			case PLAYER_DIRECTION_MOVING_RIGHT:
				if (player.speed > 0)
					if (!trymovedown(player))
						if (!trymoveright(player))
							trymoveup(player);
				break;

			case PLAYER_DIRECTION_MOVING_DOWN:
				if (player.speed > 0)
					if (!trymoveleft(player))
						if (!trymovedown(player))
							trymoveright(player);
				break;

			default:
				printf("Fatal error: processgameplaystep()");
				exit(1);
			}
			break;
		default:
			printf("Fatal error: processGamePlayer()");
			exit(1);
		}
	}
	player.speeddone += 1;
}

void Game::processgameplayplayer(SDL_Event &event) {
	// Has a key been pressed down?
	if(event.type == SDL_KEYDOWN) {
		// Player = me = ASDWE
		if (event.key.keysym.sym == SDLK_a && !(event.key.keysym.sym == SDLK_d))
			me.left();
		if (event.key.keysym.sym == SDLK_d && !(event.key.keysym.sym == SDLK_a))
			me.right();
		if (event.key.keysym.sym == SDLK_w)
			me.up();
		if (event.key.keysym.sym == SDLK_s)
			me.down();
		if (event.key.keysym.sym == SDLK_e) {
			// Then add a bullet
			me.shoot();
			// And play a corresponding sound
			// Mix_PlayChannel(0,shot,0); TODO
		}
		if (!(event.key.keysym.sym == SDLK_d) && !(event.key.keysym.sym == SDLK_a))
			me.normal();
	}
}

void Game::processgameplayenemy(SDL_Event &event) {
	// Has a key been pressed down?
	if(event.type == SDL_KEYDOWN) {
		// Enemy = otherplayer = LEFT/RIGHT/UP/DOWN/END
		if (event.key.keysym.sym == SDLK_LEFT && !(event.key.keysym.sym == SDLK_RIGHT))
			otherplayer.left();
		if (event.key.keysym.sym == SDLK_RIGHT && !(event.key.keysym.sym == SDLK_LEFT))
			otherplayer.right();
		if (event.key.keysym.sym == SDLK_UP)
			otherplayer.up();
		if (event.key.keysym.sym == SDLK_DOWN)
			otherplayer.down();
		if (event.key.keysym.sym == SDLK_END) {
			// Then add a bullet
			otherplayer.shoot();
			// And play a corresponding sound
			// Mix_PlayChannel(0,shot,0); TODO
		}
		if ((event.key.keysym.sym != SDLK_RIGHT) && (event.key.keysym.sym != SDLK_LEFT))
			otherplayer.normal();
	}
}

