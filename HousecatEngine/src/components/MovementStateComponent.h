#pragma once

//----------------------------------------------------//
//                     COMPONENT                      //
//          Indicates an entity's movement state      //
//             for conditional animations.            //
//----------------------------------------------------//



struct MovementStateComponent {
	bool isMoving;

	MovementStateComponent(bool isMoving = false) {
		this->isMoving = isMoving;
	}
};




/**
 * 
 * @struct MovementStateComponent
 * @brief Represents the movement state of an entity, used to conditionally trigger animations.
 *
 * This component is used to flag whether an entity is currently moving or stationary.
 * It primarily interacts with the AnimationSystem to determine if animations related to
 * movement should be played. The component is important for dynamically adjusting animations
 * based on the entity's state to enhance the realism or responsiveness of character movements.
 *
 * Usage:
 * - isMoving: A boolean flag that indicates whether the entity is moving (true) or not (false).
 *
 * Example:
 * 	player.AddComponent<MovementStateComponent>(true);
 * 	
 *  Entity will start its animation after being loaded in game.
 *
 * Note:
 * - This component must be used in conjunction with AnimationComponent and SpriteComponent for effective animation handling.
 * - The AnimationSystem will use the 'isMoving' status to update the sprite's animation frame or set it to a default frame
 *   when the entity is not moving.
 * 
 */