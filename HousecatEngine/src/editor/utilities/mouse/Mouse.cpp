#include <SDL.h>

#include "Mouse.h"

#include "../../../assetmanager/AssetManager.h"


Mouse::Mouse()
	: mousePosX(0),
	mousePosY(0),
	mouseRect(glm::vec2(16, 16)),
	mousePosTile(glm::vec2(0)),
	mousePrevPosTile(glm::vec2(mousePosX, mousePosY)),
	mousePosWindow(glm::vec2(0)),
	isLeftMouseButton(false),
	isMiddleMouseButton(false),
	isRightMouseButton(false),
	tileAdded(false),
	tileRemoved(false),
	tileRecent(-1),
	tileSize(16),
	panX(0),
	panY(0),
	zoom(0.0f),
	gridSnap(false),
	isMouseOutOfBounds(false),
	appliedTransform(),
	removedTransform(),
	appliedSprite(),
	removedSprite() {
	//Logger::Lifecycle("Mouse Constructor Called!");
}

//mouse 
void Mouse::MouseTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile) {
	//normal
	if (!gridSnap) {
		mouseTile.x = (mousePosX * zoom - camera.x - (mouseRect.x * appliedTransform.scale.x * zoom) / 2);
		mouseTile.y = (mousePosY * zoom - camera.y - (mouseRect.y * appliedTransform.scale.y * zoom) / 2);

	}
	//grid snapping
	else {
		mousePosWindow.x = mousePosTile.x * tileSize;
		mousePosWindow.y = mousePosTile.y * tileSize;

		if (mousePosX >= 0) {
			mousePosX / tileSize;
		}
		if (mousePosY >= 0) {
			mousePosY / tileSize;
		}
		mouseTile.x = std::round(mousePosTile.x * tileSize * zoom) - camera.x;
		mouseTile.y = std::round(mousePosTile.y * tileSize * zoom) - camera.y;
	}

	if (!MouseOutOfBounds()) {
		SDL_Rect srcRect = {
		appliedSprite.srcRect.x,
		appliedSprite.srcRect.y,
		mouseRect.x,
		mouseRect.y
		};

		SDL_Rect destRect = {
			mouseTile.x,
			mouseTile.y,
			std::round(mouseTile.w * mouseRect.x * appliedTransform.scale.x * zoom),
			std::round(mouseTile.h * mouseRect.y * appliedTransform.scale.y * zoom)
		};

		//draw tile from set
		SDL_RenderCopyEx(
			renderer.get(),
			assetManager->ReturnEditorTexture(appliedSprite.assetID).get(),
			&srcRect,
			&destRect,
			appliedTransform.rotation,
			NULL,
			appliedSprite.flip
		);
	}

	//TODO
	//multiple tiles selected
}

