#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../components/TextDisplayComponent.h"


class RenderTextSystem : public System {
public:
	RenderTextSystem() {
		RequireComponent<TextDisplayComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, const SDL_Rect& camera) const {
		for (auto entity : GetSystemEntities()) {
			const auto text = entity.GetComponent<TextDisplayComponent>();

			if (!text.isVisible) {
				continue;
			}

			SDL_Surface* surface = TTF_RenderText_Blended(
				assetManager->GetFont(text.assetID),
				text.text.c_str(),
				text.color
			);

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			int textWidth = 0;
			int textHeight = 0;

			SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

			SDL_Rect targetRect = {
				static_cast<int>(text.position.x - (text.isFixed ? 0 : camera.x)),
				static_cast<int>(text.position.y - (text.isFixed ? 0 : camera.y)),
				textWidth,
				textHeight
			};

			SDL_RenderCopy(renderer, texture, nullptr, &targetRect);
		}
	}


};