#ifndef UNIT_H
#define UNIT_H

#include "Vector2D.h"
#include "Animation.h"

#include <Trackable.h>

using namespace std;

enum Directions
{
	NONE,
	LEFT,
	UP,
	RIGHT,
	DOWN
};

class Unit : public Trackable
{
	friend class Game;
public:
	Unit();
	Unit(Animation* animation);
	~Unit();	

	void updateUnit();
	void updatePowerUp();
	void drawUnit();
	void drawPowerUp();

	void randomTile();
	void createPowerUp();
	void move();

	void setX(int x) { mX = x; }
	void setY(int y) { mY = y; }
	void setLocation(Vector2D newLoc);

	int getX() { return mX; }
	int getY() { return mY; }

	Vector2D getLocation() { return mLocation; }
	Animation* getAnimation() { return mAnimation; }
	int getPoints() { return mPoints; }
	void setDirection(Directions direction) { mDirection = direction; }
	Directions getDirection() { return mDirection; }

private:
	Directions mDirection;
	void init();

	int mX;
	int mY;
	int mPoints;

	Vector2D mLocation;

	Animation* mAnimation;
};
#endif