void Mouse::CreateTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event) {
	
	MouseTile(renderer, assetManager, camera, mouseTile);

	//only draws if mouse is in bounds
	if (MouseOutOfBounds()) {
		return;
	}

	//set transform account camera
	appliedTransform.position = glm::vec2(mouseTile.x + camera.x, mouseTile.y + camera.y);

	//reset mouse press
	if (!LeftMouseButton()) {
		isLeftMouseButton = false;
	}
	if (!RightMouseButton()) {
		isRightMouseButton = false;
	}

	if ((event.type == SDL_MOUSEBUTTONDOWN || LeftMouseButton()) && !isMouseOutOfBounds) {
		if ((event.button.button == SDL_BUTTON_LEFT && !isLeftMouseButton)) {
			//update grid
			int gridX = static_cast<int>(mousePosWindow.x) / tileSize;
			int gridY = static_cast<int>(mousePosWindow.y) / tileSize;

			if (gridSnap) {
				appliedTransform.position.x = gridX * tileSize;
				appliedTransform.position.y = gridY * tileSize;
			}
			else {
				appliedTransform.position.x = static_cast<int>(mousePosWindow.x - (mouseRect.x * appliedTransform.scale.x / 2));
				appliedTransform.position.y = static_cast<int>(mousePosWindow.y - (mouseRect.y * appliedTransform.scale.y / 2));
			}

			Entity newTile = Housecat::GetInstance().CreateEntity();
			newTile.Group("tiles");
			newTile.AddComponent<TransformComponent>(
				glm::vec2(appliedTransform.position.x, appliedTransform.position.y),
				glm::vec2(appliedTransform.scale.x, appliedTransform.scale.y),
				appliedTransform.rotation
			);
			newTile.AddComponent<SpriteComponent>(
				appliedSprite.assetID,
				appliedSprite.width,
				appliedSprite.height,
				appliedSprite.zIndex,
				appliedSprite.isFixed,
				appliedSprite.srcRect.x,
				appliedSprite.srcRect.y
			);

			//get recent tile
			tileRecent = newTile.GetID();
			tileAdded = true;
			isLeftMouseButton = true;
		}

		if (event.button.button == SDL_BUTTON_RIGHT && !isRightMouseButton) {
			if (!Housecat::GetInstance().IsThereGroup("tiles")) {
				return;
			}

			//help for non precise removing on tile
			glm::vec2 subtract = glm::vec2(
				(mouseRect.x * appliedTransform.scale.x) / 2,
				(mouseRect.y * appliedTransform.scale.y) / 2
			);

			auto entities = Housecat::GetInstance().GetGroup("tiles");

			//remove tiles on hover
			for (auto& entity : entities) {
				const auto& transform = entity.GetComponent<TransformComponent>();
				const auto& sprite = entity.GetComponent<SpriteComponent>();

				if (mousePosX >= transform.position.x && mousePosX <= transform.position.x + sprite.width * transform.scale.x &&
					mousePosY >= transform.position.y && mousePosY <= transform.position.y + sprite.height * transform.scale.y &&
					appliedSprite.zIndex == sprite.zIndex) {

					removedTransform = transform;
					removedSprite = sprite;

					entity.Kill();
					isRightMouseButton = true;
					tileRemoved = true;
				}
			}
		}
	}
}

void Mouse::UpdateMousePosition(const SDL_Rect& camera) {
	//SDL mouse pos
	SDL_GetMouseState(&mousePosX, &mousePosY);

	//acount for camera
	mousePosX += camera.x;
	mousePosY += camera.y;
	mousePosX /= zoom;
	mousePosY /= zoom;
	mousePosWindow.x = mousePosX;
	mousePosWindow.y = mousePosY;

}

const bool Mouse::MouseOutOfBounds() const {
	if (mousePosWindow.x < 0 || mousePosWindow.y < 0) {
		return true;
	}
	return false;
}


void Mouse::MousePanCamera(EditorRenderer& renderer, SDL_Rect& camera, const AssetManagerPtr& assetManager, const float& dT) {
	if (MiddleMouseButton()) {
		SDL_ShowCursor(0);

		SDL_Rect srcRect = {
			0,
			0,
			24,
			24
		};

		SDL_Rect dstRect = {
			mousePosX * zoom - camera.x,
			mousePosY * zoom - camera.y,
			48, 
			48
		};

		//TODO
		/*SDL_RenderCopyEx(
			renderer.get(),
			assetManager->ReturnEditorTexture("mousehand").get(),
			&srcRect,
			&dstRect,
			NULL,
			NULL,
			SDL_FLIP_NONE
		);*/

		//current panning mouse to last values
		if (panX != mousePosWindow.x) {
			camera.x -= (mousePosWindow.x - panX) * zoom * dT * 5;
		}
		if (panY != mousePosWindow.y) {
			camera.y -= (mousePosWindow.y - panY) * zoom * dT * 5;
		}
	}
	else {
		SDL_ShowCursor(1);
		panX = mousePosWindow.x;
		panY = mousePosWindow.y;
	}
}

//components
void Mouse::ApplyTransform(const int scaleX, const int scaleY) {
	appliedTransform.scale = glm::vec2(scaleX, scaleY);
}

void Mouse::ApplySprite(const std::string& assetID, const int width, const int height, const int layer, const int srcRectX, const int srcRectY) {
	appliedSprite.assetID = assetID;
	appliedSprite.width = width;
	appliedSprite.height = height;
	appliedSprite.zIndex = layer;
	appliedSprite.isFixed = false;
	appliedSprite.srcRect = { srcRectX, srcRectY, width, height };
	appliedSprite.flip = SDL_FLIP_NONE;
}
