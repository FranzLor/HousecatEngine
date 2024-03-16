#pragma once

#include <stack>
#include <memory>

#include "../../../logger/Logger.h"

//-----------------------------------------------------//
//                       EDIT                          //
//           base for all edits | commands             //
//-----------------------------------------------------//
struct IEdit {
	virtual ~IEdit() = default;

	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;

	//TODO?..
	//virtual void Copy() = 0;
	//virtual void Paste() = 0;
	//virtual void Cut() = 0;
	//virtual void Delete() = 0;
	//virtual void SelectAll() = 0;
	//virtual void DeselectAll() = 0;
	//virtual void InvertSelection() = 0;
};

class EditManager {
private:
	std::stack<std::shared_ptr<IEdit>> editStack;

	std::stack<std::shared_ptr<IEdit>> redoStack;

	//...
public:
	EditManager() {
		Logger::Lifecycle("EditManager Constructor Called!");
	}

	~EditManager() {
		Logger::Lifecycle("EditManager Destructor Called!");
	}

	void Execute(std::shared_ptr<IEdit> edit);

	//undo management
	void Undo();

	//redo management
	void Redo();
	void ClearRedoStack();

	void Clear();

	//TODO?..
};

