#pragma once

#include <glm/glm.hpp>
#include <string>
#include <SDL.h>

struct TextDisplayComponent {
	std::string assetID;
	glm::vec2 position;
	bool isFixed;
	std::string text;
	SDL_Color color;

	TextDisplayComponent(std::string assetID = "", glm::vec2 position = glm::vec2(0, 0), bool isFixed = true, std::string text = "", const SDL_Color& color = { 0, 0, 0 }) {
		this->assetID = assetID;
		this->position = position;
		this->isFixed = isFixed;
		this->text = text;
		this->color = color;
	}

};