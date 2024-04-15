#pragma once

#include <tuple>

#include "../ecs/ECS.h"
#include "../components/ScriptComponent.h"
#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/AnimationComponent.h"

//----------------------------------------------------//
//                    SCRIPT SYSTEM                   //
//  Integrates Lua scripting with entity components   //
//       to provide dynamic behaviors at runtime.     //
//----------------------------------------------------//



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
	transform.position.x = static_cast<float>(x);
	transform.position.y = static_cast<float>(y);
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

	void Update(double deltaTime, int ellapsedTime) const {
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




/**
 *
 * @class ScriptSystem
 * @brief Manages the integration of Lua scripting to control and manipulate entity behaviors dynamically.
 *
 * The ScriptSystem allows scripts written in Lua to directly interact with the components of entities,
 * enabling dynamic behavior modifications based on script logic. It binds C++ functions to Lua,
 * allowing scripts to get and set properties related to position, velocity, rotation, sprite flipping,
 * and animation frame management. This system enhances gameplay flexibility and allows non-hardcoded,
 * creative gameplay mechanics and interactions.
 *
 * Usage:
 * - Add the system to your engine to enable scripting capabilities for entities with a ScriptComponent.
 * - Bind Lua context to enable Lua scripts to access entity components and manipulate them during runtime.
 * - Regularly update the system within the game loop to execute the attached Lua scripts per entity.
 *
 * Example:
 * 	housecat->AddSystem<ScriptSystem>();
 * 
 *  Adding ScriptSystem to the engine using Housecat
 *
 * 	housecat->GetSystem<ScriptSystem>().LuaBinding(lua);
 * 
 *  Binding Lua state for function access
 *
 * 	housecat->GetSystem<ScriptSystem>().Update(deltaTime, SDL_GetTicks());
 * 
 *  Updating the ScriptSystem in the game loop
 *
 * Key Functions:
 * - LuaBinding(lua): Binds Lua functions to allow scripts to manipulate entity components like Transform, RigidBody, Sprite, etc.
 * - Update(deltaTime, elapsedTime): Processes each entity with a ScriptComponent, executing the bound Lua script and handling errors.
 *
 * This system is critical for games requiring complex interactions and behaviors that are too cumbersome to hard code entirely in C++.
 * 
 */