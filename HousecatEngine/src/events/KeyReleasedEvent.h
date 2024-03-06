#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"

class KeyReleasedEvent : public Event {
public:
	SDL_Keycode keyReleasedSymbol;

	KeyReleasedEvent(SDL_Keycode keyReleasedSymbol) : keyReleasedSymbol(keyReleasedSymbol) {}
};