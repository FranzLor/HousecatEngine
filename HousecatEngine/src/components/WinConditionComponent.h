#pragma once

//----------------------------------------------------//
//                     COMPONENT                      //
//    Marks entities that can trigger win conditions  //
//                     in the game.                   //
//----------------------------------------------------//



struct WinConditionComponent {
	WinConditionComponent() = default;
};




/**
 *
 * @struct WinConditionComponent
 * @brief A marker component used to identify entities that are associated with winning the game.
 *
 * This component does not hold any data itself but is used to mark entities that,
 * when interacted with, can trigger a win condition in the game. It is used primarily
 * within the WinConditionSystem to check collisions between such entities and the player,
 * leading to game-winning scenarios.
 *
 * Usage:
 * - Attach this component to any entity that, upon collision or interaction by the player,
 *   should result in the completion of a level or game.
 *
 * Example:
 * 	finishLine.AddComponent<WinConditionComponent>();
 * 	finishLine.AddComponent<BoxColliderComponent>();
 *
 *  When the player collides with 'finishLine', the win condition is met.
 *
 * Note:
 * - Entities with this component should also have a BoxColliderComponent to detect collisions.
 *   The WinConditionSystem listens for collision events and triggers winning logic accordingly.
 *
 */