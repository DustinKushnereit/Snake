#include "GraphicsBufferManager.h"
#include "Game.h"

void GraphicsBufferManager::cleanUp()
{
	map<IDKey, GraphicsBuffer*>::iterator iter;

	for (iter = mBufferMap.begin(); iter != mBufferMap.end(); ++iter)
	{
		GraphicsBuffer* pBuffer = iter->second;
		delete pBuffer;
	}
}

GraphicsBuffer* GraphicsBufferManager::addGraphicsBuffer(const IDKey& key, const string& path)
{
	GraphicsBuffer* newBuffer = new GraphicsBuffer(path);

	mBufferMap[key] = newBuffer;

	return newBuffer;
}

void GraphicsBufferManager::deleteGraphicsBuffer(const IDKey& key)
{
	map<IDKey, GraphicsBuffer*>::iterator iter = mBufferMap.find(key);

	if (iter != mBufferMap.end())
	{
		delete iter->second;
		mBufferMap.erase(iter);
	}
}

GraphicsBuffer* GraphicsBufferManager::getGraphicsBuffer(const IDKey& key)
{
	map<IDKey, GraphicsBuffer*>::iterator iter = mBufferMap.find(key);

	if (iter != mBufferMap.end())
		return iter->second;
	else
		return NULL;
}

void GraphicsBufferManager::drawBuffer(const IDKey& key)
{
	map<IDKey, GraphicsBuffer*>::iterator iter = mBufferMap.find(key);

	if (iter != mBufferMap.end())
	{
		Game::getGame().getGraphicsSystem()->draw
			(
			iter->second,
			Vector2D(30, 30),
			Sprite(iter->second, iter->second->getWidth(), iter->second->getHeight(), Vector2D(0, 0)),
			1.0f
			);
	}
}

void GraphicsBufferManager::clearBuffers()
{
	cleanUp();
}