#pragma once

#include <SDL.h>

#include <imgui/imgui.h>

#include <sol/sol.hpp>

#include "LevelManager.h"

#include "../ecs/ECS.h"

#include "../assetmanager/AssetManager.h"

#include "../eventmanager/EventManager.h"


//----------------------------------------------------//
//                    GAME CLASS                      //
//     Main controller for game initialization,       //
//               execution, termination, and          //
//           managing game state and systems.         //
//----------------------------------------------------//


class Game {
private:
	bool isRunning;
	bool isDebugging;
	bool isDebugRendering;
	int millisecsPreviousFrame = 0;

	Uint32 quitTime = 0;

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

	void TriggerGameQuit(Uint32 delayMs);

	void Initialize();

	void Run();
	void Setup();
	void Input();
	void Update();
	void Render();
	void Destroy();

};




/**
 *
 * @class Game
 * @brief Central class for managing game state, orchestrating game systems, and handling the game loop.
 *
 * This class encapsulates all aspects of the game's execution including initialization, running the game loop,
 * rendering, and clean-up. It manages game-related subsystems such as ECS, event handling, and asset management,
 * and controls the game flow based on user input and game logic.
 *
 * Usage:
 * - The game instance is created and controlled by the main application where the game loop is executed.
 * - It initializes all necessary SDL subsystems, sets up the game window and renderer, and loads the initial game level.
 * - The game loop handles input, updates all systems, and renders the game frame by frame.
 *
 * Example Initialization and Game Loop:
 *   int main(int argc, char* argv[]) {
 *       Game game;
 *       game.Initialize();
 *       game.Run();
 *       game.Destroy();
 *       return 0;
 *   }
 *
 * Key Components:
 * - `SDL_Window*` and `SDL_Renderer*`: For rendering operations.
 * - `ImGuiContext*`: For debug and development UI overlays.
 * - `sol::state lua`: Lua state for scripting support to manage game logic and configurations.
 * - Unique pointers to `Housecat`, `AssetManager`, `EventManager`, and `LevelManager` for managing ECS, assets, events, and levels respectively.
 *
 * Key Methods:
 * - Initialize(): Sets up the SDL environment, ImGui, and loads the initial game assets and level.
 * - Run(): Starts the main game loop processing input, updates, and rendering.
 * - Destroy(): Cleans up resources, ensuring a proper shutdown.
 *
 * Note:
 * - This class should be instantiated once and is responsible for driving the entire game application.
 * - Make sure to provide this in your main function along with the Source.
 */