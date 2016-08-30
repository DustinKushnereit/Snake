#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <Trackable.h>

class Event;

// Event Listener Class from Dean Lawson
class EventListener : public Trackable
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;

private:

};
#endif