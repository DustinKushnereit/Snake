#ifndef TILES_H
#define TILES_H

#include <vector>

using namespace std;

class Tiles : public Trackable
{
public:
	Tiles() : x(0), y(0), type(0) { }

	int x, y;
	int type;
};
#endif