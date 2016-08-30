/*

Mid Term - Snake
Created by Dustin Kushnereit

*/

#include "Game.h"

#include <MemoryTracker.h>
#include <Timer.h>
#include <PerformanceTracker.h>

int main()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	pPerformanceTracker->startTracking("Init");

	gpEventSystem = new EventSystem();

	Game::getGame().init();
	Game::getGame().loopGame();
	Game::getGame().cleanup();

	delete gpEventSystem;
	delete pPerformanceTracker;

	gpEventSystem = NULL;
	pPerformanceTracker = NULL;

	gMemoryTracker.reportAllocations(std::cout);

	system("pause");

	return 0;
}