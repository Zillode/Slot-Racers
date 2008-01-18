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
	game->me.moveonmap(10,10);
	game->otherplayer.moveonmap(30,30);
}

uint Map::get(uint x, uint y)
{
	if ((x < 0) || (x > width))
		return MAP_WALL;
	if ((y < 0) || (y > height))
		return MAP_WALL;
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
