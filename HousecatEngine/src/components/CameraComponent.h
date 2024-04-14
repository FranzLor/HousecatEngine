#pragma once

//----------------------------------------------------//
//                     COMPONENT                      //
//     Represents a camera in the ECS architecture    //
//            for entities with this compo.           //
//----------------------------------------------------//



struct CameraComponent {
	CameraComponent() = default;
};




/**
 * 
 * @struct CameraComponent
 * @brief A marker component used to identify entities that the camera should follow or interact with.
 *
 * This component, by itself, contains no data. It is used to tag entities that
 * are involved in camera control logic.
 *
 * Usage:
 * - An entity with a CameraComponent is expected to be directly manipulated by
 *   camera-related systems, such as the CameraMovementSystem, which centers
 *   the camera on the entity and ensures the camera stays within map boundaries.
 * - It also interacts with the RenderSystem to determine visibility and culling
 *   based on the camera's position relative to the entity.
 *
 * Example:
 * 	player.AddComponent<CameraComponent>();
 * 	
 *  Now the camera will follow the player and render systems will adjust visibility.
 *
 * Note:
 * - This component should be added to any entity that needs to be tracked or
 *   influenced by the camera. It doesn't hold data but works in conjunction with
 *   TransformComponent and possibly other components for effective camera control.
 * 
 */