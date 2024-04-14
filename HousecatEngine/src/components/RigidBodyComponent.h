#pragma once

#include <glm/glm.hpp>


//----------------------------------------------------//
//                     COMPONENT                      //
//    Handles the physical movement dynamics of       //
//             entities in the game world.            //
//----------------------------------------------------//


struct RigidBodyComponent {
	glm::vec2 velocity;

	RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0)) {
		this->velocity = velocity;
	}
};




/**
 * 
 * @struct RigidBodyComponent
 * @brief Manages the velocity vector of an entity for simulating physical movement.
 *
 * This component stores the velocity of an entity, which is used by various systems
 * to update the entity's position based on inputs and interactions within the game environment.
 * It is important for enabling dynamic movements and physics-based behaviors, such as collisions
 * and rebounds.
 *
 * Usage:
 * - velocity: A 2D vector indicating the current velocity of the entity in the x and y directions.
 *
 * Example:
 * 	player.AddComponent<RigidBodyComponent>(glm::vec2(1.0f, 0.0f));
 * 	
 *  Entity will move with a velocity of 1.0f to the right.
 *
 * Note:
 * - The RigidBodyComponent is primarily manipulated by the KeyboardInputSystem, which adjusts the
 *   velocity based on player inputs, and the MovementSystem, which applies the velocity to change the
 *   entity's position and handles collisions by adjusting or reversing the velocity as necessary.
 * - Entities with this component can interact with static or dynamic obstacles and require accurate
 *   handling to ensure realistic movement behavior within the game.
 * 
 */