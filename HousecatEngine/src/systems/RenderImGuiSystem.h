#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include <glm/gtc/type_ptr.hpp>

#include "../ecs/ECS.h"

#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/DamageAreaComponent.h"
#include "../Components/MovementStateComponent.h"
#include "../Components/AnimationComponent.h"



class RenderImGuiSystem : public System {
public:
	RenderImGuiSystem() = default;



	void Update(const std::unique_ptr<Housecat>& housecat, const SDL_Rect& camera) {

		if (ImGui::Begin("Spawn Enemies")) {
			//static variables for enemy
			//transform
			static int posX = 0;
			static int posY = 0;
			static int scaleX = 1;
			static int scaleY = 1;
			static float rotation = 0.0;
			//rigidbody
			static int velX = 0;
			static int velY = 0;
			//sprite
			const char* sprites[] = { "ghost", "other texture" };
			static int selectedSpriteIndex = 0;
			//box collider
			static int width = 32;
			static int height = 32;
			static glm::vec2 offset = { 0, 0 };
			//health
			static int health = 100;
			//damage area
			static bool isFriendly = false;
			static int hitPercentDamage = 0;
			static double damageDelay = 0.0;
			static double minDamageDelay = 0.0;
			static double maxDamageDelay = 100.0;
			//movement state
			static bool isMoving = true;
			//animation
			static int numFrames = 1;
			static int frameSpeed = 1;
			static bool isLooped = true;


			//section input eenmey sprite texture id
			if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Combo("Texture ID", &selectedSpriteIndex, sprites, IM_ARRAYSIZE(sprites));
			}
			ImGui::Spacing();

			//section input enemy transform values
			if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::InputInt("Position X", &posX);
				ImGui::InputInt("Position Y", &posY);
				ImGui::SliderInt("Scale X", &scaleX, 1, 10);
				ImGui::SliderInt("Scale Y", &scaleY, 1, 10);
				ImGui::SliderAngle("Rotation", &rotation, 0, 360);
			}
			ImGui::Spacing();

			//section input enemy box collider
			if (ImGui::CollapsingHeader("Box Collider", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::InputInt("Width", &width);
				ImGui::InputInt("Height", &height);
				ImGui::InputFloat2("Offset", glm::value_ptr(offset));

			}
			ImGui::Spacing();

			//section input enemy rigidbody values
			if (ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::InputInt("Velocity X", &velX);
				ImGui::InputInt("Velocity Y", &velY);
			}
			ImGui::Spacing();

			//section input enemy movement state
			if (ImGui::CollapsingHeader("Movement State", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Checkbox("Movement", &isMoving);
			}
			ImGui::Spacing();

			//section input enemy animations
			if (ImGui::CollapsingHeader("Animations", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::InputInt("Num of Frames", &numFrames);
				ImGui::InputInt("Frame Speed", &frameSpeed);
				ImGui::Checkbox("Looped", &isLooped);

			}
			ImGui::Spacing();

			//section damage area
			if (ImGui::CollapsingHeader("Damage Area", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGui::Checkbox("Friendly", &isFriendly);
				ImGui::SliderInt("Damage Percent", &hitPercentDamage, 0, 100);

				ImGui::InputScalar("Damage Delay (Seconds)", ImGuiDataType_Double, &damageDelay);
				ImGui::SliderScalar("##DamageDelaySlider", ImGuiDataType_Double, &damageDelay, &minDamageDelay, &maxDamageDelay);

			}
			ImGui::Spacing();

			//section to input enemy health value
			if (ImGui::CollapsingHeader("Health", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::SliderInt("Health", &health, 0, 100);
			}
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			//enemy creation but using values
			if (ImGui::Button("Spawn Ghost")) {
				Entity enemy = housecat->CreateEntity();
				enemy.Group("enemy");
				//add components
				enemy.AddComponent<TransformComponent>(glm::vec2(posX, posY), glm::vec2(scaleX, scaleY), glm::degrees(rotation));
				enemy.AddComponent<RigidBodyComponent>(glm::vec2(velX, velY));
				enemy.AddComponent<SpriteComponent>(sprites[selectedSpriteIndex], 32, 32, 2);
				enemy.AddComponent<BoxColliderComponent>(width, height, glm::vec2(0, 0));
				enemy.AddComponent<DamageAreaComponent>(isFriendly, hitPercentDamage, damageDelay);
				enemy.AddComponent<HealthComponent>(health);
				enemy.AddComponent<MovementStateComponent>(isMoving);
				enemy.AddComponent<AnimationComponent>(numFrames, frameSpeed, isLooped);

				//reset input values after creation
				posX = posY = rotation = 0;
				scaleX = scaleY = 1;

				width = 32;
				height = 32;
				offset = { 0, 0 };

				health = 100;

				isFriendly = false;
				hitPercentDamage = 0;
				damageDelay = 0.0;

				isMoving = true;

				numFrames = 1;
				frameSpeed = 1;
				isLooped = true;
			}
		}
		ImGui::End();

		//overlay dispalys map posiiton using mouse
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;
		ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiCond_Always, ImVec2(0, 0));
		ImGui::SetNextWindowBgAlpha(0.75f);
		if (ImGui::Begin("Map Coordinates", NULL, windowFlags)) {
			ImGui::Text(
				"Coordinates (X=%.1f, Y=%.1f)",
				ImGui::GetIO().MousePos.x + camera.x,
				ImGui::GetIO().MousePos.y + camera.y
			);
		}
		ImGui::End();


	}
};