#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include <string>

struct SpriteComponent {
	std::string assetID;
	int width;
	int height;
	int zIndex;
	bool isFixed;
	SDL_Rect srcRect;
	SDL_RendererFlip flip;

	SpriteComponent(std::string assetID = "", int width = 0, int height = 0, int zIndex = 0, bool isFixed =  false, int srcRectX = 0, int srcRectY = 0, int flip = 0) {
		this->assetID = assetID;
		this->width = width;
		this->height = height;
		this->zIndex = zIndex;
		this->isFixed = isFixed;
		this->srcRect = { srcRectX, srcRectY, width, height };
		this->flip = static_cast<SDL_RendererFlip>(flip);
	}
};