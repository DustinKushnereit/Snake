#ifndef COLOR_H
#define COLOR_H

#include <Trackable.h>
typedef unsigned short ushort;

struct Color : public Trackable
{
	Color() { setRGBA(0, 0, 0, 255); }
	Color(ushort r, ushort g, ushort b, ushort a = 255) { setRGBA(r, g, b, a); }

	void setRGB(ushort r, ushort g, ushort b) { setRGBA(r, g, b, a); }
	void setRGBA(ushort r, ushort g, ushort b, ushort a = 255);

	ushort r, g, b, a;
};
#endif