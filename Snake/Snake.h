#ifndef SNAKE_H
#define SNAKE_H

#include "Tiles.h"

class Snake : public Trackable
{
public:
	vector<Tiles> vBody;
	vector<Tiles>::iterator it;

	int headPosX;
	int headPosY;
};
#endif