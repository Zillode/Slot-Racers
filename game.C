#include "main.h"
#include "game.h"

Game::Game():
	state(GAME_PLAY),
	me(this),
	otherplayer(this),
	mapid(0),
	map(NULL),
	sdlgt(0),
	resolution_x(VID_RESOLUTION_X),
	resolution_y(VID_RESOLUTION_X),
	block_width(0),
	block_height(0),
	bound_X_0(0),
	bound_X_y(0),
	bound_Y_0(0),
	bound_Y_x(0),
	td(0), td2(0), dt(0),
	graphics(NULL),
	networkgame(false)
{
	map = new Map(this, "map1.bsp");
	block_width = VID_RESOLUTION_X / map->getwidth();
	uint remains = VID_RESOLUTION_X - (map->getwidth() * block_width);
	bound_X_0 = remains / 2;
	bound_X_y = VID_RESOLUTION_X - bound_X_0 - (map->getwidth() * block_width);
	block_height = VID_RESOLUTION_Y / map->getheight();
	remains = VID_RESOLUTION_Y - (map->getheight() * block_height);
	bound_Y_0 = remains / 2;
	bound_Y_x = VID_RESOLUTION_Y - bound_Y_0 - (map->getheight() * block_height);
}

Game::~Game()
{
	if (map != NULL)
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

void Game::setmap(const char *mapname)
{
	if (map)
		delete map;
	map = new Map(this, mapname);
	++mapid;
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

bool Game::trymoveup(Player &player, bool check) {
	if (moveallowed(player, 0, -1)) {
		player.move(player.posx, player.posy - 1);
		return true;
	} else {
		return false;
	}
}

bool Game::trymovedown(Player &player, bool check) {
	if (moveallowed(player, 0, 1)) {
		player.move(player.posx, player.posy + 1);
		return true;
	} else {
		return false;
	}
}

bool Game::trymoveleft(Player &player, bool check) {
	if (moveallowed(player, -1, 0)) {
		player.move(player.posx - 1, player.posy);
		return true;
	} else {
		return false;
	}
}

bool Game::trymoveright(Player &player, bool check) {
	if (moveallowed(player, 1, 0)) {
		player.move(player.posx + 1, player.posy);
		return true;
	} else {
		return false;
	}
}

bool Game::moveallowed(Player &player, int x, int y) {
	int newposx = player.posx + bound_X_0 + x;
	int newposy = player.posy + bound_Y_0 + y;
	int newblockleft = ((newposx - (player.width / 2)) / block_width);
	int newblockright = ((newposx + (((player.width % 2) == 0) ? ((player.width / 2) - 1) : (player.width / 2))) / block_width);
	int newblockup = ((newposy - (player.height / 2)) / block_height);
	int newblockdown = ((newposy + (((player.height % 2) == 0) ? ((player.height / 2) - 1) : (player.height / 2))) / block_height);
	printf("%i,%i\n", newblockleft, newblockup);
	printf("%i,%i\n", newblockleft, newblockdown);
	printf("%i,%i\n", newblockright, newblockdown);
	printf("%i,%i\n", newblockright, newblockdown);
	printf("-------\n");
	return ((map->get(newblockleft, newblockup) == MAP_CLEAR) &&
					(map->get(newblockleft, newblockdown) == MAP_CLEAR) &&
					(map->get(newblockright, newblockup) == MAP_CLEAR) &&
					(map->get(newblockright, newblockdown) == MAP_CLEAR));
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
			break;
			// ================= DIRECTION LEFT =================
			// When the player wants to turn to left
		case PLAYER_DIRECTION_LEFT:
			switch (player.directionmoving) {
			case PLAYER_DIRECTION_MOVING_UP:
				if (player.speed > 0)
					// When player has speed > 0, he can move
					if (!trymoveleft(player, true))
						// If move left fails when going up, continue to go up
						if (!trymoveup(player))
							// If move up failed, do left
							trymoveright(player);
				break;
			case PLAYER_DIRECTION_MOVING_LEFT:
				if (player.speed > 0)
					if (!trymovedown(player, true))
						if (!trymoveleft(player))
							trymoveup(player);
				break;
			case PLAYER_DIRECTION_MOVING_RIGHT:
				if (player.speed > 0)
					if (!trymoveup(player, true))
						if (!trymoveright(player))
							trymovedown(player);
				break;

			case PLAYER_DIRECTION_MOVING_DOWN:
				if (player.speed > 0)
					if (!trymoveright(player, true))
						if (!trymovedown(player))
							trymoveleft(player);
				break;

			default:
				printf("Fatal error: processgameplaystep()");
				exit(1);
			}
			break;
			break;
			// ================= DIRECTION RIGHT =================
			// When the player wants to turn to right
		case PLAYER_DIRECTION_RIGHT:
			switch (player.directionmoving) {
			case PLAYER_DIRECTION_MOVING_UP:
				if (player.speed > 0)
					// When player has speed > 0, he can move
					if (!trymoveright(player, true))
						// If move right fails when going up, continue to go up
						if (!trymoveup(player))
							trymoveleft(player);
				break;
			case PLAYER_DIRECTION_MOVING_LEFT:
				if (player.speed > 0)
					if (!trymoveup(player, true))
						if (!trymoveleft(player))
							trymovedown(player);
				break;
			case PLAYER_DIRECTION_MOVING_RIGHT:
				if (player.speed > 0)
					if (!trymovedown(player, true))
						if (!trymoveright(player))
							trymoveup(player);
				break;

			case PLAYER_DIRECTION_MOVING_DOWN:
				if (player.speed > 0)
					if (!trymoveleft(player, true))
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
	if (event.type == SDL_KEYDOWN) {
		// Player = me = ASDWE
		if (event.key.keysym.sym == SDLK_a && (event.key.keysym.sym != SDLK_d))
			me.left();
		if (event.key.keysym.sym == SDLK_d && (event.key.keysym.sym != SDLK_a))
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
	} else if(event.type == SDL_KEYUP) {
		if ((event.key.keysym.sym == SDLK_d) && (me.directiongoal == PLAYER_DIRECTION_RIGHT))
			me.normal();
		if ((event.key.keysym.sym == SDLK_a) && (me.directiongoal == PLAYER_DIRECTION_LEFT))
			me.normal();
	}
}

void Game::processgameplayenemy(SDL_Event &event) {
	// Has a key been pressed down?
	if (event.type == SDL_KEYDOWN) {
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
	} else if(event.type == SDL_KEYUP) {
		if ((event.key.keysym.sym == SDLK_RIGHT) && (otherplayer.directiongoal == PLAYER_DIRECTION_RIGHT))
			otherplayer.normal();
		if ((event.key.keysym.sym == SDLK_LEFT) && (otherplayer.directiongoal == PLAYER_DIRECTION_LEFT))
			otherplayer.normal();
	}
}

