#pragma once

#include "editmanager/EditManager.h"

#include "../../components/TransformComponent.h"
#include "../../components/SpriteComponent.h"

class RemoveTile : public IEdit {
private:
	int tileID;

	TransformComponent transformComponent;
	SpriteComponent spriteComponent;

	std::shared_ptr<class Mouse> mouse;

public:
	RemoveTile(std::shared_ptr<class Mouse> mouse);

	virtual void Execute() override;
	virtual void Undo() override;
	virtual void Redo() override;
};