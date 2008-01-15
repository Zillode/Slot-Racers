#include "map.h"

Map::Map(uint width, uint height):
	map(width, vector<uint>(height,MAP_CLEAR))
{ }

Map::Map(string &filename)
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


