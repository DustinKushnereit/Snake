#include "Game.h"
#include <sstream>
#include <fstream>
#include <time.h>

Game Game::mpGame;

Game::Game()
{
	mGameOver = false;
	mHitSpace = false;
	mDrawLevelTwo = false;
	mDrawLevelThree = false;
	mDrawWin = false;
	srand((unsigned)time(NULL));
	mNumberOfPowerUps = 0;
	mNumberOfFood = 0;
}

Game::~Game()
{	
}

void Game::init()
{
	loadData();
	loadLevel();
	createGrid();

	mpGraphicsSystem = new GraphicsSystem(mMapWidth, mMapHeight);
	mpGraphicsSystem->init();

	mpUnit = new Unit();
	mpUnit->init();
	mpUnit->randomTile();

	mpFrameTracker = new PerformanceTracker;
	mpInputManager = new InputManager();
	mpUnitManager = new UnitManager();
	mpUnitManager->changeDirection(NONE);

	mpFont = new Font(mFontPath, mFontSize);
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpAnimation = new Animation(2000);

	mpGraphicsBufferManager->addGraphicsBuffer("Food", mSpritePath);
	mpGraphicsBufferManager->addGraphicsBuffer("Power Up", mSpritePath);
	mpGraphicsBufferManager->addGraphicsBuffer("Start Screen", mStartScreenPath);
	mpGraphicsBufferManager->addGraphicsBuffer("Level 2", mLevel2ScreenPath);
	mpGraphicsBufferManager->addGraphicsBuffer("Level 3", mLevel3ScreenPath);
	mpGraphicsBufferManager->addGraphicsBuffer("Game Over", mGameOverScreenPath);
	mpGraphicsBufferManager->addGraphicsBuffer("Win", mWinScreenPath);

	Vector2D foodSourceLocs[4];

	for (int i = 0; i < 4; i++)
	{
		int sourceX = 4 + i;
		int sourceY = 9;

		foodSourceLocs[i] = Vector2D(30 * sourceX, 30 * sourceY);
		mpAnimation->addSprite(Sprite(mpGraphicsBufferManager->getGraphicsBuffer("Food"), 30, 50, foodSourceLocs[i]));
	}

	Vector2D powerUpSourceLocs[4];

	for (int i = 0; i < 4; i++)
	{
		int sourceX = 4 + i;
		float sourceY = 4.4;

		powerUpSourceLocs[i] = Vector2D(30 * sourceX, 30 * sourceY);
		mpAnimation->addSpritePowerUp(Sprite(mpGraphicsBufferManager->getGraphicsBuffer("Power Up"), 30, 50, powerUpSourceLocs[i]));
	}
}

void Game::loadData()
{
	ifstream file;
	string fileName = "../Snake Assets/Variables.txt";
	string tempString;
	file.open(fileName);
	vector<string> txtLines;

	while (getline(file, tempString))
	{
		txtLines.push_back(tempString);
	}

	file.close();

	mMapWidth = atoi(txtLines[1].c_str());
	mMapHeight = atoi(txtLines[3].c_str());
	mSpeed = atoi(txtLines[5].c_str());
	mPointsToWin = atoi(txtLines[7].c_str());
	mLevelNumber = atoi(txtLines[9].c_str());
	mPoints = atoi(txtLines[11].c_str());
	mPowerFreq = atoi(txtLines[13].c_str());
	mTileSize = atoi(txtLines[15].c_str());
	mFontPath = txtLines[17];
	mFontSize = atoi(txtLines[19].c_str());
	mSpritePath = txtLines[21];
	mStartScreenPath = txtLines[23];
	mLevel2ScreenPath = txtLines[25];
	mLevel3ScreenPath = txtLines[27];
	mGameOverScreenPath = txtLines[29];
	mWinScreenPath = txtLines[31];
	mMaxNumberOfPowerUps = atoi(txtLines[33].c_str());

	mRowSize = mMapWidth / mTileSize;
	mCollumnSize = mMapHeight / mTileSize;
	mMapSize = mRowSize * mCollumnSize;
}

void Game::loadLevel()
{
	ifstream file;
	string fileName = "../Snake Assets/Level " + to_string(mLevelNumber) + ".txt";
	string tempString;
	file.open(fileName);

	while (getline(file, tempString))
	{
		mTileTypes.push_back(tempString);
	}

	file.close();
}

