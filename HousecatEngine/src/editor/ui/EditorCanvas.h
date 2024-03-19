#pragma once

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