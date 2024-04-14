#pragma once

//----------------------------------------------------//
//                     COMPONENT                      //
//        Manages health-related properties and       //
//               visualization for entities.          //
//----------------------------------------------------//



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




/**
 * 
 * @struct HealthComponent
 * @brief Manages the health status of entities and controls the visual representation of health bars.
 *
 * This component keeps track of an entity's health percentage and provides customizable
 * visual cues like health bars and optional text to indicate health status. It includes
 * settings for health bar colors based on health thresholds, dimensions, and positional offsets
 * relative to the entity's position. It is crucial for gameplay mechanics involving health
 * management and visual feedback.
 *
 * Usage:
 * - healthPercent: Current health of the entity as a percentage.
 * - allowText: Enables rendering a text label showing the health percentage alongside the health bar.
 * - lowHealth, mediumHealth, highHealth: Color codes for different health levels.
 * - healthBarWidth, healthBarHeight: Dimensions of the health bar.
 * - horizontalOffset, verticalOffset: Positional adjustments for the health bar relative to the entity's position.
 *
 * Example:
 * 	monster.AddComponent<HealthComponent>(100, false);
 * 	
 *  Entity starts at 100% health, with not text (font) displayed, and uses default health bar colors and positioning.
 *
 * Note:
 * - The HealthComponent is utilized by the RenderHealthSystem, which handles the drawing of health bars
 *   and the associated health text based on the component's properties. This system ensures that health
 *   visualization is synchronized with the entity's state and location, considering the camera's viewport.
 * 
 */