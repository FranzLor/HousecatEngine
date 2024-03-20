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
	tileRecent(0),
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
			mousePosX / tileSize;
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
			//TODO
			mouseTile.x - camera.x,
			mouseTile.y - camera.y,
			mouseRect.x,
			mouseRect.y
		};
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
	if (!MiddleMouseButton()) {
		isMiddleMouseButton = false;
	}
	if (!RightMouseButton()) {
		isRightMouseButton = false;
	}

	if ((event.type == SDL_MOUSEBUTTONDOWN || LeftMouseButton()) && !isMouseOutOfBounds) {
		if ((event.button.button == SDL_BUTTON_LEFT && !isLeftMouseButton)) {
			//TODO
			//create
			isLeftMouseButton = true;
		}

		if (event.button.button == SDL_BUTTON_RIGHT && !isRightMouseButton) {
			//TODO
			//remove
			isRightMouseButton = true;
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
			16,
			16
		};

		SDL_Rect dstRect = {
			camera.x -= (mousePosWindow.x - panX) * zoom * dT * 5,
			camera.y -= (mousePosWindow.y - panY) * zoom * dT * 5,
			16,
			16
		};

		SDL_RenderCopyEx(
			renderer.get(),
			assetManager->GetTexture("mousehand"),
			&srcRect,
			&dstRect,
			NULL,
			NULL,
			SDL_FLIP_NONE
		);

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
void Mouse::ApplyTransform(const int scaleX, const int scaley) {
	appliedTransform.scale = glm::vec2(scaleX, scaley);
}

void Mouse::ApplySprite(const std::string& assetID, const int width, const int height, const int layer, const int srcRectX, const int srcRectY) {
	appliedSprite.assetID = assetID;
	appliedSprite.width = width;
	appliedSprite.height = height;
	appliedSprite.zIndex = layer;
	appliedSprite.srcRect = { srcRectX, srcRectY, width, height };

}
