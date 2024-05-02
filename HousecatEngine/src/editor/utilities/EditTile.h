#pragma once

#include "../utilities/editmanager/IEdit.h"

#include "../utilities/mouse/Mouse.h"

#include "../../components/TransformComponent.h"
#include "../../components/SpriteComponent.h"
#include "../../components/BoxColliderComponent.h"


//-----------------------------------------------------//
//                    EditAddTile                      //
//         Command to add a tile in the editor.        //
//          Supports undo and redo operations.         //
//-----------------------------------------------------//


class EditAddTile : public IEdit {
private:
	int tileID;
	bool isCollider;

	std::shared_ptr<class Mouse> mouse;

	TransformComponent transformComponent;
	SpriteComponent spriteComponent;
	BoxColliderComponent colliderComponent;

public:
	EditAddTile(std::shared_ptr<Mouse>& mouse);

	virtual void Execute() override;
	virtual void Undo() override;
	virtual void Redo() override;

};


/**
 * @file EditTile.h
 * @brief Manages the addition of a tile with undo and redo capabilities.
 *
 * The EditAddTile class implements the IEdit interface to manage tile additions
 * within an editor environment. It captures the state necessary to add or remove
 * a tile and can revert or reapply this action as needed. This class is useful
 * for managing tile-based edits in a graphical editor where undoable actions are crucial.
 *
 * Usage:
 * - An instance of EditAddTile is created and executed when a tile is added.
 * - Undo removes the tile that was added.
 * - Redo re-adds the tile.
 *
 * Note:
 * - It captures the initial tile state at construction and uses this for undo/redo.
 */



 //-----------------------------------------------------//
 //                    EditRemoveTile                   //
 //       Command to remove a tile in the editor.       //
 //          Supports undo and redo operations.         //
 //-----------------------------------------------------//

class EditRemoveTile : public IEdit {
private:
	int tileID;
	bool isCollider;

	std::shared_ptr<class Mouse> mouse;

	TransformComponent transformComponent;
	SpriteComponent spriteComponent;
	BoxColliderComponent colliderComponent;

public:
	EditRemoveTile(std::shared_ptr<Mouse>& mouse);
	~EditRemoveTile() = default;

	virtual void Execute() override;
	virtual void Undo() override;
	virtual void Redo() override;

};



/**
 * @file EditTile.h
 * @brief Manages the removal of a tile with undo and redo capabilities.
 *
 * The EditRemoveTile class implements the IEdit interface to manage tile removals
 * within an editor. It keeps track of the state of the tile before removal, allowing
 * it to restore the removed tile on undo and remove it again on redo. This functionality
 * is essential in a tile-based graphical editor for robust edit tracking and reversal.
 *
 * Usage:
 * - An instance of EditRemoveTile is created when a tile is removed.
 * - Undo restores the removed tile.
 * - Redo removes the tile again.
 *
 * Note:
 * - The tile state before removal is recorded, ensuring that it can be accurately restored.
 */