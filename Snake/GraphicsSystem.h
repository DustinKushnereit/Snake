#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include "Sprite.h"
#include "Font.h"
#include "Tiles.h"
#include "Event.h"

#include <Trackable.h>
#include <allegro5/allegro_primitives.h>

class GraphicsSystem : public Trackable
{
	friend class Game;
	friend class InputManager;
public:
	GraphicsSystem(int width, int height);
	~GraphicsSystem();

	void init();
	void cleanup();

	void draw(GraphicsBuffer*, Color color);
	void draw(Vector2D drawLoc, Sprite sprite, float scale = 1.0f);
	void draw(GraphicsBuffer* newBuffer, Vector2D drawLoc, Sprite sprite, float scale = 1.0f);
	void draw();
	void drawLines();
	void drawSnake();

	void writeText(Vector2D drawLoc, Font* font, Color color, std::string text);
	void writeText(GraphicsBuffer* newBuffer, Vector2D drawLoc, Font* font, Color color, string text);

	void writeHUD(Font& font, int MESSAGE_TEXT_X, int MESSAGE_TEXT_Y, string &frames);
	void writeRate(Font& font, int MESSAGE_TEXT_X, int MESSAGE_TEXT_Y, string &frames);

	void flipDisplay();

	int getDisplayWidth() { return mDisplayWidth; }
	int getDisplayHeight() { return mDisplayHeight; }

	GraphicsBuffer* getCurrentBackBuffer() { return mpCurrentBackBuffer; }

	void updateBitmap();

protected:
	ALLEGRO_DISPLAY* mpDisplay;
	GraphicsBuffer* mpCurrentBackBuffer;
	ALLEGRO_BITMAP* mTilesBitmap;

	int mDisplayWidth;
	int mDisplayHeight;
};
#endif