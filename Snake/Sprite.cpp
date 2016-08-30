#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(GraphicsBuffer* buffer, int width, int height, Vector2D sourceLoc)
{
	mpGraphicsBuffer = buffer;
	mWidth = width;
	mHeight = height;
	mSourceLoc = sourceLoc;
}

Sprite::~Sprite()
{
}