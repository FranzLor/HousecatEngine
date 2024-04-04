#pragma once

struct HealthComponent {
	int healthPercent;
	//make text optional
	bool allowText;
	
	SDL_Color lowHealth;
	SDL_Color mediumHealth;
	SDL_Color highHealth;

	//pos
	int healthBarWidth;
	int healthBarHeight;
	int horizontalOffset;
	int verticalOffset;

	HealthComponent(
		int healthPercent = 0, bool allowText = false, SDL_Color lowHealth = { 255, 0, 0 }, 
		SDL_Color mediumHealth = { 255, 255, 0 }, SDL_Color highHealth = { 0, 255, 0 },
		int healthBarWidth = 35, int healthBarHeight = 5, int horizontalOffset = 65, int verticalOffset = 0
	) {

		this->healthPercent = healthPercent;
		this->allowText = allowText;
		this->lowHealth = lowHealth;
		this->mediumHealth = mediumHealth;
		this->highHealth = highHealth;
		this->healthBarWidth = healthBarWidth;
		this->healthBarHeight = healthBarHeight;
		this->horizontalOffset = horizontalOffset;
		this->verticalOffset = verticalOffset;

	}
};