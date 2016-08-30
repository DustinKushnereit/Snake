#include "GraphicsBuffer.h"

int GraphicsBuffer::sNumInstances = 0;

GraphicsBuffer::GraphicsBuffer(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mpBitmap = al_create_bitmap(width, height);

	shouldDestroy = true;
	sNumInstances++;
}

GraphicsBuffer::GraphicsBuffer(string path)
{
	mpBitmap = al_load_bitmap(path.c_str());

	mWidth = al_get_bitmap_width(mpBitmap);

	mHeight = al_get_bitmap_height(mpBitmap);

	shouldDestroy = true;
	sNumInstances++;
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* bitmap)
{
	mpBitmap = bitmap;

	mWidth = al_get_bitmap_width(mpBitmap);
	mHeight = al_get_bitmap_height(mpBitmap);

	shouldDestroy = false;
	sNumInstances++;
}

GraphicsBuffer::~GraphicsBuffer()
{
	sNumInstances--;
	if (shouldDestroy)
	{
		if (sNumInstances <= 0)
			al_destroy_bitmap(mpBitmap);
	}
}