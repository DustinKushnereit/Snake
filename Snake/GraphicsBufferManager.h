#ifndef GRAPHICS_BUFFER_MANAGER_H
#define GRAPHICS_BUFFER_MANAGER_H

#include "Event.h"
#include "GraphicsBuffer.h"
#include "EventListener.h"

#include <map>

typedef string IDKey;

class GraphicsBufferManager : public EventListener
{
public:
	GraphicsBufferManager() {}
	~GraphicsBufferManager() { cleanUp(); }

	GraphicsBuffer* addGraphicsBuffer(const IDKey& key, const string& pathName);

	void deleteGraphicsBuffer(const IDKey& key);
	void drawBuffer(const IDKey& key);
	void clearBuffers();

	GraphicsBuffer* getGraphicsBuffer(const IDKey& key);

	void handleEvent(const Event& event) {}

private:
	void cleanUp();

	map<IDKey, GraphicsBuffer*> mBufferMap;
};
#endif