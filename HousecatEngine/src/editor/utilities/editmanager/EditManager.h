#pragma once

#include <stack>
#include <memory>

#include "../../../logger/Logger.h"

//-----------------------------------------------------//
//                       EDIT                          //
//           base for all edits | commands             //
//-----------------------------------------------------//
struct IEdit {
	virtual ~IEdit() {}

	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	
	virtual bool CanUndo() const {
		return true;
	}

	virtual bool CanRedo() const {
		return true;
	}

	//TODO?..
	//virtual void Copy() = 0;
	//virtual void Paste() = 0;
	//virtual void Cut() = 0;
	//virtual void Delete() = 0;
	//virtual void SelectAll() = 0;
	//virtual void DeselectAll() = 0;
	//virtual void InvertSelection() = 0;
};

typedef std::stack<std::shared_ptr<IEdit>> EditStack;



class EditManager {
private:
	EditStack undoStack;

	EditStack redoStack;

	//...
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

	//TODO?..
};

