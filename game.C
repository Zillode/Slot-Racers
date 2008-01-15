
#include "game.h"

Game::Game(): state(GAME_PLAY), me(), otherplayer()
{ }

Game::~Game()
{ }

bool Game::stop()
{
	return (state == GAME_STOP);
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
}
