#ifndef ANIMATION_H
#define ANIMATION_H

#include "Sprite.h"
#include "Timer.h"

#include <vector>
#include <Trackable.h>

using namespace std;

class Animation : public Trackable
{
public:
	Animation() {};
	Animation(int msPerFrame);
	~Animation();

	void addSprite(Sprite& sprite);
	void addSpritePowerUp(Sprite& sprite);
	void updateAnimation();
	void updatePowerUpAnimation();

	Sprite& getCurrentSprite() { return mCurrentSprite; }
	void setCurrentSpriteIndex(int tmpValue) { mCurrentSpriteIndex = tmpValue; }
	int getCurrentSpriteIndex() { return mCurrentSpriteIndex; }

	Sprite& getCurrentPowerUpSprite() { return mCurrentPowerUpSprite; }
	void setCurrentPowerUpSpriteIndex(int tmpValue) { mCurrentPowerUpSpriteIndex = tmpValue; }
	int getCurrentPowerUpSpriteIndex() { return mCurrentPowerUpSpriteIndex; }

	void startPlaying() { mIsPlaying = true; }
	void stopPlaying() { mIsPlaying = false; }

	void setShouldLoop(bool shouldLoop) { mShouldLoop = shouldLoop; }
	void setMSPerFrame(int newMSPerFrame) { mMSPerFrame = newMSPerFrame; }

	void startPowerUp() { mPowerUpIsPlaying = true; }
	void stopPowerUp() { mPowerUpIsPlaying = false; }

	void setPowerUpShouldLoop(bool shouldLoop) { mPowerUpShouldLoop = shouldLoop; }
	void setMSPerPowerUpFrame(int newMSPerFrame) { mMSPerPowerUpFrame = newMSPerFrame; }

private:
	vector<Sprite>* mpListOfSprites;
	vector<Sprite>* mpListOfPowerUpSprites;

	int mMSPerFrame;
	int mMSUntilSpriteChange;

	int mNumberOfSprites;
	int mCurrentSpriteIndex;

	int mMSPerPowerUpFrame;
	int mMSUntilPowerUpSpriteChange;
	int mNumberOfPowerUpSprites;
	int mCurrentPowerUpSpriteIndex;

	bool mIsPlaying;
	bool mShouldLoop;
	bool mTimerStarted;

	bool mPowerUpIsPlaying;
	bool mPowerUpShouldLoop;
	bool mPowerUpTimerStarted;

	Sprite mCurrentSprite;
	Sprite mCurrentPowerUpSprite;
	Timer* mpTimer;	
	Timer* mpPowerUpTimer;
};
#endif