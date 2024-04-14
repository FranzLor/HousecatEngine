#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"

//----------------------------------------------------//
//               KEY RELEASED EVENT CLASS             //
//   Represents a keyboard key release event in the   //
//          application, extending the Event.         //
//----------------------------------------------------//



class KeyReleasedEvent : public Event {
public:
	SDL_Keycode keyReleasedSymbol;

	KeyReleasedEvent(SDL_Keycode keyReleasedSymbol) : keyReleasedSymbol(keyReleasedSymbol) {}
};




/**
 *
 * @class KeyReleasedEvent
 * @brief Captures a single key release from the user.
 *
 * This event is triggered when the user releases a key on the keyboard. It provides the SDL_Keycode
 * of the key that was released, allowing systems handling this event to update their states or
 * stop actions that were initiated by the corresponding key press.
 *
 * Usage:
 * - Systems that need to react to key releases can subscribe to this event and modify their state
 *   or cease actions accordingly.
 *
 * Example:
 * 	void ListenToEvents(std::unique_ptr<EventManager>& eventManager) {
 * 	    eventManager->ListenToEvent<KeyReleasedEvent>(this, &KeyboardInputSystem::KeyRelease);
 * 	}
 * 
 *  Listen to the KeyReleasedEvent in a system
 *
 * 	void KeyRelease(KeyReleasedEvent& event) {
 * 	    keyStates[event.keyReleasedSymbol] = false;
 * 	    UpdateMovementDirection();
 * 	}
 * 
 *  Update the state of the system based on the key release
 *
 * Key Members:
 * - keyReleasedSymbol: SDL_Keycode representing the key that was released.
 *
 * Like the KeyPressedEvent, this event supports clean separation of input handling from other
 * game logic, facilitating more modular and maintainable code.
 * 
 */