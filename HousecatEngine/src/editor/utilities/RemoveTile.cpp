//#include "RemoveTile.h"
//
//#include "mouse/Mouse.h"

//RemoveTile::RemoveTile(std::shared_ptr<Mouse> mouse)
//	: tileID(-1),
//	transformComponent(),
//	spriteComponent(),
//	mouse(mouse) {
//
//}
//
//void RemoveTile::Execute() {
//	transformComponent = mouse->GetRemovedTransform();
//	spriteComponent = mouse->GetRemovedSprite();
//}
//
//void RemoveTile::Undo() {
//	Entity newEntity = Housecat::GetInstance().CreateEntity();
//
//	newEntity.Group("tiles");
//	newEntity.AddComponent<TransformComponent>(transformComponent);
//	newEntity.AddComponent<SpriteComponent>(spriteComponent);
//	
//	tileID = newEntity.GetID();
//}
//
//void RemoveTile::Redo() {
//	if (tileID != -1) {
//		auto entities = Housecat::GetInstance().GetGroup("tiles");
//		for (auto& entity : entities) {
//			if (entity.GetID() == tileID) {
//				entity.Kill();
//				tileID = -1;
//			}
//		}
//	}
//}