#pragma once

#include "../ecs/ECS.h"

#include "Event.h"

//----------------------------------------------------//
//                  COLLISION EVENT CLASS             //
//     Represents a collision between two entities    //
//       within the game, triggering responses.       //
//----------------------------------------------------//



class CollisionEvent: public Event {
public:
	Entity a;
	Entity b;

	CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};




/**
 *
 * @class CollisionEvent
 * @brief An event that encapsulates a collision between two entities.
 *
 * This event is called when two entities collide within the game world.
 * It carries references to the two entities involved in the collision, allowing
 * systems that handle this event to implement specific collision response logic
 * based on the entities' properties, such as their group or tags.
 *
 * Usage:
 * - This event is typically triggered by the physics system when it detects a collision.
 * - Systems that need to respond to collisions, like the DamageSystem, can listen for
 *   this event and execute appropriate actions, such as applying damage or triggering
 *   game mechanics effects.
 *
 * Example:
 * 
 * 	void ListenToEvents(std::unique_ptr<EventManager>& eventManager) {
 * 	    eventManager->ListenToEvent<CollisionEvent>(this, &DamageSystem::HandleCollision);
 * 	}
 * 
 *  Listening to CollisionEvent in a system, then
 *
 * 	void HandleCollision(CollisionEvent& event) {
 * 	    Entity a = event.a;
 * 	    Entity b = event.b;
 * 	    if (a.HasGroup("hazards") || a.HasGroup("enemy") && b.HasTag("player")) {
 * 	        if (CanApplyDamage(a)) {
 * 	            EntityOnDamageArea(a, b);
 * 	        }
 * 	    }
 * 	    if (b.HasGroup("hazards") || b.HasGroup("enemy") && a.HasTag("player")) {
 * 	        if (CanApplyDamage(b)) {
 * 	            EntityOnDamageArea(b, a);
 * 	        }
 * 	    }
 * 	}
 * 
 *  Handling CollisionEvent to apply damage to entities.
 *
 * Key Members:
 * - a: The first entity involved in the collision.
 * - b: The second entity involved in the collision.
 *
 * This event is central to the dynamic and interactive nature of the game environment,
 * enabling the system to react appropriately to the continuous interactions between entities.
 * 
 */