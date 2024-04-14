#pragma once

#include <iostream>

#include "../ecs/ECS.h"

#include "../components/WinConditionComponent.h"
#include "../components/BoxColliderComponent.h"

#include "../eventmanager/EventManager.h"
#include "../events/CollisionEvent.h"

class WinConditionSystem : public System {
private:
    bool winConditionMet = false; 
    Game& game;
public:
	WinConditionSystem(Game& game) : game(game) {
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


            auto& housecat = Housecat::GetInstance();

            for (auto entity : GetSystemEntities()) {
                auto& text = entity.GetComponent<TextDisplayComponent>();
                auto& sfx = entity.GetComponent<SFXComponent>();

                winConditionMet = true;

                //display text
                if (entity.HasTag("winMessage")) {
                    continue;
				}
                text.isVisible = true;
                sfx.isPlaying = true;

            }
        }

        if (winConditionMet) {
            game.TriggerGameQuit(3000);
            Logger::Log("You Won! \n(Intentional Game Design)");
		}
    }
};
