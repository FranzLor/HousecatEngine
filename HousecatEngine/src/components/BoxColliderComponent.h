#pragma once

#include <glm/glm.hpp>



//----------------------------------------------------//
//                     COMPONENT                      //
//          Defines a box-shaped collider             //
//             for entities with this compo.          //
//----------------------------------------------------//



struct BoxColliderComponent {
	int width;
	int height;
	glm::vec2 offset;

	BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0, 0)) {
		this->width = width;
		this->height = height;
		this->offset = offset;
	}
};




/**
 * 
 * @struct BoxColliderComponent
 * @brief Encapsulates a rectangular collision boundary for an entity.
 *
 * This component is used to define a box-shaped collider area, specified
 * by its width and height, along with an optional offset from the entity's
 * origin. It is meant for handling collisions and physics interactions
 * within the game.
 *
 * Usage:
 * - width: The width of the collider box in game units.
 * - height: The height of the collider box in game units.
 * - offset: A 2D vector representing the offset of the collider's center
 *           from the entity's position. Defaults to (0,0), which centers
 *           the collider on the entity.
 *
 * Example:
 * 	player.AddComponent<BoxColliderComponent>(32, 32, glm::vec2(0, 0));
 * 	
 *  This gives an entity, with a 32 tile width and height,
 *   a 32x32 collider with an offset of (0, 0).
 *
 * Note:
 * 	It is recommended to adjust the offset carefully, especially for dynamic entities,
 * 	to ensure accurate collision detection and response.
 * 
 */