#include "Font.h"

Font::Font(const string& path, int size)
{
	init(path, size);
}

Font::~Font()
{
	if (mInitialized)
		cleanUp();
}

bool Font::init(const string& path, int size)
{
	if (mInitialized)
		return false;

	mSize = size;
	mpFont = al_load_font(path.c_str(), size, 0);
	mInitialized = true;

	return true;
}

void Font::cleanUp()
{
	al_destroy_font(mpFont);
	mpFont = NULL;
	mInitialized = false;
}