#pragma once

#include <SDL.h>
#include <algorithm>


#include "../ecs/ECS.h"

#include "../assetmanager/AssetManager.h"

#include "../components/TransformComponent.h"
#include "../components/SpriteComponent.h"


//----------------------------------------------------//
//                  RENDER SYSTEM                     //
//    Manages the rendering of entities with sprite   //
//    components relative to the camera's viewport.   //
//----------------------------------------------------//



class RenderSystem : public System {
public:
	RenderSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, SDL_Rect& camera) const {
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

			//dont render entities if outside camera view
			bool isEntityOutsideCameraView = (
				renderableEntity.transformComponent.position.x + (renderableEntity.transformComponent.scale.x * renderableEntity.spriteComponent.width) < camera.x ||
				renderableEntity.transformComponent.position.x > camera.x + camera.w ||
				renderableEntity.transformComponent.position.y + (renderableEntity.transformComponent.scale.y * renderableEntity.spriteComponent.height) < camera.y ||
				renderableEntity.transformComponent.position.y > camera.y + camera.h
			);

			//cull sprites taht are outside the camera view, or not fixed
			if (isEntityOutsideCameraView && !renderableEntity.spriteComponent.isFixed) {
				continue;
			}

			renderableEntities.emplace_back(renderableEntity);
		}

		//sort by z index
		std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b) {
			return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
		});

		for (auto entity : renderableEntities) {
			const auto& transform = entity.transformComponent;
			const auto& sprite = entity.spriteComponent;

			SDL_Texture* texture = assetManager->GetTexture(sprite.assetID);

			//put color mod before render
			SDL_SetTextureColorMod(texture, sprite.color.r, sprite.color.g, sprite.color.b);

			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x - (sprite.isFixed ? 0 : camera.x)),
				static_cast<int>(transform.position.y - (sprite.isFixed ? 0 : camera.y)),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y)
			};

			//render the sprite
			SDL_RenderCopyEx(
				renderer,
				texture,
				&srcRect,
				&dstRect,
				transform.rotation,
				NULL,
				sprite.flip
			);

			SDL_SetTextureColorMod(texture, 255, 255, 255);
		}
	}


	void UpdateEditor(SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, SDL_Rect& camera, const float& zoom) const {
		//helper vector that needs transform and sprite
		struct RenderableEntity {
			TransformComponent transformComponent;
			SpriteComponent spriteComponent;
		};

		std::vector<RenderableEntity> renderableEntities;
		for (const auto& entity : GetSystemEntities()) {
			RenderableEntity renderableEntity;
			renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();
			renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();

			//dont render entities if outside camera view
			bool isEntityOutsideCameraView = (
				renderableEntity.transformComponent.position.x + (renderableEntity.transformComponent.scale.x * renderableEntity.spriteComponent.width) < camera.x ||
				renderableEntity.transformComponent.position.x > camera.x + camera.w ||
				renderableEntity.transformComponent.position.y + (renderableEntity.transformComponent.scale.y * renderableEntity.spriteComponent.height) < camera.y ||
				renderableEntity.transformComponent.position.y > camera.y + camera.h
			);


			renderableEntities.emplace_back(renderableEntity);
		}

		//sort by z index
		std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b) {
			return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
			});

		for (const auto& entity : renderableEntities) {
			const auto& transform = entity.transformComponent;
			const auto& sprite = entity.spriteComponent;

			//source of original sprite texture
			SDL_Rect srcRect = sprite.srcRect;
			//destination of original srpite texture
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x * zoom - (sprite.isFixed ? 0 : camera.x)),
				static_cast<int>(transform.position.y * zoom - (sprite.isFixed ? 0 : camera.y)),
				static_cast<int>(sprite.width * transform.scale.x * zoom),
				static_cast<int>(sprite.height * transform.scale.y * zoom) 
			};

			SDL_RenderCopyEx(
				renderer,
				assetManager->ReturnEditorTexture(sprite.assetID).get(),
				&srcRect,
				&dstRect,
				transform.rotation,
				NULL,
				sprite.flip
			);
		}
	}

};





/**
 *
 * @class RenderSystem
 * @brief A system for rendering entities with TransformComponent and SpriteComponent, considering their visibility relative to the camera.
 *
 * This system is responsible for drawing entities that are equipped with both Transform and Sprite components,
 * rendering only those within the bounds of the camera's view. It sorts entities by their z-index to manage
 * render order, ensuring correct layering in the scene. Entities can optionally be fixed in the camera's viewport,
 * which makes them ignore camera movements, suitable for UI elements.
 *
 * Usage:
 * - Add this system to your game to manage the rendering of all sprite-based entities.
 * - It should be updated in the main game loop to draw all active entities based on their current state and camera visibility.
 *
 * Example:
 * 	housecat->AddSystem<RenderSystem>();
 * 
 *  Adding RenderSystem to the game
 *
 * 	housecat->GetSystem<RenderSystem>().Update(rendererGame, assetManager, camera);
 * 
 *  Calling in the main rendering loop
 *
 * Key Methods:
 * - Update(renderer, assetManager, camera): Processes and renders all entities that have TransformComponent and SpriteComponent.
 *   It adjusts the rendering based on the entity's position relative to the camera and applies texture modifications as needed.
 * - UpdateEditor(renderer, assetManager, camera, zoom): Similar to Update but tailored for editor mode, it allows for zooming
 *   and other modifications ideal for a game editor environment.
 *
 * The RenderSystem ensures efficient rendering by culling off-screen entities and applying z-index based sorting,
 * crucial for maintaining performance and visual correctness in complex scenes.
 * 
 * Note:
 * - This system should be called before any other rendering operations to ensure proper layering and visibility.
 */