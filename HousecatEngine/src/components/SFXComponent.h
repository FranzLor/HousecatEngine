#pragma once

#include <SDL_mixer.h>

#include <map>
#include <string>

struct SFXComponent {
	std::string soundID;
	int volume;
	int loop;
	bool isPlaying;

	//seconds
	Uint32 delay;
	Uint32 lastPlayed;
	int channel;

	SFXComponent(std::string soundID = "", int volume = 50, int loop = 0, bool isPlaying = false, Uint32 delay = 1, int channel = 0) {
		this->soundID = soundID;
		this->volume = volume;
		this->loop = loop;
		this->isPlaying = isPlaying;
		this->delay = delay;
		this->lastPlayed = 0;
		this->channel = channel;
	}
};