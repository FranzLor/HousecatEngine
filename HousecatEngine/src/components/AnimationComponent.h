#pragma once

#include <SDL.h>



//----------------------------------------------------//
//                     COMPONENT                      //
//                stores animation data               //
//             for entities with this compo.          //
//----------------------------------------------------//



struct AnimationComponent {
	int numFrames;
	int currentFrame;
	int frameSpeed;
	int startTime;

	bool isLooped;

	AnimationComponent(int numFrames = 1, int frameSpeed = 1, bool isLooped = true) {
		this->numFrames = numFrames;
		this->currentFrame = 1;
		this->frameSpeed = frameSpeed;
		this->startTime = SDL_GetTicks();
		this->isLooped = isLooped;
	}
};




/**
 * 
 * @struct AnimationComponent
 * @brief Manages the animation state for an entity within the ECS framework.
 *
 * This component stores animation details like number of frames,
 * the current frame, the speed at which frames change, and the animation
 * start time. It's designed to be used with entities that require animated
 * graphics, such as the player, enemies, or other interactive objs.
 *
 * Usage:
 * - numFrames: Total num of frames in the animation sequence.
 * - currentFrame: The current frame to be displayed. Starts at 1.
 * - frameSpeed: The duration (in ms) each frame is displayed,
 *               which controls the animation speed.
 * - startTime: Timestamp when the animation was started (in ms),
 *              typically set to the current time from SDL_GetTicks().
 * - isLooped: Determines whether the animation should loop back to the
 *             beginning after reaching the last frame.
 *
 *  EX:
 *	player.AddComponent<AnimationComponent>(4, 5, true);
 *
 *  Entity will have 4 frames, with each frame displayed for 5ms, looped.
 *
 * Note:
 * This component should be updated periodically (each frame or timestep).
 * 
 */