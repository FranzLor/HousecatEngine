#pragma once

#include <SDL.h>
#include <algorithm>


#include "../ecs/ECS.h"

#include "../assetmanager/AssetManager.h"

#include "../components/TransformComponent.h"
#include "../components/SpriteComponent.h"


class RenderSystem : public System {
public:
	RenderSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	//REMIND update for camera 
	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, SDL_Rect& camera) {
		//helper vector that needs transform and sprite
		struct RenderableEntity {
			TransformComponent transformComponent;
			SpriteComponent spriteComponent;
		};

		std::vector<RenderableEntity> renderableEntities;
		for (auto entity : GetSystemEntities()) {
			RenderableEntity renderableEntity;
			renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();
			renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();

			renderableEntities.emplace_back(renderableEntity);
		}

		//sort by z index
		std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b) {
			return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
			});

		for (auto entity : renderableEntities) {
			const auto& transform = entity.transformComponent;
			const auto& sprite = entity.spriteComponent;

			//source of original sprite texture
			SDL_Rect srcRect = sprite.srcRect;
			//destination of original srpite texture
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x - (sprite.isFixed ? 0 : camera.x)),
				static_cast<int>(transform.position.y - (sprite.isFixed ? 0 : camera.y)),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y)
			};
			
			SDL_RenderCopyEx(
				renderer,
				assetManager->GetTexture(sprite.assetID),
				&srcRect,
				&dstRect,
				transform.rotation,
				NULL,
				sprite.flip
			);
		}
	}

};