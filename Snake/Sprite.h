#ifndef SPRITE_H
#define SPRITE_H

#include "GraphicsBuffer.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <Trackable.h>
#include <Vector2D.h>

class Sprite : public Trackable
{
public:
	Sprite();
	Sprite(GraphicsBuffer* buffer, int width, int height, Vector2D sourceLoc);
	~Sprite();

	Vector2D getSourceLoc() { return mSourceLoc; }
	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }
	GraphicsBuffer* getGraphicsBuffer() { return mpGraphicsBuffer; }

private:
	GraphicsBuffer* mpGraphicsBuffer;
	Vector2D mSourceLoc;

	int mWidth;
	int mHeight;
};
#endif