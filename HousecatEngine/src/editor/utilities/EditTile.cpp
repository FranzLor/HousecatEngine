#include "EditTile.h"

#include "../utilities/mouse/Mouse.h"

EditAddTile::EditAddTile(std::shared_ptr<Mouse>& mouse)
	: tileID(-1),
	initialStateStored(false),
	mouse(mouse),
	transformComponent(),
	spriteComponent() {

}

void EditAddTile::Execute() {
	tileID = mouse->GetAddedTile();
	auto entities = Housecat::GetInstance().GetGroup("tiles");

	for (auto& entity : entities) {
		if (entity.GetID() == tileID) {
			transformComponent = entity.GetComponent<TransformComponent>();
			spriteComponent = entity.GetComponent<SpriteComponent>();
			//break out early
			initialStateStored = true;
			break;
		}
	}
}

void EditAddTile::Undo() {
	//make sure to store before undo
	if (!initialStateStored) {
		return;
	}

	//REMIND
	auto entities = Housecat::GetInstance().GetGroup("tiles");
	//get tileID, then checks every entityID against it, looking for a match
	auto it = std::find_if(entities.begin(), entities.end(), [this](const auto& entity) {
		return entity.GetID() == this->tileID;
		});

	if (it != entities.end()) {
		it->Kill();
	}
}

void EditAddTile::Redo() {
	//make sure to store before redo
	if (!initialStateStored) {
		return;
	}

	Entity recreateEntity = Housecat::GetInstance().CreateEntity();

	recreateEntity.Group("tiles");
	recreateEntity.AddComponent<TransformComponent>(transformComponent);
	recreateEntity.AddComponent<SpriteComponent>(spriteComponent);

	tileID = recreateEntity.GetID();
}






EditRemoveTile::EditRemoveTile(std::shared_ptr<Mouse>& mouse)
	: tileID(-1),
	mouse(mouse),
	transformComponent(),
	spriteComponent() {

}

void EditRemoveTile::Execute() {
	tileID = mouse->GetRemovedTile();
	auto entities = Housecat::GetInstance().GetGroup("tiles");

	for (auto& entity : entities) {
		if (entity.GetID() == tileID) {
			transformComponent = entity.GetComponent<TransformComponent>();
			spriteComponent = entity.GetComponent<SpriteComponent>();

			entity.Kill();
			break;
		}
	}
}

void EditRemoveTile::Undo() {
	//guard clause for recreating removed entity
	if (tileID == -1) {
		return;
	}

	Entity recreateEntity = Housecat::GetInstance().CreateEntity();
	recreateEntity.Group("tiles");
	recreateEntity.AddComponent<TransformComponent>(transformComponent);
	recreateEntity.AddComponent<SpriteComponent>(spriteComponent);
	tileID = recreateEntity.GetID();
}

void EditRemoveTile::Redo() {
	auto entities = Housecat::GetInstance().GetGroup("tiles");

	auto it = std::find_if(entities.begin(), entities.end(), [this](const auto& entity) {
		return entity.GetID() == this->tileID;
		});

	if (it != entities.end()) {
		it->Kill();
	}
}