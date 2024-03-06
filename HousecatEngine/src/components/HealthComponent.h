#pragma once

struct HealthComponent {
	int healthPercent;

	HealthComponent(int healthPercent = 0) {
		this->healthPercent = healthPercent;
	}
};