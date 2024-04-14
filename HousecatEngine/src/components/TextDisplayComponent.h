#pragma once

#include <glm/glm.hpp>
#include <string>
#include <SDL.h>

//----------------------------------------------------//
//                     COMPONENT                      //
//   Handles display properties for text elements     //
//              within the game environment.          //
//----------------------------------------------------//



struct TextDisplayComponent {
	std::string assetID;
	glm::vec2 position;
	bool isFixed;
	bool isVisible;
	std::string text;
	SDL_Color color;

	TextDisplayComponent(std::string assetID = "", glm::vec2 position = glm::vec2(0, 0), bool isFixed = true, bool isVisible = true, std::string text = "", const SDL_Color& color = { 0, 0, 0 }) {
		this->assetID = assetID;
		this->position = position;
		this->isFixed = isFixed;
		this->isVisible = isVisible;
		this->text = text;
		this->color = color;
	}

};




/**
 *
 * @struct TextDisplayComponent
 * @brief Manages display settings for text within the game, such as position, visibility, and style.
 *
 * This component stores information necessary for rendering text elements on the screen,
 * including the font asset ID, text content, position, and visibility. It can be used
 * for UI elements like scores, dialogues, and interactive prompts that require dynamic text rendering.
 * The text can be either fixed or scrollable with the camera, making it versatile for various UI layouts.
 *
 * Usage:
 * - assetID: Identifier for the font in the AssetManager.
 * - position: The position on the screen where the text is to be displayed.
 * - isFixed: If true, the text does not move with the camera (suitable for UI elements).
 * - isVisible: Controls the visibility of the text.
 * - text: The string content to display.
 * - color: The SDL_Color for the text, allowing for customization of text color.
 *
 * Example:
 * 	message.AddComponent<TextDisplayComponent>("font_asset", glm::vec2(100, 200), true, true, "Hello World", {255, 0, 0});
 * 	
 *  This creates a text element that displays "Hello World" at position (100, 200) with red coloring.
 *
 * Note:
 * - This component is used by the RenderTextSystem to draw text based on its properties.
 * - It can interact with systems like the DamageSystem to display messages upon events such as 'Player Death' or 'Win Condition Met'.
 * 
 */