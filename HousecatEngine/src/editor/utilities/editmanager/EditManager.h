#pragma once

#include <vector>

#include "IEdit.h"
#include "CompoundEdit.h"

#include "../../../logger/Logger.h"


//-----------------------------------------------------//
//                   EditManager                       //
// Manages the history of edit operations for undo and //
// redo functionality in the editor.                   //
//-----------------------------------------------------//

class EditManager {
private:
	EditStack undoStack;

	EditStack redoStack;

	//compound edits
	bool isBatching = false;
	std::shared_ptr<CompoundEdit> currentBatch;

public:
	EditManager() {
		Logger::Lifecycle("EditManager Constructor Called!");
	}

	~EditManager() {
		Logger::Lifecycle("EditManager Destructor Called!");
	}

	void ExecuteEdit(std::shared_ptr<IEdit> edit);

	//undo management
	void Undo();

	//redo management
	void Redo();

	void Clear();

	bool CanUndo() const { return !undoStack.empty(); }
	bool CanRedo() const { return !redoStack.empty(); }

	void StartBatching() {
		isBatching = true;
		currentBatch = std::make_shared<CompoundEdit>();
	}

	void EndBatching() {
		isBatching = false;
		ExecuteEdit(currentBatch);
		currentBatch = nullptr;
	}
};



/**
 * @file EditManager.h
 * @brief Manages edit operations, providing undo and redo functionalities.
 *
 * The EditManager class handles the lifecycle of edit commands through
 * two primary stacks: undoStack and redoStack. It supports the execution of new
 * edits, undoing the last operation, and redoing the last undone operation.
 * This class also supports batching multiple edits into a single compound
 * edit command, facilitating grouped undo/redo actions.
 *
 * Usage:
 * - ExecuteEdit: Execute a new edit command and add it to the undo stack.
 * - Undo: Revert the most recent command from the undo stack.
 * - Redo: Re-execute the most recent undone command from the redo stack.
 * - StartBatching: Begin grouping commands into a single batch.
 * - EndBatching: End the grouping of commands and execute the batch.
 * - Clear: Clear all pending undo and redo commands.
 */