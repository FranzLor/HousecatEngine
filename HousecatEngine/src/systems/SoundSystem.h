#pragma once

#include <SDL.h>

#include <SDL_mixer.h>

#include "../ecs/ECS.h"

#include "../assetmanager/AssetManager.h"

#include "../events/SFXEvent.h"

#include "../components/SFXComponent.h"
#include "../events/KeyPressedEvent.h"


class SoundSystem : public System {
private:
	std::unique_ptr<EventManager>& eventManager;
	std::unique_ptr<AssetManager>& assetManager;

public:
	SoundSystem(std::unique_ptr<EventManager>& eventManager, std::unique_ptr<AssetManager>& assetManager)
		: eventManager(eventManager), assetManager(assetManager) {

        RequireComponent<SFXComponent>();

        ListenToEvents(eventManager);
    }

	void ListenToEvents(const std::unique_ptr<EventManager>& eventManager) {
		eventManager->ListenToEvent<KeyPressedEvent>(this, &SoundSystem::KeyPressed);
	}

	void KeyPressed(KeyPressedEvent& event) {
		if (event.keyPressedSymbol == SDLK_SPACE) {
			PlaySoundForEvent(event);
		}
	}

	void PlaySoundForEvent(const KeyPressedEvent& event) {
		for (auto& entity : GetSystemEntities()) {
			if (entity.HasTag("player")) {
				auto& SFX = entity.GetComponent<SFXComponent>();
				PlaySFX(entity, SFX.soundID);
			}
		}
	}

	void PlaySFX(Entity& entity, const std::string& soundID) {
		if (!entity.HasComponent<SFXComponent>()) {
			return;
		}

		auto& SFX = entity.GetComponent<SFXComponent>();
		assetManager->PlaySound(soundID, SFX.volume, SFX.loop ? -1: 0);

		
	}

	void StopSFX(StopSFXEvent& event) {
		Mix_HaltChannel(event.channel);
	}

	void AdjustVolume(AdjustVolumeEvent& event) {
		Mix_Volume(event.channel, event.volume);
	}



	void Update() {

	}


};