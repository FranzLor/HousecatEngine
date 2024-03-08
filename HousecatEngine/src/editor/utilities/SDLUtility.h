#pragma once

#include <SDL.h>

#include <glm/glm.hpp>

#include <memory>

struct SDLUtility {
public:
	SDLUtility() = default;
	~SDLUtility() = default;

	void operator()(SDL_Window* window) const {
		SDL_DestroyWindow(window);
	}

	void operator()(SDL_Renderer* renderer) const {
		SDL_DestroyRenderer(renderer);
	}

	void operator()(SDL_Texture* texture) const {
		SDL_DestroyTexture(texture);
	}
};

using EditorWindow = std::unique_ptr<SDL_Window, SDLUtility>;
using EditorRenderer = std::unique_ptr<SDL_Renderer, SDLUtility>;
using EditorTexture = std::unique_ptr<SDL_Texture, SDLUtility>;
