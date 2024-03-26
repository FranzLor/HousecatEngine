#pragma once

#include <stack>
#include <memory>

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
