#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"

class KeyPressedEvent : public Event {
public:
	SDL_Keycode keyPressedSymbol;

	KeyPressedEvent(SDL_Keycode keyPressedSymbol) : keyPressedSymbol(keyPressedSymbol) {}
};