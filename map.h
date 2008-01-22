#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Game;

class Map {
	public:
		Map(Game *game, uint width, uint height);
		Map(Game *game, const char *filename);
		~Map();
		uint get(uint x,uint y);
		uint put(uint x,uint y, uint val);
		uint getwidth();
		uint getheight();
		void setplayers();
	private:
		vector< vector<uint> > map;
		Map(const Map & m);
		Game *game;
		uint width;
		uint height;
};

#endif
