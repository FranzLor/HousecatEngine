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
			for (auto& entity : GetSystemEntities()) {
				if (entity.HasTag("player") && entity.HasComponent<SFXComponent>()) {
					auto& SFX = entity.GetComponent<SFXComponent>();
					
					Uint32 currentTime = SDL_GetTicks();
					Uint32 delayInMS = static_cast<Uint32>(SFX.delay * 1000.0f);

					if (currentTime >= SFX.lastPlayed + delayInMS) {
						PlaySFX(entity, SFX.soundID);
						SFX.isPlaying = true;
					}
				}
			}
		}
	}

	void PlaySFX(Entity& entity, const std::string& soundID) {
		auto& SFX = entity.GetComponent<SFXComponent>();
		Uint32 currentTime = SDL_GetTicks();

		//convert ms to s
		Uint32 delayInMS = static_cast<Uint32>(SFX.delay * 1000.0f);
		if (SFX.isPlaying) {
			if (currentTime > SFX.lastPlayed + delayInMS) {
				SFX.lastPlayed = currentTime;
				assetManager->PlaySound(soundID, SFX.volume, SFX.loop ? -1 : 0);
				SFX.isPlaying = true;
				if (!SFX.loop) {
					SFX.isPlaying = false;
				}
			}
		}
	}

	void StopSFX(StopSFXEvent& event) {
		Mix_HaltChannel(event.channel);
	}

	void AdjustVolume(AdjustVolumeEvent& event) {
		Mix_Volume(event.channel, event.volume);
	}

	void Update() {
		Uint32 currentTime = SDL_GetTicks();

		for (auto& entity : GetSystemEntities()) {
			if (!entity.HasComponent<SFXComponent>()) {
				continue;
			}

			auto& SFX = entity.GetComponent<SFXComponent>();

			if (SFX.isPlaying) {
				Uint32 delayInMS = static_cast<Uint32>(SFX.delay * 1000.0f);
				if (currentTime >= SFX.lastPlayed + delayInMS) {
					SFX.lastPlayed = currentTime;
					assetManager->PlaySound(SFX.soundID, SFX.volume, SFX.loop ? -1 : 0);
					if (!SFX.loop) {
						SFX.isPlaying = false;
					}
				}
			}
		}
	}


};