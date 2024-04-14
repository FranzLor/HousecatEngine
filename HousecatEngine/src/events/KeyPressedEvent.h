#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"

//----------------------------------------------------//
//               KEY PRESSED EVENT CLASS              //
//   Represents a keyboard key press event in the     //
//          application, extending the Event.         //
//----------------------------------------------------//



class KeyPressedEvent : public Event {
public:
	SDL_Keycode keyPressedSymbol;

	KeyPressedEvent(SDL_Keycode keyPressedSymbol) : keyPressedSymbol(keyPressedSymbol) {}
};




/**
 * 
 * @class KeyPressedEvent
 * @brief Captures a single key press from the user.
 *
 * This event is dispatched when the user presses a key on the keyboard. It carries the SDL_Keycode
 * of the key that was pressed, allowing systems that handle this event to perform specific actions
 * based on the input, such as moving a character or initiating an action.
 *
 * Usage:
 * - Systems that need to react to key presses can subscribe to this event and update their state
 *   or perform actions accordingly.
 *
 * Example:
 *  
 * 	void ListenToEvents(std::unique_ptr<EventManager>& eventManager) {
 * 	    eventManager->ListenToEvent<KeyPressedEvent>(this, &KeyboardInputSystem::KeyInput);
 * 	}
 * 
 *  Listen to the KeyPressedEvent in a system
 * 
 * 	void KeyInput(KeyPressedEvent& event) {
 * 	    keyStates[event.keyPressedSymbol] = true;
 * 	    UpdateMovementDirection();
 * 	}
 * 
 *  Update the state of the system based on the key press
 *
 * Key Members:
 * - keyPressedSymbol: SDL_Keycode representing the key that was pressed.
 *
 * This event helps in decoupling the input handling logic from game logic, promoting a clean and
 * manageable code structure.
 * 
 */