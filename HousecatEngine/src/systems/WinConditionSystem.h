#pragma once

#include <iostream>

#include "../ecs/ECS.h"

#include "../components/WinConditionComponent.h"
#include "../components/BoxColliderComponent.h"

#include "../eventmanager/EventManager.h"
#include "../events/CollisionEvent.h"


//----------------------------------------------------//
//               WIN CONDITION SYSTEM                 //
// Manages the conditions under which a game is won.  //
//----------------------------------------------------//


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




/**
 *
 * @class WinConditionSystem
 * @brief Manages game win conditions by monitoring collisions that fulfill winning criteria.
 *
 * This system uses the ECS framework to check interactions between entities that might trigger a win scenario.
 * Entities involved in win conditions must have both a WinConditionComponent and a BoxColliderComponent.
 * The system listens for collision events that might signal a game-winning condition.
 *
 * Usage:
 * - The system must be added to the game engine setup with a reference to the main game object for triggering game state changes.
 * - It subscribes to collision events and evaluates if these collisions meet the defined win conditions.
 *
 * Example:
 * 	housecat->AddSystem<WinConditionSystem>(*this);
 * 
 *  Adding the WinConditionSystem to the game using Housecat
 *
 * 	housecat->GetSystem<WinConditionSystem>().ListenToEvents(eventManager);
 * 
 *  Setup listening for events in the game loop
 *
 * Key Methods:
 * - ListenToEvents(EventManager&): Initializes the system to respond to relevant game events.
 * - HandleCollision(CollisionEvent&): Checks if the collision meets win conditions and handles the game state accordingly.
 *
 * This system ensures that winning the game is a result of specific entity interactions, enhancing gameplay dynamics and player satisfaction.
 * 
 */
