#pragma once

#include <memory>


class EditorUIRendering {
private:
	int canvasWidth;
	int canvasHeight;
	int canvasPreviousWidth;
	int canvasPreviousHeight;

	int tileSize;

	int gridX;
	int gridY;

	std::shared_ptr<class EditorCanvas> canvas;
	std::shared_ptr<class ImGuiFunctions> imguiFunctions;

public:
	EditorUIRendering();
	~EditorUIRendering();

	void Update(SDL_Renderer& renderer);

	void RenderGrid(SDL_Renderer& renderer);

	void CreateNewCanvas();

	void UpdateCanvas();

};

