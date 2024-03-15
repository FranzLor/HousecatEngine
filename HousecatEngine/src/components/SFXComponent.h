#pragma once

#include <SDL_mixer.h>

#include <map>
#include <string>

struct SFXComponent {
	std::string soundID;
	int volume;
	int loop;
	//seconds
	Uint32 delay;
	Uint32 lastPlayed;
	int channel;

	SFXComponent(std::string soundID = "", int volume = 50, int loop = 0, Uint32 delay = 1, int channel = 0) {
		this->soundID = soundID;
		this->volume = volume;
		this->loop = loop;
		this->delay = delay;
		this->lastPlayed = 0;
		this->channel = channel;
	}
};