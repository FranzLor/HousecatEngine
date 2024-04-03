#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../assetmanager/AssetManager.h"

#include "../components/HealthComponent.h"
#include "../components/TransformComponent.h"
#include "../components/SpriteComponent.h"


class RenderHealthSystem : public System {
public:
	RenderHealthSystem() {
		RequireComponent<HealthComponent>();
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, const SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			const auto health = entity.GetComponent<HealthComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			//draws healthbar 
			SDL_Color healthColor = { 255, 255, 255 };
			SDL_Color RED = { 255, 0, 0 };
			SDL_Color YELLOW = { 255, 255, 0 };
			SDL_Color BLUE = { 0, 0, 255 };

			if (health.healthPercent >= 0 && health.healthPercent < 40) {
				healthColor = RED;
			}
			if (health.healthPercent >= 40 && health.healthPercent < 80) {
				healthColor = YELLOW;
			}
			if (health.healthPercent >= 80 && health.healthPercent <= 100) {
				healthColor = BLUE;
			}

			//position health bar
			int healthBarWidth = 35;
			int healthBarHeight = 5;
			int horizontalOffset = 65;
			int verticalOffset = 0;

			double healthBarPosX = (transform.position.x + (sprite.width * transform.scale.x) - horizontalOffset) - camera.x;
			double healthBarPosY = (transform.position.y + verticalOffset) - camera.y;

			SDL_Rect healthBarRectangle = {
				static_cast<int>(healthBarPosX),
				static_cast<int>(healthBarPosY),
				static_cast<int>(healthBarWidth * (health.healthPercent / 100.0)),
				static_cast<int>(healthBarHeight)
			};
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