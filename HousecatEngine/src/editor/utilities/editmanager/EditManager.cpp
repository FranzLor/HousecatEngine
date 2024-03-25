#include "EditManager.h"

void EditManager::ExecuteEdit(std::shared_ptr<IEdit> edit) {
	redoStack = EditStack();
	edit->Execute();
	undoStack.push(edit);
}

void EditManager::Undo() {
	if (!undoStack.empty()) {
		auto& edit = undoStack.top();
		if (edit->CanUndo()) {
			edit->Undo();
			redoStack.push(edit);
			undoStack.pop();
		}
	}
}

void EditManager::Redo() {
	if (!redoStack.empty()) {
		auto& edit = redoStack.top();
		if (edit->CanRedo()) {
			edit->Redo();
			undoStack.push(edit);
			redoStack.pop();
		}
	}
}

void EditManager::Clear() {
	undoStack = EditStack();
	redoStack = EditStack();
}
