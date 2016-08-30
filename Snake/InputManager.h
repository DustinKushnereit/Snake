#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "EventSystem.h"
#include "EventListener.h"
#include "allegro5\keyboard.h"

class InputManager : public EventListener
{
public:
	InputManager();
	~InputManager();

	void handleEvent(const Event& event);
	void processInput();
	void processSpace();

private:
	ALLEGRO_KEYBOARD_STATE* mpKeyboardState;
	ALLEGRO_EVENT_QUEUE *mpEventQueue;

	bool mKeyPressed;
	void cleanup();
};
#endif