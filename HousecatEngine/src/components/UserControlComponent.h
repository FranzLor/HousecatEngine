#pragma once

#include <glm/glm.hpp>

//----------------------------------------------------//
//                     COMPONENT                      //
//   Allows entities to be controlled by user input   //
//             through directional commands.          //
//----------------------------------------------------//



struct UserControlComponent {
	glm::vec2 upDirection;
	glm::vec2 rightDirection;
	glm::vec2 downDirection;
	glm::vec2 leftDirection;

	UserControlComponent(glm::vec2 upDirection = glm::vec2(0), glm::vec2 rightDirection = glm::vec2(0), 
		glm::vec2 downDirection = glm::vec2(0), glm::vec2 leftDirection = glm::vec2(0)) {

		this->upDirection = upDirection;
		this->rightDirection = rightDirection;
		this->downDirection = downDirection;
		this->leftDirection = leftDirection;
	}
};




/**
 *
 * @struct UserControlComponent
 * @brief Defines directional vectors for entity movement based on user input.
 *
 * This component maps keyboard inputs to movement directions, allowing entities
 * to be moved in a game world. It contains vectors that define the directions for
 * up, right, down, and left movements. Each vector can be independently set to
 * control the speed and direction of the entity when the corresponding key is pressed.
 *
 * Usage:
 * - upDirection, rightDirection, downDirection, leftDirection: Vectors representing
 *   the movement direction and speed for each input key.
 *
 * Example:
 * 	player.AddComponent<UserControlComponent>(
 * 	    glm::vec2(0, -1), //Move up
 * 	    glm::vec2(1, 0),  //Move right
 * 	    glm::vec2(0, 1),  //Move down
 * 	    glm::vec2(-1, 0)  //Move left
 * 	);
 * 	
 *  This configuration allows the player to move in four directions.
 *
 * Note:
 * - This component is utilized by the KeyboardInputSystem, which checks the state
 *   of the keyboard and adjusts the entity's position based on the defined directions.
 * - The component should be used in conjunction with a RigidBodyComponent for applying
 *   the velocity changes, and a MovementStateComponent to track whether the entity is moving.
 * 
 */