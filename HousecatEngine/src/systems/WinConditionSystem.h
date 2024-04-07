#pragma once

#include "../ecs/ECS.h"

#include "../components/WinConditionComponent.h"
#include "../components/BoxColliderComponent.h"

#include "../eventmanager/EventManager.h"
#include "../events/CollisionEvent.h"
#include <iostream>

class WinConditionSystem : public System {
private:
    bool winConditionMet = false;
public:
	WinConditionSystem() {
		RequireComponent<WinConditionComponent>();
		RequireComponent<BoxColliderComponent>();
	}

	void ListenToEvents(std::unique_ptr<EventManager>& eventManager) {
		eventManager->ListenToEvent<CollisionEvent>(this, &WinConditionSystem::HandleCollision);
	}

    void HandleCollision(CollisionEvent& event) {
        if (winConditionMet) {
            return;
        }

        Entity a = event.a;
        Entity b = event.b;

        // Check if one of the entities is the player and the other is the win area
        if ((a.HasTag("player") && b.HasComponent<WinConditionComponent>()) ||
            (b.HasTag("player") && a.HasComponent<WinConditionComponent>())) {

            winConditionMet = true;

            //TODO
            //stop update
            auto& housecat = Housecat::GetInstance();
            for (auto entity : GetSystemEntities()) {
                auto& text = entity.GetComponent<TextDisplayComponent>();
                auto& win = entity.GetComponent<WinConditionComponent>();
                if (entity.HasTag("winMessage")) {
                    continue;
				}
                text.isVisible = true;
            }

        }
    }

};