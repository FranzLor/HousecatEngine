#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include <string>

//----------------------------------------------------//
//                     COMPONENT                      //
//     Manages the visual representation of an        //
//                 entity within the game.            //
//----------------------------------------------------//



struct SpriteComponent {
	std::string assetID;
	int width;
	int height;
	int zIndex;
	bool isFixed;
	SDL_Rect srcRect;
	SDL_RendererFlip flip;

	//used for color changing
	SDL_Color color;
	SDL_Color originalColor;
	Uint32 colorChangeEndTime = 0;

	SpriteComponent(std::string assetID = "", int width = 0, int height = 0, int zIndex = 0, bool isFixed =  false,
		int srcRectX = 0, int srcRectY = 0, int flip = 0, SDL_Color color = { 255, 255, 255, 255 }) {


		this->assetID = assetID;
		this->width = width;
		this->height = height;
		this->zIndex = zIndex;
		this->isFixed = isFixed;
		this->srcRect = { srcRectX, srcRectY, width, height };
		this->flip = static_cast<SDL_RendererFlip>(flip);
		this->color = color;
		this->originalColor = color;
	}
};




/**
 *
 * @struct SpriteComponent
 * @brief Stores properties necessary for rendering a sprite on the screen.
 *
 * This component contains all the important data for rendering a sprite,
 * including asset ID, dimensions, layer depth (zIndex), and
 * whether it is a fixed sprite or moves with the camera. It also includes
 * attributes for dynamically adjusting the sprite's appearance, such as
 * color modifications and flip orientation.
 *
 * Usage:
 * - assetID: Identifier for the sprite's texture in the AssetManager.
 * - width, height: Dimensions of the sprite.
 * - zIndex: The rendering order depth; lower values are rendered first.
 * - isFixed: If true, the sprite does not move with the camera (useful for UI elements).
 * - srcRect: The rectangle defining the portion of the texture to draw.
 * - flip: Defines if the sprite should be flipped horizontally or vertically.
 * - color, originalColor: Used for dynamic color changes, including highlighting or damage effects.
 * - colorChangeEndTime: Timestamp after which the sprite's color change effect should revert.
 *
 * Example:
 * 	player.AddComponent<SpriteComponent>("player_texture", 64, 64, 1, false, 0, 0, SDL_FLIP_NONE);
 * 	
 *  This sets up the player with a 64x64 sprite, not fixed to the camera, with no initial flip.
 *
 * Note:
 * - The SpriteComponent is primarily used by the RenderSystem to draw entities on the screen.
 *   It supports sorting entities by zIndex to manage the rendering order and applies visual transformations
 *   based on the entity's TransformComponent.
 * 
 */