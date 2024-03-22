#pragma once

#include "../utilities/editmanager/EditManager.h"
#include "../utilities/mouse/Mouse.h"

#include "../../components/TransformComponent.h"
#include "../../components/SpriteComponent.h"

class EditAddTile : public IEdit {
private:
	int tileID;
	bool initialStateStored;

	std::shared_ptr<class Mouse> mouse;

	TransformComponent transformComponent;
	SpriteComponent spriteComponent;

public:
	EditAddTile(std::shared_ptr<Mouse>& mouse);
	~EditAddTile() = default;

	virtual void Execute() override;
	virtual void Undo() override;
	virtual void Redo() override;

};

class EditRemoveTile : public IEdit {
private:
	int tileID;

	std::shared_ptr<class Mouse> mouse;

	TransformComponent transformComponent;
	SpriteComponent spriteComponent;

public:
	EditRemoveTile(std::shared_ptr<Mouse>& mouse);
	~EditRemoveTile() = default;

	virtual void Execute() override;
	virtual void Undo() override;
	virtual void Redo() override;

};