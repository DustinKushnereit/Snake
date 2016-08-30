#include "UnitManager.h"
#include "Game.h"

UnitManager::UnitManager()
{
	mIDFood = 0;
	mIDPowerUp = 0;
	mShouldAnimateFood = true;
	mShouldAnimatePowerUp = true;
	mpUnit = new Unit;

	gpEventSystem->addListener(LEFT_EVENT, this);
	gpEventSystem->addListener(RIGHT_EVENT, this);
	gpEventSystem->addListener(UP_EVENT, this);
	gpEventSystem->addListener(DOWN_EVENT, this);
}

UnitManager::~UnitManager()
{
	cleanUpFood();
	cleanUpPowerUp();

	gpEventSystem->removeListener(LEFT_EVENT, this);
	gpEventSystem->removeListener(RIGHT_EVENT, this);
	gpEventSystem->removeListener(UP_EVENT, this);
	gpEventSystem->removeListener(DOWN_EVENT, this);

	delete mpUnit;

	mpUnit = NULL;
}

void UnitManager::cleanUpFood()
{
	map<int, Unit*>::iterator iter;

	for (iter = mFoodMap.begin(); iter != mFoodMap.end(); ++iter)
	{
		Unit* pUnit = iter->second;
		delete pUnit;
	}

	mIDFood = 0;
	mFoodMap.clear();
}

void UnitManager::cleanUpPowerUp()
{
	map<int, Unit*>::iterator iter;

	for (iter = mPowerUpMap.begin(); iter != mPowerUpMap.end(); ++iter)
	{
		Unit* pUnit = iter->second;
		delete pUnit;
	}

	mIDPowerUp = 0;
	mPowerUpMap.clear();
}

Unit* UnitManager::createAndAddFood(const Vector2D location, Animation* pAnimation)
{
	Unit* pUnit = new Unit(pAnimation);
	pUnit->setLocation(location - Vector2D(30, 30));
	
	mFoodMap[mIDFood] = pUnit;
	mIDFood++;
	
	return pUnit;
}

Unit* UnitManager::createAndAddPowerUp(const Vector2D location, Animation* pAnimation)
{
	Unit* pUnit = new Unit(pAnimation);
	pUnit->setLocation(location - Vector2D(30, 30));

	mPowerUpMap[mIDPowerUp] = pUnit;
	mIDPowerUp++;

	return pUnit;
}

void UnitManager::handleEvent(const Event& event)
{
	if (event.getType() == SPACE_EVENT)
		mShouldAnimateFood = !mShouldAnimateFood;
	else if (event.getType() == LEFT_EVENT)
	{
		if (mpUnit->getDirection() == RIGHT)
			changeDirection(RIGHT);
		else
			changeDirection(LEFT);
	}
	else if (event.getType() == RIGHT_EVENT)
	{
		if (mpUnit->getDirection() == LEFT)
			changeDirection(LEFT);
		else
			changeDirection(RIGHT);
	}
	else if (event.getType() == UP_EVENT)
	{
		if (mpUnit->getDirection() == DOWN)
			changeDirection(DOWN);
		else
			changeDirection(UP);
	}
	else if (event.getType() == DOWN_EVENT)
	{
		if (mpUnit->getDirection() == UP)
			changeDirection(UP);
		else
			changeDirection(DOWN);
	}
}

void UnitManager::clearFood()
{
	cleanUpFood();
}

void UnitManager::clearPowerUp()
{
	cleanUpPowerUp();
}

void UnitManager::updateFood()
{
	map<int, Unit*>::iterator iter;

	for (iter = mFoodMap.begin(); iter != mFoodMap.end(); ++iter)
	{
		if (iter->second != NULL)
		{
			if (mShouldAnimateFood)
			{
				iter->second->updateUnit();
			}
		}
	}
}

void UnitManager::updatePowerUp()
{
	map<int, Unit*>::iterator iter;

	for (iter = mPowerUpMap.begin(); iter != mPowerUpMap.end(); ++iter)
	{
		if (iter->second != NULL)
		{
			if (mShouldAnimatePowerUp)
			{
				iter->second->updatePowerUp();
			}
		}
	}
}

void UnitManager::drawFood()
{
	map<int, Unit*>::iterator iter;

	for (iter = mFoodMap.begin(); iter != mFoodMap.end(); ++iter)
	{
		if (iter->second != NULL)
			iter->second->drawUnit();
	}
}

void UnitManager::drawPowerUp()
{
	map<int, Unit*>::iterator iter;

	for (iter = mPowerUpMap.begin(); iter != mPowerUpMap.end(); ++iter)
	{
		if (iter->second != NULL)
			iter->second->drawPowerUp();
	}
}

void UnitManager::changeDirection(Directions direction)
{
	mpUnit->setDirection(direction);
}

void UnitManager::move()
{
	mpUnit->move();
}

void UnitManager::createPowerup()
{
	mpUnit->createPowerUp();
}

void UnitManager::createFood()
{
	mpUnit->randomTile();
}