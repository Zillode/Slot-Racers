#include "map.h"
#include "main.h"
#include <stdio.h>

Map::Map(Game *thegame, uint thewidth, uint theheight):
	map(thewidth, vector<uint>(theheight, MAP_CLEAR)),
	game(thegame),
	width(thewidth),
	height(theheight)
{ }

Map::Map(Game *thegame, const char *filename):
	map(0),
	game(thegame),
	width(19),
	height(11)
{
	char c(0);
	uint posx(0);
	uint posy(0);
	map = vector< vector<uint> >(width, vector<uint>(height, MAP_CLEAR));
	char mapname[100];
	strcpy(mapname, "data/maps/");
	strncat(mapname, filename, 85);
	FILE *fmap = fopen(mapname, "r");
	if (fmap != NULL)
		do {
			if (posx == width && posy == height)
				break;
			c = fgetc(fmap);
			switch (c) {
			case '0':
			case '1':
				if (c == '0')
					map[posx][posy] = MAP_CLEAR;
				if (c == '1')
					map[posx][posy] = MAP_WALL;
				posx++;
				if (posx == width) {
					posx = 0;
					posy++;
				}
				if (posy == height) {
					c = EOF;
				}
				break;
			case ' ':
			case '\n':
			case EOF:
				break;
			default:
				printf("Warning: BSP != 0/1\n");
			}
		} while (c != EOF);
	else
		printf("Fatal error: opening map");
	fclose(fmap);
}

Map::~Map()
{ }

void Map::setplayers() {
	game->me.moveonmap(0,0,PLAYER_DIRECTION_MOVING_RIGHT);
	game->otherplayer.moveonmap(0,0,PLAYER_DIRECTION_MOVING_DOWN);
}

uint Map::get(uint x, uint y)
{
	if (x >= width)
		return MAP_WALL;
	if (y >= height)
		return MAP_WALL;
	return map[x][y];
}

uint Map::put(uint x, uint y, uint val)
{
	assert(x < map.size());
	assert(y < map[x].size());
	map[x][y] = val;
	return val;
}

uint Map::getwidth()
{
	return width;
}

uint Map::getheight()
{
	return height;
}
