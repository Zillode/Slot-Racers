
#include "game.h"

Game::Game(): status(GAME_PLAY)
{ }

Game::~Game()
{ }

bool Game::stop()
{
	return (status == GAME_STOP);
}

void Game::check_events()
{
	// TODO
}
