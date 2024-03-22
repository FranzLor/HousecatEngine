//#include "AddTile.h"
//
//#include "mouse/Mouse.h"

//AddTile::AddTile(std::shared_ptr<Mouse>& mouse)
//	: tileID(-1),
//	transformComponent(),
//	spriteComponent(),
//	mouse(mouse) {
//
//}
//
//
//
//void AddTile::Execute() {
//	tileID = mouse->GetAddedTile();
//}
//
//void AddTile::Undo() {
//	auto entities = Housecat::GetInstance().GetGroup("tiles");
//
//	for (auto& entity : entities) {
//		if (entity.GetID() == tileID) {
//			const auto& transform = entity.GetComponent<TransformComponent>();
//			const auto& sprite = entity.GetComponent<SpriteComponent>();
//
//			transformComponent = transform;
//			spriteComponent = sprite;
//
//			entity.Kill();
//		}
//	}
//}
//
//void AddTile::Redo() {
//	Entity newEntity = Housecat::GetInstance().CreateEntity();
//	newEntity.HasGroup("tiles");
//	newEntity.AddComponent<TransformComponent>(transformComponent);
//	newEntity.AddComponent<SpriteComponent>(spriteComponent);
//
//	tileID = newEntity.GetID();
//}
