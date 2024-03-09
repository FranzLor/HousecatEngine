#include "EditManager.h"

void EditManager::Execute(std::shared_ptr<IEdit> edit) {
	edit->Execute();
	editStack.push(edit);
	//clear redo stack after new edit
	ClearRedoStack();
}

void EditManager::Undo() {
	if (!editStack.empty()) {
		auto lastEdit = editStack.top();
		lastEdit->Undo();

		//moves undone to the redo stack
		redoStack.push(lastEdit);
		editStack.pop();
	}
}

void EditManager::Redo() {
	if (!redoStack.empty()) {
		auto nextEdit = redoStack.top();
		nextEdit->Execute();
		editStack.push(nextEdit);
		redoStack.pop();
	}
}

void EditManager::ClearRedoStack() {
	while (!redoStack.empty()) {
		redoStack.pop();
	}
}