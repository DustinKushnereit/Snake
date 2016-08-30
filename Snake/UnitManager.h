#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include "EventListener.h"
#include "Unit.h"
#include "GraphicsBufferManager.h"

#include <map>

using namespace std;

class UnitManager : public EventListener
{
public:
	UnitManager();
	~UnitManager();

	Unit* createAndAddFood(const Vector2D location, Animation* pAnimation);
	Unit* createAndAddPowerUp(const Vector2D location, Animation* pAnimation);

	void clearFood();
	void clearPowerUp();

	void updateFood();
	void updatePowerUp();

	void drawFood();
	void drawPowerUp();

	void cleanUpFood();
	void cleanUpPowerUp();

	void move();
	void changeDirection(Directions direction);
	void createPowerup();
	void createFood();

	void handleEvent(const Event& event);

private:
	map<int, Unit*> mFoodMap;
	map<int, Unit*> mPowerUpMap;

	int mIDFood;
	int mIDPowerUp;

	bool mShouldAnimateFood;
	bool mShouldAnimatePowerUp;

	Unit* mpUnit;

	Animation* mpAnimation;
};
#endif