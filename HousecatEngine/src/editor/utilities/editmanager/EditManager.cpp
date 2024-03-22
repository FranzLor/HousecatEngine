#include "EditManager.h"

void EditManager::Execute(std::shared_ptr<IEdit> edit) {
	edit->Execute();
	undoStack.push(edit);
	//clear redo stack after new edit
	ClearRedoStack();
}

void EditManager::Undo() {
	if (!undoStack.empty()) {
		auto lastEdit = undoStack.top();
		lastEdit->Undo();

		//moves undone to the redo stack
		redoStack.push(lastEdit);
		undoStack.pop();
	}
}

void EditManager::Redo() {
	if (!redoStack.empty()) {
		auto nextEdit = redoStack.top();
		nextEdit->Execute();
		undoStack.push(nextEdit);
		redoStack.pop();
	}
}

void EditManager::ClearRedoStack() {
	std::stack<EditPtr>().swap(redoStack);

}

void EditManager::Clear() {
	std::stack<EditPtr>().swap(undoStack);
	std::stack<EditPtr>().swap(redoStack);
}