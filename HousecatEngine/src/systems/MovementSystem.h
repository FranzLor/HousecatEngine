#pragma once

#include "../ecs/ECS.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"

class MovementSystem: public System {
public:
	MovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void Update(double deltaTime) {
		for (auto entity : GetSystemEntities()) {
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

			transform.position.x += static_cast<float>(rigidbody.velocity.x * deltaTime);
			transform.position.y += static_cast<float>(rigidbody.velocity.y * deltaTime);
		
			//TODO collision
			//stop out of map bounds
			//use buffer
			//for nonplayer, kill
		}
	}

};

