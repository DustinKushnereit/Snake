#include "Animation.h"

Animation::Animation(int msPerFrame)
{
	mMSPerFrame = msPerFrame;
	mMSUntilSpriteChange = msPerFrame;

	mMSPerPowerUpFrame = msPerFrame;
	mMSUntilPowerUpSpriteChange = msPerFrame;

	mpListOfSprites = new vector<Sprite>();
	mpListOfPowerUpSprites = new vector<Sprite>();

	mNumberOfSprites = 0;
	mCurrentSpriteIndex = 0;

	mNumberOfPowerUpSprites = 0;
	mCurrentPowerUpSpriteIndex = 0;

	mIsPlaying = false;
	mPowerUpIsPlaying = false;
}

Animation::~Animation()
{
	delete mpListOfSprites;
	delete mpListOfPowerUpSprites;
	delete mpTimer;
	delete mpPowerUpTimer;
}

void Animation::addSprite(Sprite& sprite)
{
	mpListOfSprites->push_back(sprite);

	mNumberOfSprites++;

	if (mNumberOfSprites == 1)
		mCurrentSprite = sprite;
}

void Animation::addSpritePowerUp(Sprite& sprite)
{
	mpListOfPowerUpSprites->push_back(sprite);

	mNumberOfPowerUpSprites++;

	if (mNumberOfPowerUpSprites == 1)
		mCurrentPowerUpSprite = sprite;
}

void Animation::updateAnimation()
{
	if (mIsPlaying)
	{
		if (!mTimerStarted)
		{
			mpTimer = new Timer();
			mpTimer->start();
			mTimerStarted = true;
		}

		mMSUntilSpriteChange -= mpTimer->getElapsedTime();

		if (mMSUntilSpriteChange <= 0)
		{
			mCurrentSpriteIndex++;

			if (mCurrentSpriteIndex >= mNumberOfSprites)
			{
				mCurrentSpriteIndex = 0;

				if (!mShouldLoop)
				{
					mIsPlaying = false;
					mTimerStarted = false;
					mpTimer->stop();
				}
			}
			else
			{
				mCurrentSprite = mpListOfSprites->at(mCurrentSpriteIndex);

				mMSUntilSpriteChange = mMSPerFrame;

				mpTimer->start();
			}
		}
	}
}

void Animation::updatePowerUpAnimation()
{
	if (mPowerUpIsPlaying)
	{
		if (!mPowerUpTimerStarted)
		{
			mpPowerUpTimer = new Timer();
			mpPowerUpTimer->start();
			mPowerUpTimerStarted = true;
		}

		mMSUntilPowerUpSpriteChange -= mpPowerUpTimer->getElapsedTime();

		if (mMSUntilPowerUpSpriteChange <= 0)
		{
			mCurrentPowerUpSpriteIndex++;

			if (mCurrentPowerUpSpriteIndex >= mNumberOfPowerUpSprites)
			{
				mCurrentPowerUpSpriteIndex = 0;

				if (!mPowerUpShouldLoop)
				{
					mPowerUpIsPlaying = false;
					mPowerUpTimerStarted = false;
					mpPowerUpTimer->stop();
				}
			}
			else
			{
				mCurrentPowerUpSprite = mpListOfPowerUpSprites->at(mCurrentPowerUpSpriteIndex);

				mMSUntilPowerUpSpriteChange = mMSPerPowerUpFrame;

				mpPowerUpTimer->start();
			}
		}
	}
}