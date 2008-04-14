#include "main.h"
#include "game.h"
#include <algorithm>

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
	prevtime(0),
	graphics(NULL),
	networkgame(false)
{
	map = new Map(this, "map1.bsp");
	// Width
	block_width = VID_RESOLUTION_X / map->getwidth();
	uint remains = VID_RESOLUTION_X - (map->getwidth() * block_width);
	bound_X_0 = remains / 2;
	bound_X_y = VID_RESOLUTION_X - bound_X_0 - (map->getwidth() * block_width);
	// Height
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
	unsigned long speed = 50;
	unsigned long time = std::min(SDL_GetTicks() - prevtime, speed);
	SDL_Delay(speed - time);
	prevtime = SDL_GetTicks();

	td2=SDL_GetTicks();
	dt=((float)(td2-td))*0.1;
	td=td2;
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
	for (uint i(0); i < 3; ++i) {
		processgameplaystep(me);
		processgameplaystep(otherplayer);
		processgameplaystep(me.bullet);
		processgameplaystep(otherplayer.bullet);
		checkbullets();
	}
}

void Game::checkbullets() {
	if (me.bullet.shot && collide(me.bullet, otherplayer)) {
		me.bullet.stop();
		me.score += 1;
		otherplayer.directionmoving = me.bullet.directionmoving;
		otherplayer.speed = PLAYER_MAX_SPEED;
		for (uint i(0); i < 70; ++i) {
			processgameplaystep(otherplayer);
		}
	}
	if (otherplayer.bullet.shot && collide(otherplayer.bullet, me)) {
		otherplayer.bullet.stop();
		otherplayer.score += 1;
		me.speed = PLAYER_MAX_SPEED;
		me.directionmoving = otherplayer.bullet.directionmoving;
		for (uint i(0); i < 70; ++i) {
			processgameplaystep(me);
		}
	}
}

bool Game::collide(MovingObject &object1, MovingObject &object2) {
	int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;
	uint block_width_offset = block_width * 0.80;
	uint block_height_offset = block_height * 0.80;
    left1 = object1.posx + ((block_width - (block_width_offset)) /2);
    left2 = object2.posx + ((block_width - (block_width_offset)) /2);
    right1 = left1 + block_width_offset;
    right2 = left2 + block_width_offset;
    top1 = object1.posy + ((block_width - block_height_offset) /2);
    top2 = object2.posy + ((block_height_offset - block_height_offset) /2);
    bottom1 = top1 + block_height_offset;
    bottom2 = top2 + block_height_offset;

    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;

    if (right1 < left2) return false;
    if (left1 > right2) return false;

    return true;
}

void Game::processgameplaynetworkenemy() {
	// TODO
	printf("Fatal Error: processgameplaynetworkenemy()");
	exit(1);
}

void Game::setgraphics(Graphics *thegraphics) {
	graphics = thegraphics;
}

bool Game::trymoveup(MovingObject &movingobject, bool check) {
	if (moveallowed(movingobject, 0, -1)) {
		movingobject.move(movingobject.posx, movingobject.posy - 1);
		return true;
	} else {
		return false;
	}
}

bool Game::trymovedown(MovingObject &movingobject, bool check) {
	if (moveallowed(movingobject, 0, 1)) {
		movingobject.move(movingobject.posx, movingobject.posy + 1);
		return true;
	} else {
		return false;
	}
}

bool Game::trymoveleft(MovingObject &movingobject, bool check) {
	if (moveallowed(movingobject, -1, 0)) {
		movingobject.move(movingobject.posx - 1, movingobject.posy);
		return true;
	} else {
		return false;
	}
}

bool Game::trymoveright(MovingObject &movingobject, bool check) {
	if (moveallowed(movingobject, 1, 0)) {
		movingobject.move(movingobject.posx + 1, movingobject.posy);
		return true;
	} else {
		return false;
	}
}

bool Game::moveallowed(MovingObject &movingobject, int x, int y) {
	int newposx = movingobject.posx + x;
	int newposy = movingobject.posy + y;
	int newblockleft = ((newposx - bound_X_0 - (block_width / 2)) / block_width);
	int newblockright = ((newposx - bound_X_0 + (((block_width % 2) == 0) ? ((block_width / 2) - 1) : (block_width / 2))) / block_width);
	int newblockup = ((newposy - bound_Y_0 - (block_height / 2)) / block_height);
	int newblockdown = ((newposy - bound_Y_0 + (((block_height % 2) == 0) ? ((block_height / 2) - 1) : (block_height / 2))) / block_height);
	/*printf("%i,%i\n", newblockleft, newblockup);
	printf("%i,%i\n", newblockleft, newblockdown);
	printf("%i,%i\n", newblockright, newblockdown);
	printf("%i,%i\n", newblockright, newblockdown);
	printf("-------\n");*/
	return ((map->get(newblockleft, newblockup) == MAP_CLEAR) &&
					(map->get(newblockleft, newblockdown) == MAP_CLEAR) &&
					(map->get(newblockright, newblockup) == MAP_CLEAR) &&
					(map->get(newblockright, newblockdown) == MAP_CLEAR));
}

