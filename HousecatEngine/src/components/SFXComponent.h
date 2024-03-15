#pragma once

#include <SDL_mixer.h>

#include <map>
#include <string>

struct SFXComponent {
	std::string soundID;
	int volume;
	int loop;
	int channel;

	SFXComponent(std::string soundID = "", int volume = 50, int loop = 0, int channel = 0) {
		this->soundID = soundID;
		this->volume = volume;
		this->loop = loop;
		this->channel = channel;
	}
};