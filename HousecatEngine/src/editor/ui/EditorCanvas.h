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
	const int& GetCanvasWidth() const {
		return canvasWidth;
	}

	const int& GetCanvasHeight() const {
		return canvasHeight;
	}

	void SetCanvasWidth(int width) {
		canvasWidth = width;
	}

	void SetCanvasHeight(int height) {
		canvasWidth = height;
	}
};