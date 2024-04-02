#pragma once

#include <glm/glm.hpp>

struct MovementComponent {
	glm::vec2 initialPosition;
	glm::vec2 targetPosition;

	float speed;
	//1 towards, -1 away
	int direction = 1;

	MovementComponent(glm::vec2 initialPosition = glm::vec2(0.0f, 0.0f), glm::vec2 targetPosition = glm::vec2(0.0f, 0.0f),
		float speed = 0.0f, int direction = 1) {

		this->initialPosition = initialPosition;
		this->targetPosition = targetPosition;
		this->speed = speed;
		this->direction = direction;
	}

};
