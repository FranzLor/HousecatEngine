#pragma once

#include "../utilities/editmanager/EditManager.h"
#include "../ui/EditorCanvas.h"


class EditCanvasSize : public IEdit {
private:
	int canvasPreviousWidth;
	int canvasPreviousHeight;

	std::shared_ptr<class EditorCanvas> canvas;

public:
	EditCanvasSize(std::shared_ptr<EditorCanvas>& canvas, const int& canvasPreviousWidth, const int& canvasPreviousHeight);
	~EditCanvasSize() = default;

	virtual void Execute() override;
	virtual void Undo() override;
	virtual void Redo() override;

	EditCanvasSize(const EditCanvasSize&) = delete;
	EditCanvasSize& operator=(const EditCanvasSize&) = delete;
};

