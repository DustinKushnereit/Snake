#ifndef FONT_H
#define FONT_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>
#include <Trackable.h>

class GraphicsSystem;

using namespace std;

class Font : public Trackable
{
public:
	Font(const string& path, int size);
	~Font();

	bool init(const string& path, int size);
	void cleanUp();

	int getSize() const { return mSize; }

private:
	friend class GraphicsSystem;

	ALLEGRO_FONT* mpFont;
	int mSize;
	bool mInitialized;
};
#endif