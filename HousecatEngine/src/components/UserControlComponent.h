#pragma once

#include <glm/glm.hpp>

struct UserControlComponent {
	glm::vec2 upDirection;
	glm::vec2 rightDirection;
	glm::vec2 downDirection;
	glm::vec2 leftDirection;

	UserControlComponent(glm::vec2 upDirection = glm::vec2(0), glm::vec2 rightDirection = glm::vec2(0), 
		glm::vec2 downDirection = glm::vec2(0), glm::vec2 leftDirection = glm::vec2(0)) {

		this->upDirection = upDirection;
		this->rightDirection = rightDirection;
		this->downDirection = downDirection;
		this->leftDirection = leftDirection;
	}
};