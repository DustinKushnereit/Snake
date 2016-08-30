#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Trackable.h>

struct Rect : public Trackable
{
	Rect() { set(0, 0, 0, 0); }
	Rect(int x, int y, int width, int height) { set(x, y, width, height); }

	void set(int x, int y, int width, int height);
	void toZero() { set(0, 0, 0, 0); }

	int getWidth() { return(width); }
	int getHeight() { return(height); }

	int getX() { return(x); }
	int getY() { return(y); }

	int x, y, width, height;
};
#endif