#pragma once

#include <SDL.h>

#include <imgui/imgui.h>

#include <sol/sol.hpp>

#include "LevelManager.h"

#include "../ecs/ECS.h"

#include "../assetmanager/AssetManager.h"

#include "../eventmanager/EventManager.h"



class Game {
private:
	bool isRunning;
	bool isDebugging;
	bool isDebugRendering;
	int millisecsPreviousFrame = 0;

	Entity* playerEntity;

	//Main Game window
	SDL_Window* window;
	SDL_Renderer* rendererGame;

	//Game camera
	SDL_Rect camera;

	//ImGui context
	ImGuiContext* gameContext;

	//SOL for lua
	sol::state lua;

	//managers
	std::unique_ptr<Housecat> housecat;
	std::unique_ptr<AssetManager> assetManager;
	std::unique_ptr<EventManager> eventManager;
	std::unique_ptr<LevelManager> levelManager;

public:
	Game();
	~Game();

	const int FPS = 60;
	const int MILLISECS_PER_FRAME = 1000 / FPS;

	static int windowWidth;
	static int windowHeight;

	static int mapWidth;
	static int mapHeight;

	static int tileSize;
	static double tileScale;

	static int paddingLeft;
	static int paddingRight;
	static int paddingTop;
	static int paddingBottom;

	Entity* GetPlayerEntity() {
		return playerEntity;
	}

	void Initialize();

	void Run();
	void Setup();
	void Input();
	void Update();
	void Render();
	void Destroy();

	/*bool IsRunning() const { return isRunning; }
	void SetRunning(bool running) { isRunning = running; }*/

};

