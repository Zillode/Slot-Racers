#ifndef MAP_H
#define MAP_H

#include "main.h"

using std::vector;
using std::string;

class Map {
	public:
		Map(uint width, uint height);
		Map(string &filename);
		~Map();
		uint get(uint x,uint y);
		uint put(uint x,uint y, uint val);
		const uint width;
		const uint height;
	private:
		vector< vector<uint> > map;
		Map(const Map & m);
};

#endif
