#pragma once

#include "../utilities/editmanager/EditManager.h"
#include "../ui/EditorCanvas.h"


//-----------------------------------------------------//
//                    EditCanvasSize                   //
// Command to change the canvas size in the editor.    //
// Supports undo and redo operations.                  //
//-----------------------------------------------------//


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




/**
 * @file EditCanvasSize.h
 * @brief Manages changes to the canvas size with undo and redo capabilities.
 *
 * The EditCanvasSize class implements the IEdit interface to manage canvas size changes
 * within an editor. It records the previous size of the canvas and can revert or
 * reapply size changes as needed. This class is part of the command pattern used
 * to implement undoable and redoable actions related to canvas resizing.
 *
 * Usage:
 * - An instance of EditCanvasSize is created whenever the canvas size is changed.
 * - The Execute method can be called to apply a new size.
 * - Undo reverts to the previous size.
 * - Redo reapplies the new size by invoking Undo (toggling the state).
 *
 * Example:
 * - editManager->ExecuteEdit(std::make_shared<EditCanvasSize>(canvas, canvasPreviousWidth, canvasPreviousHeight));
 *
 *  In this example, the EditCanvasSize command is executed by the EditManager to manage canvas size changes.
 *
 * Note:
 * - Copy constructor and copy assignment operator are deleted to prevent copying, ensuring unique command instances.
 */