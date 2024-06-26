#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../assetmanager/AssetManager.h"

#include "../components/HealthComponent.h"
#include "../components/TransformComponent.h"
#include "../components/SpriteComponent.h"

//----------------------------------------------------//
//              RENDER HEALTH SYSTEM                  //
// Displays health bars for entities based on their   //
// health component values.                           //
//----------------------------------------------------//


class RenderHealthSystem : public System {
public:
	RenderHealthSystem() {
		RequireComponent<HealthComponent>();
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, const SDL_Rect& camera) const {
		for (auto entity : GetSystemEntities()) {
			const auto health = entity.GetComponent<HealthComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			//draws healthbar 
			SDL_Color healthColor = { 255, 255, 255 };

			if (health.healthPercent >= 0 && health.healthPercent < 40) {
				healthColor = health.lowHealth;
			}
			if (health.healthPercent >= 40 && health.healthPercent < 80) {
				healthColor = health.mediumHealth;
			}
			if (health.healthPercent >= 80 && health.healthPercent <= 100) {
				healthColor = health.highHealth;
			}

			double healthBarPosX = (transform.position.x + (sprite.width * transform.scale.x) - health.horizontalOffset) - camera.x;
			double healthBarPosY = (transform.position.y + health.verticalOffset) - camera.y;

			SDL_Rect healthBarRectangle = {
				static_cast<int>(healthBarPosX),
				static_cast<int>(healthBarPosY),
				static_cast<int>(health.healthBarWidth * (health.healthPercent / 100.0)),
				static_cast<int>(health.healthBarHeight)
			};
			SDL_Rect borderRectangle = {
				healthBarRectangle.x - 1,
				healthBarRectangle.y - 1,
				healthBarRectangle.w + 2,
				healthBarRectangle.h + 2
			};
			//render color for border
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &borderRectangle);
			//render color for health
			SDL_SetRenderDrawColor(renderer, healthColor.r, healthColor.g, healthColor.b, 255);
			SDL_RenderFillRect(renderer, &healthBarRectangle);

			//render health percentage text label
			if (health.allowText) {

				std::string healthText = std::to_string(health.healthPercent);
				//REMIND 
				SDL_Surface* surface = TTF_RenderText_Solid(assetManager->GetFont("roboto"), healthText.c_str(), healthColor);
				SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);

				int labelWidth = 0;
				int labelHeight = 0;
				SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);
				SDL_Rect healthBarTextRectangle = {
					static_cast<int>(healthBarPosX),
					static_cast<int>(healthBarPosY) + 2,
					labelWidth,
					labelHeight
				};

				SDL_RenderCopy(renderer, texture, NULL, &healthBarTextRectangle);
				SDL_DestroyTexture(texture);
			}
		}
	}
};



/**
 *
 * @class RenderHealthSystem
 * @brief Manages the rendering of health bars for entities to visually represent their health status.
 *
 * This system uses HealthComponent to draw health bars on the game screen, reflecting each entity's current health.
 * The system adjusts the color of the health bar based on the health percentage, providing a visual indicator that
 * enhances player feedback and game aesthetics. It supports optional text rendering of the health percentage.
 *
 * Usage:
 * - Add this system to your game engine for entities that require a visual representation of health.
 * - It should be updated every frame within the game's render loop to reflect any changes in health.
 *
 * Example:
 * 	housecat->AddSystem<RenderHealthSystem>();
 * 
 *  Adding RenderHealthSystem to the game using Housecat
 *
 * 	housecat->GetSystem<RenderHealthSystem>().Update(rendererGame, assetManager, camera);
 * 
 *  Updating and rendering the health bars in the game's render method
 *
 * Key Methods:
 * - Update(renderer, assetManager, camera): Renders health bars according to entity health data, positioning,
 *   and camera view, ensuring the bars appear correctly on screen relative to their entities.
 *
 * The RenderHealthSystem is essential for games where health management is critical, allowing players to visually
 * monitor the health status of characters or units dynamically during gameplay.
 * 
 * Note: 
 * - Call this system after the RenderSystem to ensure health bars are drawn on top of entities.
 */