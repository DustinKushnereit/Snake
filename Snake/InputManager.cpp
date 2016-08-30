#include "InputManager.h"
#include "Game.h"

InputManager::InputManager()
{
	al_install_keyboard();

	mpKeyboardState = new ALLEGRO_KEYBOARD_STATE;
	mKeyPressed = false;

	gpEventSystem->addListener(EXIT_EVENT, this);
	gpEventSystem->addListener(SPACE_EVENT, this);
	
	mpEventQueue = al_create_event_queue();
	al_get_keyboard_state(mpKeyboardState);

	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mpEventQueue, al_get_display_event_source(Game::getGame().getGraphicsSystem()->mpDisplay));
}

InputManager::~InputManager()
{
	cleanup();
}

void InputManager::cleanup()
{
	gpEventSystem->removeListener(EXIT_EVENT, this);
	gpEventSystem->removeListener(SPACE_EVENT, this);
	al_destroy_event_queue(mpEventQueue);
	delete mpKeyboardState;
}

void InputManager::handleEvent(const Event& event)
{
	if (event.getType() == EXIT_EVENT)
		Game::getGame().shouldContinueGame(true);
	else if (event.getType() == SPACE_EVENT)
	{
		Game::getGame().hitSpace(true);
		Game::getGame().setGameOver(false);
		Game::getGame().setLevelTwo(false);
		Game::getGame().setLevelThree(false);
		Game::getGame().setWin(false);
	}
}

void InputManager::processInput()
{
	al_get_keyboard_state(mpKeyboardState);

	ALLEGRO_EVENT tempEvent;

	while (al_get_next_event(mpEventQueue, &tempEvent))
	{
		if (tempEvent.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (tempEvent.keyboard.keycode == ALLEGRO_KEY_LEFT)
				gpEventSystem->fireEvent(Event(LEFT_EVENT));
			else if (tempEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				gpEventSystem->fireEvent(Event(RIGHT_EVENT));
			else if (tempEvent.keyboard.keycode == ALLEGRO_KEY_UP)
				gpEventSystem->fireEvent(Event(UP_EVENT));
			else if (tempEvent.keyboard.keycode == ALLEGRO_KEY_DOWN)
				gpEventSystem->fireEvent(Event(DOWN_EVENT));
			else if (tempEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				gpEventSystem->fireEvent(Event(EXIT_EVENT));
		}
	}
}

void InputManager::processSpace()
{
	al_get_keyboard_state(mpKeyboardState);

	ALLEGRO_EVENT tempEvent;

	while (al_get_next_event(mpEventQueue, &tempEvent))
	{
		if (tempEvent.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (tempEvent.keyboard.keycode == ALLEGRO_KEY_SPACE)
				gpEventSystem->fireEvent(Event(SPACE_EVENT));
			else if (tempEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				gpEventSystem->fireEvent(Event(EXIT_EVENT));
		}
	}
}