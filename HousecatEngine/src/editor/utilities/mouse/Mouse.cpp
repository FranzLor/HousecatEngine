#include <SDL.h>

#include "Mouse.h"

#include "../../../assetmanager/AssetManager.h"
#include "../../ui/EditorCanvas.h"



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
}

//mouse 
void Mouse::MouseTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile) {
	//normal
	if (!gridSnap) {
		mouseTile.x = static_cast<int>((mousePosX * zoom - camera.x - (mouseRect.x * appliedTransform.scale.x * zoom) / 2));
		mouseTile.y = static_cast<int>((mousePosY * zoom - camera.y - (mouseRect.y * appliedTransform.scale.y * zoom) / 2));
	}
	//grid snapping
	else {
		mousePosTile.x = static_cast<float>(mousePosX * tileSize);
		mousePosTile.y = static_cast<float>(mousePosY * tileSize);

		if (mousePosX >= 0) {
			mousePosTile.x = static_cast<float>(mousePosX / tileSize);
		}
		if (mousePosY >= 0) {
			mousePosTile.y = static_cast<float>(mousePosY / tileSize);
		}
		mouseTile.x = static_cast<int>(std::round(mousePosTile.x * tileSize * zoom) - camera.x);
		mouseTile.y = static_cast<int>(std::round(mousePosTile.y * tileSize * zoom) - camera.y);
	}

	if (!MouseOutOfBounds()) {
		SDL_Rect srcRect = {
			static_cast<int>(appliedSprite.srcRect.x),
			static_cast<int>(appliedSprite.srcRect.y),
			static_cast<int>(mouseRect.x),
			static_cast<int>(mouseRect.y)
		};

		SDL_Rect destRect = {
			mouseTile.x,
			mouseTile.y,
			static_cast<int>(std::round(mouseTile.w * mouseRect.x * appliedTransform.scale.x * zoom)),
			static_cast<int>(std::round(mouseTile.h * mouseRect.y * appliedTransform.scale.y * zoom))
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

}

void Mouse::CreateTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event) {

	MouseTile(renderer, assetManager, camera, mouseTile);

	//only draws if mouse is in bounds
	if (MouseOutOfBounds()) {
		return;
	}

	//multi tiles
	glm::vec2 pos = glm::vec2(mouseTile.x + camera.x / tileSize, mouseTile.y + camera.y / tileSize);

	//set transform account camera
	appliedTransform.position = glm::vec2(mouseTile.x + camera.x, mouseTile.y + camera.y);

	//reset mouse press
	if (!LeftMouseButton()) {
		isLeftMouseButton = false;
	}

	if ((event.type == SDL_MOUSEBUTTONDOWN || LeftMouseButton()) && !isMouseOutOfBounds) {
		if ((event.button.button == SDL_BUTTON_LEFT && !isLeftMouseButton) || MultiTile(pos)) {
			//update grid
			int gridX = static_cast<int>(mousePosWindow.x) / tileSize;
			int gridY = static_cast<int>(mousePosWindow.y) / tileSize;


			if (gridSnap) {
				appliedTransform.position.x = static_cast<float>(gridX * tileSize);
				appliedTransform.position.y = static_cast<float>(gridY * tileSize);
			}
			else {
				appliedTransform.position.x = static_cast<float>(mousePosWindow.x - (mouseRect.x * appliedTransform.scale.x / 2.0f));
				appliedTransform.position.y = static_cast<float>(mousePosWindow.y - (mouseRect.y * appliedTransform.scale.y / 2.0f));
			}

			Entity newTile = Housecat::GetInstance().CreateEntity();
			newTile.Group("tiles");
			newTile.AddComponent<TransformComponent>(
				glm::vec2(appliedTransform.position.x, appliedTransform.position.y),
				appliedTransform.scale,
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
			isLeftMouseButton = true;
			tileAdded = true;

			mousePrevPosTile.x = pos.x;
			mousePrevPosTile.y = pos.y;
		}
	}
}

void Mouse::RemoveTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event) {
	//TODO
	// RENDER ERASER ICON
	//MouseTile(renderer, assetManager, camera, mouseTile);

	////only draws if mouse is in bounds
	//if (MouseOutOfBounds()) {
	//	return;
	//}

	//multi tiles
	glm::vec2 pos = glm::vec2(mouseTile.x + camera.x / tileSize, mouseTile.y + camera.y / tileSize);

	//set transform account camera
	appliedTransform.position = glm::vec2(mouseTile.x + camera.x, mouseTile.y + camera.y);

	//reset mouse press
	if (!LeftMouseButton()) {
		isLeftMouseButton = false;
	}

	if ((event.type == SDL_MOUSEBUTTONDOWN || LeftMouseButton()) && !isMouseOutOfBounds) {
		if ((event.button.button == SDL_BUTTON_LEFT && !isLeftMouseButton) || MultiTile(pos)) {
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

					//storing for undo|redo
					removedTransform = transform;
					removedSprite = sprite;

					entity.Kill();
					isLeftMouseButton = true;
					tileRemoved = true;
					break;
				}
			}
		}
	}
}

