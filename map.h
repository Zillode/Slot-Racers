#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Map {
	public:
		Map(uint width, uint height);
		Map(string &filename);
		~Map();
		uint get(uint x,uint y);
		uint put(uint x,uint y, uint val);
		uint getwidth();
		uint getheight();
	private:
		vector< vector<uint> > map;
		Map(const Map & m);
		uint width;
		uint height;
};

#endif
