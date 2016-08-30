#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <map>
#include <Trackable.h>

class Event;
class EventListener;
enum EventType;

using namespace std;

// Event System class from Dean Lawson
class EventSystem : public Trackable
{
public:
	EventSystem();
	~EventSystem();

	void fireEvent(const Event& theEvent);
	void addListener(EventType type, EventListener* pListener);
	void removeListener(EventType type, EventListener* pListener);
	void removeListenerFromAllEvents(EventListener* pListener);

private:
	static EventSystem* msInstance;
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents(const Event& theEvent);

};
#endif

extern EventSystem* gpEventSystem;