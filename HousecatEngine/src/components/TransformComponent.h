#pragma once

#include <glm/glm.hpp>

//----------------------------------------------------//
//                     COMPONENT                      //
//    Manages spatial properties of entities such     //
//    as position, scale, and rotation in the game.   //
//----------------------------------------------------//



struct TransformComponent {
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;

	TransformComponent(glm::vec2 position = glm::vec2(0,0), glm::vec2 scale = glm::vec2(0,0), double rotation = 0.0) {
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}
};




/**
 *
 * @struct TransformComponent
 * @brief Stores and manages position, scale, and rotation for an entity in the game world.
 *
 * This component is essential for defining the spatial characteristics of entities. It is used
 * by various systems to manipulate and query the entity's position in the world, apply transformations,
 * and render entities correctly based on their spatial data. The component's flexibility facilitates
 * complex behaviors like movement, collision response, and camera following.
 *
 * Usage:
 * - position: 2D vector representing the entity's position in the world.
 * - scale: 2D vector representing the size of the entity relative to its original size.
 * - rotation: A double value representing the rotation of the entity in degrees.
 *
 * Example:
 * 	player.AddComponent<TransformComponent>(glm::vec2(100, 100), glm::vec2(1, 1), 0.0);
 * 	
 *  This places the player at position (100, 100), with no scaling or rotation.
 *
 * Note:
 * - This component is widely used in rendering, physics, and camera systems to determine how and where
 *   entities are drawn, how they interact with other entities and the game world, and how the camera tracks them.
 * 
 */