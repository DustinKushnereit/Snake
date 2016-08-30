#ifndef GRAPHICS_BUFFER_H
#define GRAPHICS_BUFFER_H

#include "Color.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <Trackable.h>
#include <string>

using namespace std;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;
public:
	GraphicsBuffer(int width, int height);
	GraphicsBuffer(string path);
	~GraphicsBuffer();

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

private:
	ALLEGRO_BITMAP* mpBitmap;

	int mWidth;
	int mHeight;
	static int sNumInstances;

	bool shouldDestroy;
	
	GraphicsBuffer(ALLEGRO_BITMAP* bitmap);
	ALLEGRO_BITMAP* getBitmap() { return mpBitmap; }
};
#endif