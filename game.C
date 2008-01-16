#include "main.h"
#include "game.h"

Game::Game(): state(GAME_PLAY),
	me(),
	otherplayer(),
	map(NULL)
{
	map = new Map(50,50);
	mapid = 0;
	map->put(20,20,MAP_WALL); // TODO
}

Game::~Game()
{ }

bool Game::stop()
{
	return (state == GAME_STOP);
}

void Game::setmap(string mapname)
{
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
    if(!paused)
    {
      sdlgt+=dt*10;
    }

	// Check if we have some interesting events...
    SDL_Event event;
	SDL_PollEvent(&event);
	// If we must quit, then do so
	if(event.type == SDL_QUIT) { done = 1; }

	// Has a key been pressed down?
	if(event.type == SDL_KEYDOWN) {
		// If it was escape then quit
		if(event.key.keysym.sym == SDLK_ESCAPE)
		{
			state = GAME_STOP;
		}

		if(event.key.keysym.sym == SDLK_p)
		{
			if (state == GAME_PAUSE)
				state = GAME_PLAY
			else
				state = GAME_PAUSE;
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
			default:
				printf("Fatal error: CheckEvents()");
				exit(1);
		}
	}


}

void Game::processgameplay(SDL_Event &event) {
		processgameplayeplayer(event);
		if (network_game)
			processgameplaynetworkenemy()
		else
			processgameplayenemy(event);
		processgameplaystep(player);
		processgameplaystep(enemy);
}

void Game::processgameplaynetworkenemy() {
	// TODO
	printf("Fatal Error: processgameplaynetworkenemy()");
	exit(1);
}

void Game::processgameplayplayer(SDL_Event &event) {
		// Player = me = ASDWE
		if (event.key.keysym.sym == SDLK_a && !(event.key.keysym.sym == SDLK_d))
			player.left();
		if (event.key.keysym.sym == SDLK_d && !(event.key.keysym.sym == SDLK_a))
			player.right();
		if (event.key.keysym.sym == SDLK_w)
			player.up();
		if (event.key.keysym.sym == SDLK_s)
			player.down();
		if (event.key.keysym.sym == SDLK_e) {
			// Then add a bullet
			player.shoot();
			// And play a corresponding sound
			// Mix_PlayChannel(0,shot,0); TODO
		}
		
}

bool Game::trymoveup(Player &player, uint speed) {
	uint posx = player.posx;
	uint posy = player.posy;
	if (speed == 0)
		return false;
	if (speed > 0 && (map->get(posx, posy + speed) == MAP_CLEAR)) {
		player.move(posx, posy + speed);
		return true;
	} else {
		return trymoveup(player, speed - 1);
	}
}

bool Game::trymovedown(Player &player, uint speed) {
	uint posx = player.posx;
	uint posy = player.posy;
	if (speed == 0)
		return false;
	if (speed > 0 && (map->get(posx, posy - speed) == MAP_CLEAR)) {
		player.move(posx, posy - speed);
		return true;
	} else {
		return trymoveup(player, speed - 1);
	}
}

bool Game::trymoveleft(Player &player, uint speed) {
	uint posx = player.posx;
	uint posy = player.posy;
	if (speed == 0)
		return false;
	if (speed > 0 && (map->get(posx - speed, posy) == MAP_CLEAR)) {
		player.move(posx - speed, posy);
		return true;
	} else {
		return trymoveup(player, speed - 1);
	}
}

bool Game::trymoveright(Player &player, uint speed) {
	uint posx = player.posx;
	uint posy = player.posy;
	if (speed == 0)
		return false;
	if (speed > 0 && (map->get(posx + speed, posy) == MAP_CLEAR)) {
		player.move(posx + speed, posy);
		return true;
	} else {
		return trymoveup(player, speed - 1);
	}
}

