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

	TransformComponent originalTransformComponent;
	SpriteComponent originalSpriteComponent;

public:
	EditAddTile(std::shared_ptr<Mouse> mouse);
	~EditAddTile() = default;

	void Execute() override;
	void Undo() override;
	void Redo() override;

};

class EditRemoveTile : public IEdit {
private:
	int tileID;

	std::shared_ptr<class Mouse> mouse;

	TransformComponent originalTransformComponent;
	SpriteComponent originalSpriteComponent;

public:
	EditRemoveTile(std::shared_ptr<Mouse> mouse);
	~EditRemoveTile() = default;

	void Execute() override;
	void Undo() override;
	void Redo() override;

};