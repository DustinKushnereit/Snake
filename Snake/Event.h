#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <trackable.h>
#include <Vector2D.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,

	SPACE_EVENT,
	EXIT_EVENT,
	LEFT_EVENT,
	UP_EVENT,
	RIGHT_EVENT,
	DOWN_EVENT,

	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] =
{
	"Space Event",
	"Exit Event",
	"Left Event",
	"Up Event",
	"Right Event",
	"Down Event"
};

// Event class from Dean Lawson
class Event : public Trackable
{
public:
	Event(EventType type);
	Event(EventType type, const Vector2D& vector);
	virtual ~Event();

	EventType getType() const { return mType; };
	Vector2D getVector() const { return mVector; };
	const string& getEventName() const;

private:
	EventType mType;
	Vector2D mVector;
};
#endif