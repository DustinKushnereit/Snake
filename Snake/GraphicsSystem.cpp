#include "GraphicsSystem.h"
#include "Game.h"

GraphicsSystem::GraphicsSystem(int width, int height)
{
	mDisplayWidth = width;
	mDisplayHeight = height;
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

void GraphicsSystem::init()
{
	if (!al_init())
		cout << "This could be a problem... Allegro didn't initialize properly.\n";

	if (!al_init_image_addon())
		cout << "This could be a problem... Allegro couldn't initialize the image addon.\n";

	al_init_font_addon();

	if (!al_init_ttf_addon())
		cout << "This could be a problem... Allegro couldn't initialize the ttf addon.\n";

	al_init_primitives_addon();

	if (!al_init_primitives_addon())
		cout << "This could be a problem... Allegro couldn't initialize the primitives addon.\n";

	mpDisplay = al_create_display(420, 420);

	mpCurrentBackBuffer = new GraphicsBuffer(al_get_backbuffer(mpDisplay));

	mTilesBitmap = al_create_bitmap(Game::getGame().getWidth(), Game::getGame().getHeight());
}

void GraphicsSystem::cleanup()
{
	delete mpCurrentBackBuffer;
	al_destroy_display(mpDisplay);
	al_destroy_bitmap(mTilesBitmap);
}

void GraphicsSystem::draw(GraphicsBuffer* buffer, Color color)
{
	al_set_target_bitmap(buffer->getBitmap());

	al_clear_to_color(al_map_rgba(color.r, color.g, color.b, color.a));

	al_set_target_bitmap(al_get_backbuffer(mpDisplay));

	al_draw_bitmap(buffer->getBitmap(), 0, 0, 0);
}

void GraphicsSystem::draw(Vector2D drawLoc, Sprite sprite, float scale)
{
	al_draw_scaled_bitmap(
		al_get_backbuffer(mpDisplay),
		sprite.getSourceLoc().getX(),
		sprite.getSourceLoc().getY(),
		sprite.getWidth() * scale,
		sprite.getHeight() * scale,
		drawLoc.getX(),
		drawLoc.getY(),
		sprite.getWidth(),
		sprite.getHeight(),
		0);
}

void GraphicsSystem::draw(GraphicsBuffer* newBuffer, Vector2D drawLoc, Sprite sprite, float scale)
{
	*mpCurrentBackBuffer = *newBuffer;

	al_draw_scaled_bitmap(
		newBuffer->getBitmap(),
		sprite.getSourceLoc().getX(),
		sprite.getSourceLoc().getY(),
		sprite.getWidth(),
		sprite.getHeight(),
		drawLoc.getX(),
		drawLoc.getY(),
		sprite.getWidth() * scale,
		sprite.getHeight() * scale,
		0
		);
}

void GraphicsSystem::draw()
{
	al_clear_to_color(al_map_rgb(240, 240, 240));

	al_draw_bitmap(mTilesBitmap, 0, 0, NULL);

	drawSnake();
	drawLines();
}

void GraphicsSystem::writeHUD(Font& font, int MESSAGE_TEXT_X, int MESSAGE_TEXT_Y, string &frames)
{
	al_draw_filled_rectangle(0, 0, 419, 34, al_map_rgb(0, 0, 0));

	al_draw_text(font.mpFont, al_map_rgba(255, 0, 0, 1), MESSAGE_TEXT_X, MESSAGE_TEXT_Y, ALLEGRO_ALIGN_CENTRE, frames.c_str());
}

void GraphicsSystem::writeRate(Font& font, int MESSAGE_TEXT_X, int MESSAGE_TEXT_Y, string &frames)
{
	al_draw_rectangle(600, 5, 790, 35, al_map_rgb(255, 0, 0), 4);

	al_draw_filled_rectangle(600, 5, 790, 35, al_map_rgb(0, 0, 0));

	al_draw_text(font.mpFont, al_map_rgba(255, 0, 0, 1), MESSAGE_TEXT_X, MESSAGE_TEXT_Y, ALLEGRO_ALIGN_CENTRE, frames.c_str());
}

void GraphicsSystem::writeText(Vector2D drawLoc, Font* font, Color color, std::string text)
{
	al_draw_text(
		font->mpFont,
		al_map_rgb(0, 0, 0),
		drawLoc.getX(),
		drawLoc.getY(),
		0,
		text.c_str()
		);
}

void GraphicsSystem::writeText(GraphicsBuffer* newBuffer, Vector2D drawLoc, Font* font, Color color, std::string text)
{
	mpCurrentBackBuffer = newBuffer;

	al_draw_text(
		font->mpFont,
		al_map_rgba(color.r, color.g, color.b, color.a),
		drawLoc.getX(),
		drawLoc.getY(),
		0,
		text.c_str()
		);
}

void GraphicsSystem::flipDisplay()
{
	al_flip_display();
}

void GraphicsSystem::drawLines()
{
	for (int x = 0; x < Game::getGame().getRow(); x++)
		al_draw_line(
		x * Game::getGame().getTileSize(),
		0,
		x * Game::getGame().getTileSize(),
		Game::getGame().getWidth(),
		al_map_rgb(255, 0, 0),
		3);

	for (int y = 0; y < Game::getGame().getCollumn(); y++)
		al_draw_line(
		0,
		y * Game::getGame().getTileSize(),
		Game::getGame().getWidth(),
		y * Game::getGame().getTileSize(),
		al_map_rgb(255, 0, 0),
		3);
}

void GraphicsSystem::drawSnake()
{
	for (Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin(); Game::getGame().getSnake()->it != Game::getGame().getSnake()->vBody.end(); Game::getGame().getSnake()->it++)
		al_draw_filled_rectangle(
		Game::getGame().getSnake()->it->x * Game::getGame().getTileSize(),
		Game::getGame().getSnake()->it->y * Game::getGame().getTileSize(),
		Game::getGame().getSnake()->it->x * Game::getGame().getTileSize() + Game::getGame().getTileSize(),
		Game::getGame().getSnake()->it->y * Game::getGame().getTileSize() + Game::getGame().getTileSize(),
		al_map_rgb(0, 0, 255));
}

void GraphicsSystem::updateBitmap()
{
	al_set_target_bitmap(mTilesBitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	for (int x = 0; x < Game::getGame().mRowSize; x++)
	{
		for (int y = 0; y < Game::getGame().mCollumnSize; y++)
		{
			if (Game::getGame().mTilesGrid[x][y].type == 1) //Wall
			{
				al_draw_filled_rectangle(
					x * Game::getGame().mTileSize,
					y * Game::getGame().mTileSize,
					x * Game::getGame().mTileSize + Game::getGame().mTileSize,
					y * Game::getGame().mTileSize + Game::getGame().mTileSize,
					al_map_rgb(0, 0, 0));
			}
			else if (Game::getGame().mTilesGrid[x][y].type == 2) //Food
			{
				Game::getGame().getUnitManager()->createAndAddFood
					(
						Vector2D(
									x * Game::getGame().mTileSize + 30,
									y * Game::getGame().mTileSize + 22
								),
						Game::getGame().getAnimation()
					);

				al_draw_filled_rectangle(
					x * Game::getGame().mTileSize,
					y * Game::getGame().mTileSize,
					x * Game::getGame().mTileSize + Game::getGame().mTileSize,
					y * Game::getGame().mTileSize + Game::getGame().mTileSize,
					al_map_rgb(255, 255, 0));
			}
			else if (Game::getGame().mTilesGrid[x][y].type == 3) //Power Up
			{
				Game::getGame().getUnitManager()->createAndAddPowerUp
					(
					Vector2D(
					x * Game::getGame().mTileSize + 30,
					y * Game::getGame().mTileSize + 22
					),
					Game::getGame().getAnimation()
					);

				al_draw_filled_rectangle(
					x * Game::getGame().mTileSize,
					y * Game::getGame().mTileSize,
					x * Game::getGame().mTileSize + Game::getGame().mTileSize,
					y * Game::getGame().mTileSize + Game::getGame().mTileSize,
					al_map_rgb(150, 0, 190));
			}
		}
	}

	al_set_target_bitmap(al_get_backbuffer(mpDisplay));
}