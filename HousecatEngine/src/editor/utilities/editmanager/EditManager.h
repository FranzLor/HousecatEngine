#pragma once

#include <vector>

#include "IEdit.h"
#include "CompoundEdit.h"

#include "../../../logger/Logger.h"

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

