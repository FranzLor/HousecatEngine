#include "EditTile.h"

#include "../utilities/mouse/Mouse.h"

EditAddTile::EditAddTile(std::shared_ptr<Mouse>& mouse)
	: tileID(-1),
	isCollider(false),
	mouse(mouse),
	transformComponent(),
	spriteComponent(),
	colliderComponent() {

}

void EditAddTile::Execute() {
	tileID = mouse->GetAddedTile();
}

void EditAddTile::Undo() {
	//REMIND
	auto entities = Housecat::GetInstance().GetGroup("tiles");
	for (auto& entity : entities) {
		if (entity.GetID() == tileID) {
			transformComponent = entity.GetComponent<TransformComponent>();
			spriteComponent = entity.GetComponent<SpriteComponent>();
			
			if (entity.HasComponent<BoxColliderComponent>()) {
				isCollider = true;
				const auto& boxCollider = entity.GetComponent<BoxColliderComponent>();
				colliderComponent = boxCollider;
			}

			entity.Kill();
			break;
		}
	}
}

void EditAddTile::Redo() {
	Entity recreateEntity = Housecat::GetInstance().CreateEntity();

	recreateEntity.Group("tiles");
	recreateEntity.AddComponent<TransformComponent>(transformComponent);
	recreateEntity.AddComponent<SpriteComponent>(spriteComponent);

	if (isCollider) {
		recreateEntity.AddComponent<BoxColliderComponent>(colliderComponent);
	}

	tileID = recreateEntity.GetID();
}






EditRemoveTile::EditRemoveTile(std::shared_ptr<Mouse>& mouse)
	: tileID(-1),
	isCollider(false),
	mouse(mouse),
	transformComponent(),
	spriteComponent(),
	colliderComponent() {

}

void EditRemoveTile::Execute() {
	colliderComponent = mouse->GetRemovedCollider();

	if (colliderComponent.width == 0 && colliderComponent.height == 0 && colliderComponent.offset == glm::vec2(0)) {
		isCollider = false;
	}
	else {
		isCollider = true;
	}

	transformComponent = mouse->GetRemovedTransform();
	spriteComponent = mouse->GetRemovedSprite();
}

void EditRemoveTile::Undo() {
	Entity recreateEntity = Housecat::GetInstance().CreateEntity();
	recreateEntity.Group("tiles");
	recreateEntity.AddComponent<TransformComponent>(transformComponent);
	recreateEntity.AddComponent<SpriteComponent>(spriteComponent);

	if (isCollider) {
		recreateEntity.AddComponent<BoxColliderComponent>(colliderComponent);
	}
	tileID = recreateEntity.GetID();
}

void EditRemoveTile::Redo() {
	if (tileID == -1) {
		return;
	}

	auto entities = Housecat::GetInstance().GetGroup("tiles");

	auto it = std::find_if(entities.begin(), entities.end(), [this](const auto& entity) {
		return entity.GetID() == this->tileID;
		});

	if (it != entities.end()) {
		it->Kill();
		tileID = -1;
	}
}