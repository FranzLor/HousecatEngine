#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include <glm/glm.hpp>

#include <fstream>
#include <memory>

#include "Game.h"

#include "../logger/Logger.h"

#include "../ecs/ECS.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/AnimationComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/HealthComponent.h"
#include "../components/UserControlComponent.h"
#include "../components/MovementStateComponent.h"
#include "../components/CameraComponent.h"
#include "../components/DamageAreaComponent.h"
#include "../components/TextDisplayComponent.h"


#include "../systems/MovementSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/AnimationSystem.h"
#include "../systems/CollisionSystem.h"
#include "../systems/RenderColliderSystem.h"
#include "../systems/DamageSystem.h"
#include "../systems/KeyboardInputSystem.h"
#include "../systems/CameraMovementSystem.h"
#include "../systems/RenderTextSystem.h"
#include "../systems/RenderHealthSystem.h"
#include "../systems/RenderImGuiSystem.h"


int Game::windowWidth;
int Game::windowHeight;

//map control
int Game::mapWidth;
int Game::mapHeight;

//tile 
int Game::tileSize;
double Game::tileScale;

//padding for player contraint in map
int Game::paddingLeft = 5;
int Game::paddingRight = 0;
int Game::paddingTop = 5;
int Game::paddingBottom = 0;

Game::Game()
	: isRunning(false),
	isDebugging(false),
	isDebugRendering(false),
	playerEntity(nullptr),
	window(nullptr),
	rendererGame(nullptr),
	camera({ 0, 0, 0, 0 }),
	gameContext(nullptr),
	housecat(std::make_unique<Housecat>()),
	assetManager(std::make_unique<AssetManager>()),
	eventManager(std::make_unique<EventManager>()),
	levelManager(std::make_unique<LevelManager>()) {

	Logger::Lifecycle("Main Game Constructor Called!");
}

Game::~Game() {
	Logger::Lifecycle("Main Game Destructor Called!");
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Error("Error Initializing SDL!");
		return;
	}
	if (TTF_Init() != 0) {
		Logger::Error("Error Initializing TTF!");
		return;
	}
	if (!(Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) & (MIX_INIT_OGG | MIX_INIT_MP3))) {
		Logger::Error("Error Initializing Mixer!");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	//main window
	windowWidth = 800;
	windowHeight = 800;
	window = SDL_CreateWindow(
		"Housecat - Cat Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		0
	);

	if (!window) {
		Logger::Error("Error Creating SDL Main Window!");
		return;
	}

	rendererGame = SDL_CreateRenderer(window, -1, 0);

	if (!rendererGame) {
		Logger::Error("Error Creating Main Renderer!");
		return;
	}

	//SDL mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		Logger::Error("Error Initializing Mixer Audio!");
		return;
	}

	//Camera init
	camera.x = 0;
	camera.y = 0;
	camera.w = windowWidth;
	camera.h = windowHeight;

	//ImGui init
	IMGUI_CHECKVERSION();

	gameContext = ImGui::CreateContext();

	ImGui_ImplSDL2_InitForSDLRenderer(window, rendererGame);
	ImGui_ImplSDLRenderer2_Init(rendererGame);

	SDL_SetWindowFullscreen(window, SDL_FALSE);
	isRunning = true;
}



void Game::Input() {
	SDL_Event sdlGameEvent;
	while (SDL_PollEvent(&sdlGameEvent)) {
		//handle ImGui w/ SDL input
		ImGui_ImplSDL2_ProcessEvent(&sdlGameEvent);
		ImGuiIO& IO = ImGui::GetIO();

		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		IO.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		IO.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		IO.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

		switch (sdlGameEvent.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYUP:
				eventManager->TriggerEvent<KeyReleasedEvent>(sdlGameEvent.key.keysym.sym);
				break;
			case SDL_KEYDOWN:
				eventManager->TriggerEvent<KeyPressedEvent>(sdlGameEvent.key.keysym.sym);
				if (sdlGameEvent.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
					
				}
				if (sdlGameEvent.key.keysym.sym == SDLK_TAB) {
					isDebugging = !isDebugging;
				}
				break;
			
		} 
		//TODO: process eventmessager 
		//EX: eventMessager->Event<KeyPressed>(pass event SDL sym);
	}
}

//remove later, might be useful for multi window?

//Uint32 Game::GetWindowID() const {
//	return SDL_GetWindowID(window);
//}




void Game::Setup() {
	housecat->AddSystem<MovementSystem>();
	housecat->AddSystem<RenderSystem>();
	housecat->AddSystem<AnimationSystem>();
	housecat->AddSystem<CollisionSystem>();
	housecat->AddSystem<RenderColliderSystem>();
	housecat->AddSystem<DamageSystem>();
	housecat->AddSystem<KeyboardInputSystem>();
	housecat->AddSystem<CameraMovementSystem>();
	housecat->AddSystem<RenderTextSystem>();
	housecat->AddSystem<RenderHealthSystem>();
	housecat->AddSystem<RenderImGuiSystem>();

	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);
	levelManager->LoadLevel(housecat, rendererGame, assetManager, lua, 1);
}



void Game::Update() {
	//set and capped to 144hz
	int waitingTime = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (waitingTime > 0 && waitingTime <= MILLISECS_PER_FRAME) {
		SDL_Delay(waitingTime);
	}
	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
	millisecsPreviousFrame = SDL_GetTicks();

	//resets event handlers for frame
	eventManager->Reset();

	//event listeners
	housecat->GetSystem<DamageSystem>().ListenToEvents(eventManager);
	housecat->GetSystem<KeyboardInputSystem>().ListenToEvents(eventManager);
	housecat->GetSystem<MovementSystem>().ListenToEvents(eventManager);

	//update Manager for all entities to be created/killed
	//(FIXED)
	housecat->Update();

	//SYSTEMS - updates here
	housecat->GetSystem<MovementSystem>().Update(deltaTime);
	housecat->GetSystem<AnimationSystem>().Update();
	housecat->GetSystem<CollisionSystem>().Update(eventManager);
	//housecat->GetSystem<DamageSystem>().Update();
	housecat->GetSystem<CameraMovementSystem>().Update(camera);
}

void Game::Render() {
	SDL_SetRenderDrawColor(rendererGame, 50, 50, 50, 255);
	SDL_RenderClear(rendererGame);

	ImGui::SetCurrentContext(gameContext);

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//SYSTEMS - calls update rendering
	housecat->GetSystem<RenderSystem>().Update(rendererGame, assetManager, camera);
	//[TAB] key for debugging
	if (isDebugging) {
		auto& renderColliderSystem = housecat->GetSystem<RenderColliderSystem>();
		if (renderColliderSystem.GetRenderingState()) {
			renderColliderSystem.Update(rendererGame, camera);
			renderColliderSystem.RenderDebugGrid(rendererGame, camera, 32 * 2, 32 * 2, windowWidth, windowHeight);
		}

		housecat->GetSystem<RenderImGuiSystem>().Update(housecat, camera);


	}
	housecat->GetSystem<RenderTextSystem>().Update(rendererGame, assetManager, camera);
	housecat->GetSystem<RenderHealthSystem>().Update(rendererGame, assetManager, camera);
	ImGui::EndFrame();

	//render ImGui
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(rendererGame);
}

void Game::Run() {
	Setup();
	//TODO: improve error handling...
	while (isRunning) {
		Input();
		Update();
		Render();
	}
}

void Game::Destroy() {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(rendererGame);
	SDL_DestroyWindow(window);
	SDL_Quit();
}