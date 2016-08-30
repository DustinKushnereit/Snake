#include "Unit.h"
#include "Game.h"

Unit::Unit()
{
}

Unit::Unit(Animation* animation)
{
	mAnimation = animation;
}

Unit::~Unit()
{
}

void Unit::init()
{
	Game::getGame().getSnake()->vBody.clear();
	Game::getGame().getSnake()->vBody.push_back(Game::getGame().mTilesGrid[1][1]);
}

void Unit::updateUnit()
{
	mAnimation->updateAnimation();
}

void Unit::updatePowerUp()
{
	mAnimation->updatePowerUpAnimation();
}

void Unit::drawUnit()
{
	Game::getGame().getGraphicsSystem()->draw(mAnimation->getCurrentSprite().getGraphicsBuffer(), mLocation, mAnimation->getCurrentSprite());
}

void Unit::drawPowerUp()
{
	Game::getGame().getGraphicsSystem()->draw(mAnimation->getCurrentPowerUpSprite().getGraphicsBuffer(), mLocation, mAnimation->getCurrentPowerUpSprite());
}

void Unit::setLocation(Vector2D newLoc)
{
	mLocation = newLoc;
	mX = newLoc.getX();
	mY = newLoc.getY();
}

void Unit::randomTile()
{
	srand(time(0));

	int tmpX = rand() % Game::getGame().getRow();
	int tmpY = rand() % Game::getGame().getCollumn();

	if (tmpX == 0)
		tmpX++;

	if (tmpX == Game::getGame().getRow() - 1)
		tmpX--;

	if (tmpY == 0)
		tmpY++;

	if (tmpY == Game::getGame().getCollumn() - 1)
		tmpY--;

	for (Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin(); Game::getGame().getSnake()->it != Game::getGame().getSnake()->vBody.end(); Game::getGame().getSnake()->it++)
	{
		while (Game::getGame().getSnake()->it->x == tmpX && Game::getGame().getSnake()->it->y == tmpY)
		{
			tmpX = rand() % Game::getGame().getRow();
			tmpY = rand() % Game::getGame().getCollumn();

			if (tmpX == 0)
				tmpX++;

			if (tmpX == Game::getGame().getRow() - 1)
				tmpX--;

			if (tmpY == 0)
				tmpY++;

			if (tmpY == Game::getGame().getCollumn() - 1)
				tmpY--;

			Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin();
		}
	}

	if (Game::getGame().mTilesGrid[tmpX][tmpY].type == 0)
	{
		Game::getGame().setTilesType(tmpX, tmpY, 2);
		Game::getGame().increaseNumberOfFood();
	}
}

void Unit::createPowerUp()
{
	srand(time(0));

	int tmpX = rand() % Game::getGame().getRow();
	int tmpY = rand() % Game::getGame().getCollumn();

	if (tmpX == 0)
		tmpX++;

	if (tmpX == Game::getGame().getRow() - 1)
		tmpX--;

	if (tmpY == 0)
		tmpY++;

	if (tmpY == Game::getGame().getCollumn() - 1)
		tmpY--;

	for (Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin(); Game::getGame().getSnake()->it != Game::getGame().getSnake()->vBody.end(); Game::getGame().getSnake()->it++)
	{
		while (Game::getGame().getSnake()->it->x == tmpX && Game::getGame().getSnake()->it->y == tmpY)
		{
			tmpX = rand() % Game::getGame().getRow();
			tmpY = rand() % Game::getGame().getCollumn();

			if (tmpX == 0)
				tmpX++;

			if (tmpX == Game::getGame().getRow() - 1)
				tmpX--;

			if (tmpY == 0)
				tmpY++;

			if (tmpY == Game::getGame().getCollumn() - 1)
				tmpY--;

			Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin();
		}
	}

	if (Game::getGame().mTilesGrid[tmpX][tmpY].type == 0)
		Game::getGame().setTilesType(tmpX, tmpY, 3);
}

