#ifndef GAME_H
#define GAME_H

#include "GraphicsSystem.h"
#include "Animation.h"
#include "Unit.h"
#include "InputManager.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "Rectangle.h"

#include "Tiles.h"
#include "Snake.h"

#include <PerformanceTracker.h>
#include <Trackable.h>
#include <Timer.h>

#include <iostream>
#include <ctime>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

class Game : public Trackable
{
	friend class Unit;
	friend class GraphicsSystem;
public:
	static Game& getGame() { return mpGame; }
	~Game();

	void init();
	void loadData();
	void loadLevel();
	void createGrid();
	void cleanup();
	void drawHUD();
	void drawScreens(string screenName);
	void loopGame();
	void checkConditions();
	void resetLevel(int levelNumber);

	void shouldContinueGame(bool quit) { mQuitGame = quit; }
	void hitSpace(bool space) { mHitSpace = space; }

	GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; }
	Animation* getAnimation() { return mpAnimation; }
	Snake* getSnake() { return &mSnake; }
	UnitManager* getUnitManager() { return mpUnitManager; }
	GraphicsBufferManager* getGraphicsBufferManager() { return mpGraphicsBufferManager; }

	bool getGameOver() { return mGameOver; }
	int getSpeed() { return mSpeed; }
	int getWidth() const { return mMapWidth; }
	int getHeight() const { return mMapHeight; }
	int getTileSize() const { return mTileSize; }
	int getRow() const { return mRowSize; }
	int getCollumn() const { return mCollumnSize; }

	void setTilesType(int x, int y, int type) { mTilesGrid[x][y].type = type; }
	void setPoints(int point) { mPoints += point; }
	void setSpeed(int tmpValue) { mSpeed = tmpValue; }
	void setGameOver(bool tmpValue) { mGameOver = tmpValue; }
	void setLevelTwo(bool tmpValue) { mDrawLevelTwo = tmpValue; }
	void setLevelThree(bool tmpValue) { mDrawLevelThree = tmpValue; }
	void setWin(bool tmpValue) { mDrawWin = tmpValue; }
	void decreaseNumberOfPowerUps() { mNumberOfPowerUps--; }
	void decreaseNumberOfFood() { mNumberOfFood--; }
	void increaseNumberOfFood() { mNumberOfFood++; }
	//void setNumberOfFood( int tmpValue) { mNumberOfFood = tmpValue; }

protected:
	Game();

	bool mQuitGame;
	bool mHitSpace;
	bool mGameOver;
	bool mDrawLevelTwo;
	bool mDrawLevelThree;
	bool mDrawWin;

	int mMapWidth;
	int mMapHeight;
	float mSpeed;
	int mPointsToWin;
	int mLevelNumber;
	int mPoints;
	int mPowerFreq;
	int mTileSize;
	string mFontPath;
	int mFontSize;
	string mSpritePath;
	int mRowSize;
	int mCollumnSize;
	int mMapSize;
	vector<string> mTileTypes;
	string mStartScreenPath;
	string mLevel2ScreenPath;
	string mLevel3ScreenPath;
	string mGameOverScreenPath;
	string mWinScreenPath;
	int mNumberOfPowerUps;
	int mNumberOfFood;
	int mMaxNumberOfPowerUps;

	InputManager* mpInputManager;
	Font* mpFont;
	Unit* mpUnit;
	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpGraphicsBufferManager;
	Animation* mpAnimation;
	GraphicsSystem* mpGraphicsSystem;
	Sprite mSprite;

	Timer* mpTimer;
	PerformanceTracker* mpFrameTracker;

	vector< vector<Tiles> > mTilesGrid;

	Snake mSnake;

	static Game mpGame;
};
#endif