void Game::processgameplaystep(Player &player) {
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
							if (!trymoveup(player, player.speed))
								// If move up failed, do random right/left
								if ((rand() % 2) == 0) {
									if (!trymoveright(player, player.speed))
										// If move right also failed, try left
										trymoveleft(player, player.speed);
								} else {
									if (!trymoveleft(player, player.speed))
										// If move right also failed, try left
										trymoveright(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_LEFT:
						if (player.speed > 0)
							if (!trymoveleft(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveup(player, player.speed))
										trymovedown(player, player.speed);
								} else {
									if (!trymovedown(player, player.speed))
										trymoveup(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_RIGHT:
						if (player.speed > 0)
							if (!trymoveright(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveup(player, player.speed))
										trymovedown(player, player.speed);
								} else {
									if (!trymovedown(player, player.speed))
										trymoveup(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_DOWN:
						if (player.speed > 0)
							if (!trymovedown(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveleft(player, player.speed))
										trymoveright(player, player.speed);
								} else {
									if (!trymoveright(player, player.speed))
										trymoveleft(player, player.speed);
								}
						break;
					default:
						printf("Fatal error: processgameplaystep()");
						exit(1);
				}
			// ================= DIRECTION LEFT =================
			// When the player wants to turn left
			case PLAYER_DIRECTION_LEFT:
				// If it's possible, just go in the same direction
				switch (player.directionmoving) {
					case PLAYER_DIRECTION_MOVING_UP:
						// Try to move up
						if (player.speed > 0)
							// When player has speed > 0, he can move
							if (!trymoveleft(player, player.speed))
								// If move up failed, do random right/left
								if ((rand() % 2) == 0) {
									if (!trymoveright(player, player.speed))
										// If move right also failed, try left
										trymoveleft(player, player.speed);
								} else {
									if (!trymoveleft(player, player.speed))
										// If move right also failed, try left
										trymoveright(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_LEFT:
						if (player.speed > 0)
							if (!trymoveleft(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveup(player, player.speed))
										trymovedown(player, player.speed);
								} else {
									if (!trymovedown(player, player.speed))
										trymoveup(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_RIGHT:
						if (player.speed > 0)
							if (!trymoveright(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveup(player, player.speed))
										trymovedown(player, player.speed);
								} else {
									if (!trymovedown(player, player.speed))
										trymoveup(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_DOWN:
						if (player.speed > 0)
							if (!trymovedown(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveleft(player, player.speed))
										trymoveright(player, player.speed);
								} else {
									if (!trymoveright(player, player.speed))
										trymoveleft(player, player.speed);
								}
						break;
					default:
						printf("Fatal error: processgameplaystep()");
						exit(1);
				}
				break;
			// ================= DIRECTION LEFT =================
			// When the player wants to turn left
			case PLAYER_DIRECTION_NORMAL:
				// If it's possible, just go in the same direction
				switch (player.directionmoving) {
					case PLAYER_DIRECTION_MOVING_UP:
						// Try to move up
						if (player.speed > 0)
							// When player has speed > 0, he can move
							if (!trymoveup(player, player.speed))
								// If move up failed, do random right/left
								if ((rand() % 2) == 0) {
									if (!trymoveright(player, player.speed))
										// If move right also failed, try left
										trymoveleft(player, player.speed);
								} else {
									if (!trymoveleft(player, player.speed))
										// If move right also failed, try left
										trymoveright(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_LEFT:
						if (player.speed > 0)
							if (!trymoveleft(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveup(player, player.speed))
										trymovedown(player, player.speed);
								} else {
									if (!trymovedown(player, player.speed))
										trymoveup(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_RIGHT:
						if (player.speed > 0)
							if (!trymoveright(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveup(player, player.speed))
										trymovedown(player, player.speed);
								} else {
									if (!trymovedown(player, player.speed))
										trymoveup(player, player.speed);
								}
						break;
					case PLAYER_DIRECTION_MOVING_DOWN:
						if (player.speed > 0)
							if (!trymovedown(player, player.speed))
								if ((rand() % 2) == 0) {
									if (!trymoveleft(player, player.speed))
										trymoveright(player, player.speed);
								} else {
									if (!trymoveright(player, player.speed))
										trymoveleft(player, player.speed);
								}
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


void Game::processgameplayenemy(SDL_Event &event) {
		// Enemy = otherplayer = LEFT/RIGHT/UP/DOWN/END
		if (event.key.keysym.sym == SDLK_LEFT && !(event.key.keysym.sym == SDLK_RIGHT))
			enemy.left();
		if (event.key.keysym.sym == SDLK_RIGHT && !(event.key.keysym.sym == SDLK_LEFT))
			enemy.right();
		if (event.key.keysym.sym == SDLK_UP)
			enemy.up();
		if (event.key.keysym.sym == SDLK_DOWN)
			enemy.down();
		if (event.key.keysym.sym == SDLK_END) {
			// Then add a bullet
			enemy.shoot();
			// And play a corresponding sound
			// Mix_PlayChannel(0,shot,0); TODO
		}
}