void Mouse::FillTiles(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event, const EditorCanvas& canvas) {
	//used for rendering
	//remove when -> highlighting with texture
	MouseTile(renderer, assetManager, camera, mouseTile);

	//only draws if mouse is in bounds
	if (MouseOutOfBounds()) {
		return;
	}

	//multi tiles for apply fill
	//dont remove
	glm::vec2 pos = glm::vec2(mouseTile.x + camera.x / tileSize, mouseTile.y + camera.y / tileSize);

	//set transform account camera
	appliedTransform.position = glm::vec2(mouseTile.x + camera.x, mouseTile.y + camera.y);

	//reset mouse press
	if (!LeftMouseButton()) {
		isLeftMouseButton = false;
	}

	//REMIND
	//spamming fps drop

	//TODO 
	//UNDO/REDO
	if ((event.type == SDL_MOUSEBUTTONDOWN || LeftMouseButton()) && !isMouseOutOfBounds) {
		if ((event.button.button == SDL_BUTTON_LEFT && !isLeftMouseButton) || MultiTile(pos)) {

			int canvasWidthInTiles = canvas.GetCanvasWidth() / tileSize;
			int canvasHeightInTiles = canvas.GetCanvasHeight() / tileSize;

			//checks if all positions have tiles
			bool allTilesExist = true;
			for (int x = 0; x < canvasWidthInTiles; ++x) {
				for (int y = 0; y < canvasHeightInTiles; ++y) {

					auto check = TileExistsAtPosition(x, y);
					if (check == TileCheckResult::NoTile || check == TileCheckResult::DifferentTile) {
						glm::vec2 tilePosition = glm::vec2(x * tileSize, y * tileSize);

						Entity newTile = Housecat::GetInstance().CreateEntity();
						newTile.Group("tiles");
						newTile.AddComponent<TransformComponent>(
							tilePosition,
							appliedTransform.scale,
							appliedTransform.rotation
						);

						newTile.AddComponent<SpriteComponent>(
							appliedSprite.assetID,
							tileSize,
							tileSize,
							appliedSprite.zIndex,
							appliedSprite.isFixed,
							appliedSprite.srcRect.x,
							appliedSprite.srcRect.y
						);
						tileAdded = true;

					}
				}
			}
		}
	}
}

TileCheckResult Mouse::TileExistsAtPosition(int x, int y) {
	if (!Housecat::GetInstance().IsThereGroup("tiles")) {
		return TileCheckResult::NoTile;
	}

	auto tiles = Housecat::GetInstance().GetGroup("tiles");
	for (const auto& tile : tiles) {
		const auto& transform = tile.GetComponent<TransformComponent>();
		const auto& sprite = tile.GetComponent<SpriteComponent>();

		//calc grid pos
		int tileGridX = static_cast<int>(transform.position.x) / tileSize;
		int tileGridY = static_cast<int>(transform.position.y) / tileSize;

		//find tile at pos
		if (tileGridX == x && tileGridY == y) {
			//check sprite 
			if (sprite.assetID == appliedSprite.assetID &&
				sprite.srcRect.x == appliedSprite.srcRect.x &&
				sprite.srcRect.y == appliedSprite.srcRect.y) {

				return TileCheckResult::ExactTile;
			}
			else {
				return TileCheckResult::DifferentTile;
			}
		}
	}

	return TileCheckResult::NoTile;
}



bool Mouse::MultiTile(const glm::vec2& pos) {
	if (gridSnap) {
		if ((pos.x != mousePrevPosTile.x || pos.y != mousePrevPosTile.y) && LeftMouseButton()) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Mouse::UpdateMousePosition(const SDL_Rect& camera) {
	//SDL mouse pos
	SDL_GetMouseState(&mousePosX, &mousePosY);

	float tempMousePosX = static_cast<float>(mousePosX + camera.x) / zoom;
	float tempMousePosY = static_cast<float>(mousePosY + camera.y) / zoom;

	mousePosX = static_cast<int>(std::round(tempMousePosX));
	mousePosY = static_cast<int>(std::round(tempMousePosY));

	mousePosWindow.x = tempMousePosX;
	mousePosWindow.y = tempMousePosY;
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

		//mouse texture
		SDL_Rect srcRect = { 0, 0, 32, 32 };
		SDL_Rect dstRect = {
			mousePosX * static_cast<int>(zoom) - camera.x,
			mousePosY * static_cast<int>(zoom) - camera.y,
			32, 32
		};
		SDL_RenderCopyEx(
			renderer.get(),
			assetManager->ReturnEditorTexture("pan").get(),
			&srcRect,
			&dstRect,
			NULL,
			NULL,
			SDL_FLIP_NONE
		);

		if (panX != mousePosWindow.x || panY != mousePosWindow.y) {
			//calculate changes
			float deltaX = static_cast<float>((mousePosWindow.x - panX) * zoom * dT * 40.0f);
			float deltaY = static_cast<float>((mousePosWindow.y - panY) * zoom * dT * 40.0f);

			camera.x -= static_cast<int>(deltaX);
			camera.y -= static_cast<int>(deltaY);
		}
	}
	else {
		SDL_ShowCursor(1);
		panX = static_cast<int>(mousePosWindow.x);
		panY = static_cast<int>(mousePosWindow.y);
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
