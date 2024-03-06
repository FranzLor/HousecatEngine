#pragma once

#include <SDL.h>

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