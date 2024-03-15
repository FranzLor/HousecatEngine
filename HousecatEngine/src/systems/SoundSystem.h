#pragma once

#include <SDL.h>

#include <SDL_mixer.h>

#include "../ecs/ECS.h"

#include "../assetmanager/AssetManager.h"

#include "../components/SFXComponent.h"


class SoundSystem : public System {
public:
	SoundSystem() {
		RequireComponent<SFXComponent>();
	}

	void PlaySFX(std::unique_ptr<AssetManager>& assetManager, Entity& entity, const std::string& soundID) {
		auto& SFX = entity.GetComponent<SFXComponent>();
		auto sounds = SFX.soundID.find(soundID);

		if (sounds == SFX.soundID.end()) {
			//sound id not found
			return;
		}

		Mix_Chunk* sound = assetManager->GetSound(soundID);

		if (sound == nullptr) {
			//sound not found
			return;
		}

		Mix_VolumeChunk(sound, SFX.volume);
		int channel = Mix_PlayChannel(SFX.channel, sound, SFX.loop ? -1 : 0);
		if (channel == -1) {
			//error playing sound
			return;
		}

	}


	void Update(double deltaTime) {
		for (auto entity : GetSystemEntities()) {
			const auto SFX = entity.GetComponent<SFXComponent>();

			//TODO
			//button event?
			//damage event
			//collision event

		}
	}


};