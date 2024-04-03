#pragma once

struct HealthComponent {
	int healthPercent;
	//make text optional
	bool allowText = false;

	HealthComponent(int healthPercent = 0, bool allowText = false) {
		this->healthPercent = healthPercent;
		this->allowText = allowText;
	}
};