void Game::createGrid()
{
	vector< vector<Tiles> > tempTilesGrid(mRowSize, vector<Tiles>(mCollumnSize));

	for (int i = 0; i < mMapSize; i++)
	{
		tempTilesGrid[i % mRowSize][i / mCollumnSize].x = i % mRowSize;
		tempTilesGrid[i % mRowSize][i / mCollumnSize].y = i / mCollumnSize;
		tempTilesGrid[i % mRowSize][i / mCollumnSize].type = atoi(mTileTypes[i].c_str());
		mTilesGrid = tempTilesGrid;
	}
}

void Game::cleanup()
{
	delete mpGraphicsSystem;
	delete mpFont;
	delete mpAnimation;
	delete mpTimer;
	delete mpFrameTracker;
	delete mpUnit;
	delete mpUnitManager;
	delete mpGraphicsBufferManager;
	delete mpInputManager;

	mpGraphicsSystem = NULL;
	mpFont = NULL;
	mpAnimation = NULL;
	mpTimer = NULL;
	mpFrameTracker = NULL;
	mpUnit = NULL;
	mpUnitManager = NULL;
	mpGraphicsBufferManager = NULL;
	mpInputManager = NULL;
}

void Game::drawHUD()
{
	mpUnitManager->drawFood();
	mpUnitManager->drawPowerUp();

	stringstream SS;
	SS << "Points: " << mPoints << " / " << mPointsToWin << "            Level: " << mLevelNumber;
	mpGraphicsSystem->writeHUD(*mpFont, 210, 10, SS.str());	

	mpGraphicsSystem->flipDisplay();
}

void Game::drawScreens(string screenName)
{
	mpGraphicsBufferManager->drawBuffer(screenName);

	mpGraphicsSystem->flipDisplay();
}

void Game::loopGame()
{
	mpAnimation->setShouldLoop(true);
	mpAnimation->startPlaying();

	mpAnimation->setPowerUpShouldLoop(true);
	mpAnimation->startPowerUp();

	Timer tempTimer;

	mpTimer = new Timer();
	mpTimer->start();

	while (!mQuitGame)
	{
		tempTimer.start();
		mpFrameTracker->startTracking("Frame");

		if (mHitSpace == false)
		{
			mpInputManager->processSpace();
			drawScreens("Start Screen");
		}
		else if (mGameOver)
		{
			mpInputManager->processSpace();
			drawScreens("Game Over");
			resetLevel(1);
		}
		else if (mDrawLevelTwo)
		{
			mpInputManager->processSpace();
			drawScreens("Level 2");
			resetLevel(2);
		}
		else if (mDrawLevelThree)
		{
			mpInputManager->processSpace();
			drawScreens("Level 3");
			resetLevel(3);
		}
		else if (mDrawWin)
		{
			mpInputManager->processSpace();
			drawScreens("Win");
			resetLevel(1);
		}
		else
		{
			mpInputManager->processInput();

			mpGraphicsSystem->updateBitmap();

			mpGraphicsSystem->draw();

			mpUnitManager->move();

			mpUnitManager->updateFood();
			mpUnitManager->updatePowerUp();

			drawHUD();

			checkConditions();

			if (mNumberOfPowerUps < mMaxNumberOfPowerUps && mPowerFreq > (rand() % 100) && mNumberOfFood >= 1)
			{
				mNumberOfPowerUps++;
				mpUnitManager->createPowerup();
			}

			if (mNumberOfFood < 1)
				mpUnitManager->createFood();
		}

		tempTimer.sleepUntilElapsed(mSpeed);
		mpFrameTracker->stopTracking("Frame");
		mpFrameTracker->clearTracker("Frame");
	}
	mpTimer->stop();
}

void Game::checkConditions()
{
	if (mPoints >= mPointsToWin && mLevelNumber < 3)
	{
		mLevelNumber++;

		if (mLevelNumber == 2)
			mDrawLevelTwo = true;
		else
			mDrawLevelThree = true;
	}
	else if (mPoints >= mPointsToWin && mLevelNumber >= 3)
	{
		mLevelNumber = 1;
		mDrawWin = true;
	}

	if (mpAnimation->getCurrentSpriteIndex() >= 4)
		mpAnimation->setCurrentSpriteIndex(0);
}

void Game::resetLevel(int levelNumber)
{
	mpUnitManager->clearFood();
	mpUnitManager->clearPowerUp();

	mpUnitManager->changeDirection(NONE);

	mTilesGrid.clear();
	mTileTypes.clear();

	loadData();

	mLevelNumber = levelNumber;
	mNumberOfPowerUps = 0;
	mNumberOfFood = 0;

	loadLevel();
	createGrid();

	mpUnit->init();
	mpUnit->randomTile();
}