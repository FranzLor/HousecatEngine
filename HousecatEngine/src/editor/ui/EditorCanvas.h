#pragma once


//-----------------------------------------------------//
//                  EditorCanvas                       //
//  Manages the dimensions of the editor's workspace   //
//  in the Housecat game engine. This class allows     //
//  dynamic resizing of the canvas to accommodate      //
//  various project needs.                             //
//-----------------------------------------------------//


class EditorCanvas {
private:
	int canvasWidth;
	int canvasHeight;

public:
	EditorCanvas(int canvasWidth = 0, int canvasHeight = 0) {
		this->canvasWidth = canvasWidth;
		this->canvasHeight = canvasHeight;
	}

	~EditorCanvas() = default;

	//helper functions
	inline const int& GetCanvasWidth() const {
		return canvasWidth;
	}

	inline const int& GetCanvasHeight() const {
		return canvasHeight;
	}

	inline void SetCanvasWidth(int width) {
		canvasWidth = width;
	}

	inline void SetCanvasHeight(int height) {
		canvasHeight = height;
	}
};



/**
 * @file EditorCanvas.h
 * @brief Manages the canvas in the Housecat game editor.
 *
 * The EditorCanvas class provides methods to get and set the dimensions of the
 * canvas used in the editor. This canvas acts as the workspace where game levels
 * or scenes are designed. It supports dynamic resizing which is integrated into
 * the editor's UI, allowing changes to be made interactively by the user.
 *
 * Key Features:
 * - Get and set canvas width and height.
 * - Integral part of the editor's layout management.
 */