void Game::processgameplaystep(MovingObject &movingobject) {
	if (movingobject.speeddone > OBJECT_MAX_SPEED)
		movingobject.speeddone = 0;
	// If his speed is high enough to move at this point, make a move!
	if (movingobject.speed > movingobject.speeddone) {
		switch (movingobject.directiongoal) {
			// ================= DIRECTION NORMAL =================
			// When the movingobject doesn't wants to turn
		case PLAYER_DIRECTION_NORMAL:
			// If it's possible, just go in the same direction
			switch (movingobject.directionmoving) {
			case PLAYER_DIRECTION_MOVING_UP:
				// Try to move up
				if (movingobject.speed > 0)
					// When movingobject has speed > 0, he can move
					if (!trymoveup(movingobject))
						// If move up failed, do random right/left
						if ((rand() % 2) == 0) {
							if (!trymoveright(movingobject))
								// If move right also failed, try left
								trymoveleft(movingobject);
						} else {
							if (!trymoveleft(movingobject))
								// If move right also failed, try left
								trymoveright(movingobject);
						}
				break;
			case PLAYER_DIRECTION_MOVING_LEFT:
				if (movingobject.speed > 0)
					if (!trymoveleft(movingobject))
						if ((rand() % 2) == 0) {
							if (!trymoveup(movingobject))
								trymovedown(movingobject);
						} else {
							if (!trymovedown(movingobject))
								trymoveup(movingobject);
						}
				break;
			case PLAYER_DIRECTION_MOVING_RIGHT:
				if (movingobject.speed > 0)
					if (!trymoveright(movingobject))
						if ((rand() % 2) == 0) {
							if (!trymoveup(movingobject))
								trymovedown(movingobject);
						} else {
							if (!trymovedown(movingobject))
								trymoveup(movingobject);
						}
				break;
			case PLAYER_DIRECTION_MOVING_DOWN:
				if (movingobject.speed > 0)
					if (!trymovedown(movingobject))
						if ((rand() % 2) == 0) {
							if (!trymoveleft(movingobject))
								trymoveright(movingobject);
						} else {
							if (!trymoveright(movingobject))
								trymoveleft(movingobject);
						}
				break;
			default:
				printf("Fatal error: processgameplaystep()");
				exit(1);
			}
			break;
			// ================= DIRECTION LEFT =================
			// When the movingobject wants to turn to left
		case PLAYER_DIRECTION_LEFT:
			switch (movingobject.directionmoving) {
			case PLAYER_DIRECTION_MOVING_UP:
				if (movingobject.speed > 0)
					// When movingobject has speed > 0, he can move
					if (!trymoveleft(movingobject, true))
						// If move left fails when going up, continue to go up
						if (!trymoveup(movingobject))
							// If move up failed, do left
							trymoveright(movingobject);
				break;
			case PLAYER_DIRECTION_MOVING_LEFT:
				if (movingobject.speed > 0)
					if (!trymovedown(movingobject, true))
						if (!trymoveleft(movingobject))
							trymoveup(movingobject);
				break;
			case PLAYER_DIRECTION_MOVING_RIGHT:
				if (movingobject.speed > 0)
					if (!trymoveup(movingobject, true))
						if (!trymoveright(movingobject))
							trymovedown(movingobject);
				break;

			case PLAYER_DIRECTION_MOVING_DOWN:
				if (movingobject.speed > 0)
					if (!trymoveright(movingobject, true))
						if (!trymovedown(movingobject))
							trymoveleft(movingobject);
				break;

			default:
				printf("Fatal error: processgameplaystep()");
				exit(1);
			}
			break;
			// ================= DIRECTION RIGHT =================
			// When the movingobject wants to turn to right
		case PLAYER_DIRECTION_RIGHT:
			switch (movingobject.directionmoving) {
			case PLAYER_DIRECTION_MOVING_UP:
				if (movingobject.speed > 0)
					// When movingobject has speed > 0, he can move
					if (!trymoveright(movingobject, true))
						// If move right fails when going up, continue to go up
						if (!trymoveup(movingobject))
							trymoveleft(movingobject);
				break;
			case PLAYER_DIRECTION_MOVING_LEFT:
				if (movingobject.speed > 0)
					if (!trymoveup(movingobject, true))
						if (!trymoveleft(movingobject))
							trymovedown(movingobject);
				break;
			case PLAYER_DIRECTION_MOVING_RIGHT:
				if (movingobject.speed > 0)
					if (!trymovedown(movingobject, true))
						if (!trymoveright(movingobject))
							trymoveup(movingobject);
				break;

			case PLAYER_DIRECTION_MOVING_DOWN:
				if (movingobject.speed > 0)
					if (!trymoveleft(movingobject, true))
						if (!trymovedown(movingobject))
							trymoveright(movingobject);
				break;

			default:
				printf("Fatal error: processgameplaystep()");
				exit(1);
			}
			break;
		default:
			printf("Fatal error: processGameMovingObject()");
			exit(1);
		}
	}
	movingobject.speeddone += 1;
}

void Game::processgameplayplayer(SDL_Event &event) {
	// Has a key been pressed down?
	if (event.type == SDL_KEYDOWN) {
		// MovingObject = me = ASDWE
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

