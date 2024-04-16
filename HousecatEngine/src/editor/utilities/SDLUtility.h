#pragma once

#include <SDL.h>

#include <glm/glm.hpp>

#include <memory>


//-----------------------------------------------------//
//                    SDLUtility                       //
// Custom deleter for smart pointer management of SDL  //
// resources like windows, renderers, and textures.    //
//-----------------------------------------------------//

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



/**
 * @file SDLUtility.h
 * @brief Facilitates automatic resource management for SDL entities using smart pointers.
 *
 * SDLUtility provides custom deleter functions for SDL resources such as SDL_Window,
 * SDL_Renderer, and SDL_Texture. These deleters are used in conjunction with
 * std::unique_ptr to ensure that resources are automatically and properly cleaned up
 * when they go out of scope, preventing resource leaks.
 *
 * Usage:
 * - Use SDLUtility as a custom deleter with std::unique_ptr to manage SDL resources.
 *
 * Example:
 * - EditorWindow editorWindow(SDL_CreateWindow("Title", x, y, w, h, flags), SDLUtility());
 * - EditorRenderer editorRenderer(SDL_CreateRenderer(window, -1, flags), SDLUtility());
 * - EditorTexture editorTexture(SDL_CreateTexture(renderer, format, access, w, h), SDLUtility());
 *
 * This approach encapsulates SDL cleanup logic within resource handle classes, simplifying
 * resource management throughout the editor.
 */