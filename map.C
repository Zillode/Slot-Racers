#include "map.h"
#include "main.h"

Map::Map(Game *thegame, uint thewidth, uint theheight):
	width(thewidth),
	height(theheight),
	game(thegame),
	map(thewidth, vector<uint>(theheight, MAP_CLEAR))
{ }

Map::Map(Game *thegame, string &filename):
	width(0),
	height(0),
	game(thegame),
	map(0)
{
	// TODO: vul vector adhv filename (.bsp)
	printf("TODO!");
	exit(1);
}

Map::~Map()
{ }

void Map::setplayers() {
	game->me.move(0,0);
	game->otherplayer.move(30,30);
}

uint Map::get(uint x, uint y)
{
	assert(x < map.size());
	assert(y < map[x].size());
	return map[x][y];
}

uint Map::put(uint x, uint y, uint val)
{
	assert(x < map.size());
	assert(y < map[x].size());
	map[x][y] = val;
}

uint Map::getwidth()
{
	return width;
}

uint Map::getheight()
{
	return height;
}
