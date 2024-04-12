#pragma once

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"

#include "../components/BoxColliderComponent.h"
#include "../components/HealthComponent.h"
#include "../components/DamageAreaComponent.h"
#include "../components/WinConditionComponent.h"
#include "../components/SFXComponent.h"

#include "../events/CollisionEvent.h"

class DamageSystem : public System {
private:
	bool deathCondition = false;
	Game& game;

public:
	DamageSystem(Game& game) : game(game) {
		RequireComponent<BoxColliderComponent>();
	}

	void ListenToEvents(std::unique_ptr<EventManager>& eventManager) {
		eventManager->ListenToEvent<CollisionEvent>(this, &DamageSystem::HandleCollision);
	}

	void HandleCollision(CollisionEvent& event) {
		Entity a = event.a;
		Entity b = event.b;
		
		if (a.HasGroup("hazards") || a.HasGroup("enemy") && b.HasTag("player")) {
			if (CanApplyDamage(a)) {
				EntityOnDamageArea(a, b);
			}
		}
		if (b.HasGroup("hazards") || b.HasGroup("enemy") && a.HasTag("player")) {
			if (CanApplyDamage(b)) {
				EntityOnDamageArea(b, a);
			}
		}

		//REMIND
		//player attacks enemy?
		/*if (a.HasGroup("player") && b.HasGroup("enemy")) {

		}
		if (b.HasGroup("player") && a.HasGroup("enemy")) {

		}*/

	}

	bool CanApplyDamage(Entity area) {
		auto& damageArea = area.GetComponent<DamageAreaComponent>();
		double currentTime = SDL_GetTicks() / 1000.0;

		//time elapsed since the last damage
		double timeElapsed = currentTime - damageArea.lastDamageTimer;

		//enough time has passed since the last damage
		if (timeElapsed >= damageArea.damageDelay) {
			damageArea.lastDamageTimer = currentTime;
			return true;
		}
		return false;
	}

	void EntityOnDamageArea(Entity area, Entity entity) {
		if (deathCondition) {
			return;
		}

		const auto damageArea = area.GetComponent<DamageAreaComponent>();

		if (!damageArea.isFriendly) {
			//reduce health of entity
			auto& health = entity.GetComponent<HealthComponent>();
			health.healthPercent -= damageArea.hitPercentDamage;

			//flash red when hit
			if (entity.HasTag("player")) {
				TemporarilyChangeSpriteColor(entity, SDL_Color{ 255, 0, 0, 150 });
			}

			if (health.healthPercent <= 0) { 
				deathCondition = true;
				entity.Kill();
			}
			 
			if (deathCondition) {
				DisplayDeathText(entity);
				game.TriggerGameQuit(3000);
				Logger::Log("You Lost! \n(Intentional Game Design)");
			}
		}
	}

	void DisplayDeathText(Entity entity) {
		for (auto entity : GetSystemEntities()) {
			if (entity.HasComponent<TextDisplayComponent>()) {
				auto& text = entity.GetComponent<TextDisplayComponent>();
				auto& sfx = entity.GetComponent<SFXComponent>();

				text.position = glm::vec2((Game::windowWidth / 2) - 50, Game::windowHeight / 2);
				text.isVisible = true;
				sfx.isPlaying = true;

				break;
			}
		}
	}

	void TemporarilyChangeSpriteColor(Entity entity, SDL_Color color) {
		if (entity.HasComponent<SpriteComponent>()) { 
			auto& sprite = entity.GetComponent<SpriteComponent>();

			//check if sprite is already red
			if (SDL_GetTicks() < sprite.colorChangeEndTime) {
				//extend duration
				sprite.colorChangeEndTime = SDL_GetTicks() + 1000;
			}
			else {
				//save the current color as the og color
				sprite.originalColor = sprite.color;
				sprite.color = color;
				sprite.colorChangeEndTime = SDL_GetTicks() + 1000;
			}
		}
	}

	void Update() const {
		Uint32 currentTime = SDL_GetTicks();

		for (auto& entity : GetSystemEntities()) {
			if (entity.HasComponent<SpriteComponent>()) {
				auto& sprite = entity.GetComponent<SpriteComponent>();
				if (currentTime >= sprite.colorChangeEndTime && sprite.colorChangeEndTime != 0) {
					//revert and reset
					sprite.color = sprite.originalColor;
					sprite.colorChangeEndTime = 0;
				}
			}
		}
	}
};