void Unit::move()
{
	if (Game::getGame().getGameOver())
		return;

	Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin();

	int tmpX, tmpY;

	tmpX = Game::getGame().getSnake()->headPosX;
	tmpY = Game::getGame().getSnake()->headPosY;

	Game::getGame().getSnake()->headPosX = Game::getGame().getSnake()->it->x;
	Game::getGame().getSnake()->headPosY = Game::getGame().getSnake()->it->y;

	switch (mDirection)
	{
	case NONE:
		break;

	case LEFT:
		Game::getGame().getSnake()->it->x--;
		break;

	case RIGHT:
		Game::getGame().getSnake()->it->x++;
		break;

	case UP:
		Game::getGame().getSnake()->it->y--;
		break;

	case DOWN:
		Game::getGame().getSnake()->it->y++;
		break;
	}

	if (Game::getGame().mTilesGrid[Game::getGame().getSnake()->it->x][Game::getGame().getSnake()->it->y].type == 1)//Wall
	{
		Game::getGame().setGameOver(true);
		return;
	}

	if (Game::getGame().mTilesGrid[Game::getGame().getSnake()->it->x][Game::getGame().getSnake()->it->y].type == 2)//Food
	{
		int tempPoint = 1;
		Game::getGame().setPoints(tempPoint);

		Game::getGame().decreaseNumberOfFood();

		int tmpSpeed = Game::getGame().getSpeed();

		if (tmpSpeed > 100)
			Game::getGame().setSpeed(tmpSpeed -= 10);

		Game::getGame().setTilesType(Game::getGame().getSnake()->it->x, Game::getGame().getSnake()->it->y, 0);

		Game::getGame().getSnake()->vBody.push_back(Game::getGame().mTilesGrid[tmpX][tmpY]);

		randomTile();

		Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin();

		Game::getGame().getUnitManager()->clearFood();
	}

	if (Game::getGame().mTilesGrid[Game::getGame().getSnake()->it->x][Game::getGame().getSnake()->it->y].type == 3)//Point PowerUp
	{
		int tempPoint = 2;
		Game::getGame().setPoints(tempPoint);

		int tmpSpeed = Game::getGame().getSpeed();

		if (tmpSpeed > 100)
			Game::getGame().setSpeed(tmpSpeed -= 20);

		Game::getGame().decreaseNumberOfPowerUps();

		Game::getGame().setTilesType(Game::getGame().getSnake()->it->x, Game::getGame().getSnake()->it->y, 0);

		Game::getGame().getSnake()->vBody.push_back(Game::getGame().mTilesGrid[tmpX][tmpY]);
		Game::getGame().getSnake()->vBody.push_back(Game::getGame().mTilesGrid[tmpX][tmpY]);

		Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin();

		Game::getGame().getUnitManager()->clearPowerUp();
	}

	tmpX = Game::getGame().getSnake()->it->x;
	tmpY = Game::getGame().getSnake()->it->y;

	for (++Game::getGame().getSnake()->it; Game::getGame().getSnake()->it != Game::getGame().getSnake()->vBody.end(); ++Game::getGame().getSnake()->it)
	{
		if (Game::getGame().getSnake()->it->x == tmpX && Game::getGame().getSnake()->it->y == tmpY)
		{
			Game::getGame().setGameOver(true);
			return;
		}
	}

	Game::getGame().getSnake()->it = Game::getGame().getSnake()->vBody.begin();

	for (++Game::getGame().getSnake()->it; Game::getGame().getSnake()->it != Game::getGame().getSnake()->vBody.end(); ++Game::getGame().getSnake()->it)
	{
		tmpX = Game::getGame().getSnake()->it->x;
		tmpY = Game::getGame().getSnake()->it->y;

		Game::getGame().getSnake()->it->x = Game::getGame().getSnake()->headPosX;
		Game::getGame().getSnake()->it->y = Game::getGame().getSnake()->headPosY;

		Game::getGame().getSnake()->headPosX = tmpX;
		Game::getGame().getSnake()->headPosY = tmpY;
	}
}