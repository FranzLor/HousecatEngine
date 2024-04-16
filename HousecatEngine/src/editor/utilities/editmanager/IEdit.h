#pragma once

#include <stack>
#include <memory>

//-----------------------------------------------------//
//                       IEdit                         //
//    Interface for implementing edit commands in the  //
//    editor. Supports undo and redo operations.       //
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



/**
 * @file IEdit.h
 * @brief Defines the interface for edit commands.
 *
 * The IEdit interface provides the necessary methods to execute, undo,
 * and redo editing commands within the editor. Implementations of this interface
 * must provide their own mechanisms for executing commands and handling undo/redo
 * capabilities, enabling a flexible command pattern.
 *
 * Methods:
 * - Execute: Perform the command.
 * - Undo: Revert the command.
 * - Redo: Re-execute the command after an undo.
 * - CanUndo: Check if the undo operation is possible.
 * - CanRedo: Check if the redo operation is possible.
 */
