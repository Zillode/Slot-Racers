#include "map.h"
#include "main.h"

Map::Map(uint thewidth, uint theheight):
	width(thewidth),
	height(theheight),
	map(width, vector<uint>(height, MAP_CLEAR))
{ }

Map::Map(string &filename):
	width(0),
	height(0),
	map(0)
{
	// TODO: vul vector adhv filename (.bsp)
	printf("TODO!");
	exit(1);
}

Map::~Map()
{ }

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
