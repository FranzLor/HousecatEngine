#pragma once

#include <tuple>

#include "../ecs/ECS.h"
#include "../components/ScriptComponent.h"
#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/AnimationComponent.h"


std::tuple<double, double> GetEntityPosition(Entity entity) {
	if (!entity.HasComponent<TransformComponent>()) {
		return std::make_tuple(0.0, 0.0);
	}
	const auto& transform = entity.GetComponent<TransformComponent>();
	return std::make_tuple(transform.position.x, transform.position.y);
}

std::tuple<double, double> GetEntityVelocity(Entity entity) {
	if (!entity.HasComponent<RigidBodyComponent>()) {
		return std::make_tuple(0.0, 0.0);
	}
	const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
	return std::make_tuple(rigidbody.velocity.x, rigidbody.velocity.y);
}

void SetEntityPosition(Entity entity, double x, double y) {
	if (!entity.HasComponent<TransformComponent>()) {
		return;
	}
	auto& transform = entity.GetComponent<TransformComponent>();
	transform.position.x = x;
	transform.position.y = y;
}

void SetEntityVelocity(Entity entity, double x, double y) {
	if (!entity.HasComponent<RigidBodyComponent>()) {
		return;
	}
	auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
	rigidbody.velocity.x = static_cast<float>(x);
	rigidbody.velocity.y = static_cast<float>(y);
}

void SetEntityRotation(Entity entity, double rotation) {
	if (!entity.HasComponent<TransformComponent>()) {
		return;
	}
	auto& transform = entity.GetComponent<TransformComponent>();
	transform.rotation = rotation;
}

void SetSpriteFlip(Entity entity, int flipState) {
	if (!entity.HasComponent<SpriteComponent>()) {
		return;
	}
	auto& sprite = entity.GetComponent<SpriteComponent>();
	
	switch (flipState) {
	case 1:
		sprite.flip = SDL_FLIP_HORIZONTAL;
		break;
	case 2:
		sprite.flip = SDL_FLIP_VERTICAL;
		break;
	default:
		sprite.flip = SDL_FLIP_NONE;
		break;
	}
}

void SetEntityAnimationFrame(Entity entity, int frame) {
	if (!entity.HasComponent<AnimationComponent>()) {
		return;
	}
	auto& animation = entity.GetComponent<AnimationComponent>();
	animation.currentFrame = frame;
}

class ScriptSystem : public System {
public:
	ScriptSystem() {
		RequireComponent<ScriptComponent>();
	}

	//bind lua functions to C++
	void LuaBinding(sol::state& lua) {
		lua.new_usertype<Entity>(
			"entity",
			"get_id", &Entity::GetID,
			"destroy", &Entity::Kill,
			"has_tag", &Entity::HasTag,
			"has_group", &Entity::HasGroup
		);

		//bind functions with our C++ methods
		lua.set_function("get_position", GetEntityPosition);
		lua.set_function("get_velocity", GetEntityVelocity);

		lua.set_function("set_position", SetEntityPosition);
		lua.set_function("set_velocity", SetEntityVelocity);
		lua.set_function("set_rotation", SetEntityRotation);
		lua.set_function("set_sprite_flip", SetSpriteFlip);
		lua.set_function("set_animation_frame", SetEntityAnimationFrame);
	}

	void Update(double deltaTime, int ellapsedTime) {
		for (auto entity : GetSystemEntities()) {
			const auto& scriptComponent = entity.GetComponent<ScriptComponent>();

			//casted for error handling
			sol::protected_function script = scriptComponent.function;
			sol::protected_function_result result = script(entity, deltaTime, ellapsedTime);

			if (!result.valid()) {
				sol::error error = result;
				Logger::Error("Error Running Script: " + std::string(error.what()));
			}
		}
	}

};