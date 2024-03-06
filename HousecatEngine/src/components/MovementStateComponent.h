#pragma once

struct MovementStateComponent {
	bool isMoving;

	MovementStateComponent(bool isMoving = false) {
		this->isMoving = isMoving;
	}
};