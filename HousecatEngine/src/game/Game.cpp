#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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
int Game::mapWidth;
int Game::mapHeight;

Game::Game()
	: isRunning(false),
	isDebugging(false),
	playerEntity(nullptr),
	window(nullptr),
	rendererGame(nullptr),
	camera({ 0, 0, 0, 0 }),
	gameContext(nullptr),
	housecat(std::make_unique<Housecat>()),
	assetManager(std::make_unique<AssetManager>()),
	eventManager(std::make_unique<EventManager>()) {

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


//TODO: lua script for lua levels
//REMOVE AFTER TESTING
void Game::LoadLevel(int level) {
	//
	//SYSTEMS - what systems you want to work with
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

	//TOD: lua + sol
	//replace in script file
	//ASSETS - add textures to game
	assetManager->AddTexture(rendererGame, "player", "./assets/textures/cat_sprite_2.png");

	assetManager->AddTexture(rendererGame, "npc", "./assets/textures/cat_animate_2.png");

	assetManager->AddTexture(rendererGame, "cat_run", "./assets/textures/cat_run.png");

	assetManager->AddTexture(rendererGame, "ghost", "./assets/textures/ghost.png");

	assetManager->AddTexture(rendererGame, "chest", "./assets/textures/chest_test.png");

	assetManager->AddTexture(rendererGame, "fire", "./assets/textures/fire_sprite.png");

	assetManager->AddTexture(rendererGame, "map", "./assets/tilemaps/terrain_tile.png");

	assetManager->AddFont("roboto", "./assets/fonts/roboto.regular.ttf", 18);
	assetManager->AddFont("montserrat", "./assets/fonts/montserrat.bold.ttf", 20);

	//load tilemap test
	int tileSize = 32;
	double tileScale = 2.0;
	int mapColumns = 40;
	int mapRows = 40;

	std::fstream mapFile;

	//TODO error handling?
	mapFile.open("./assets/tilemaps/map_test.map");

	for (int y = 0; y < mapRows; y++) {
		for (int x = 0; x < mapColumns; x++) {
			char ch;
			mapFile.get(ch);
			int srcRectY = std::atoi(&ch) * tileSize;

			mapFile.get(ch);
			int srcRectX = std::atoi(&ch) * tileSize;
			mapFile.ignore();
			mapFile.ignore();

			Entity tile = housecat->CreateEntity();
			tile.Group("tilemap");
			tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
			tile.AddComponent<SpriteComponent>("map", tileSize, tileSize, 0, false, srcRectX, srcRectY);
			
		}
	}
	mapFile.close();

	mapWidth = static_cast<int>(mapColumns * tileSize * tileScale);
	mapHeight = static_cast<int>(mapRows * tileSize * tileScale);



	//TODO: lua
	//ENTITIES - create entities to game
	Entity cat1 = housecat->CreateEntity();
	Entity cat2 = housecat->CreateEntity();
	Entity cat3 = housecat->CreateEntity();
	Entity cat4 = housecat->CreateEntity();

	Entity player = housecat->CreateEntity();
	Entity ghost = housecat->CreateEntity();

	Entity chestR = housecat->CreateEntity();
	Entity chestL = housecat->CreateEntity();

	Entity fire = housecat->CreateEntity();

	Entity healthLabel = housecat->CreateEntity();

	//TODO: lua
	//COMPONENTS - add components to entities

	//housecat->AddComponent<TransformComponent>(cat1, glm::vec2(250.0, 250.0), glm::vec2(1.0, 1.0), 0.0);

	//TESTING GROUNDS
	player.Tag("player");
	player.AddComponent<UserControlComponent>(glm::vec2(0, -90), glm::vec2(90, 0), glm::vec2(0, 90), glm::vec2(-90, 0));
	player.AddComponent<TransformComponent>(glm::vec2(180, 500), glm::vec2(4.0, 4.0), 0.0);
	player.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	player.AddComponent<AnimationComponent>(4, 5, true);
	player.AddComponent<MovementStateComponent>(false);
	player.AddComponent<SpriteComponent>("player", 32, 32, 2);
	player.AddComponent<HealthComponent>(100);
	player.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(20.0, 24.0));
	player.AddComponent<CameraComponent>();

	cat1.Group("cats");
	cat1.AddComponent<TransformComponent>(glm::vec2(150, 250), glm::vec2(4.0, 4.0), 0.0);
	cat1.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	cat1.AddComponent<AnimationComponent>(4, 5, true);
	cat1.AddComponent<MovementStateComponent>(true);
	cat1.AddComponent<SpriteComponent>("npc", 32, 32, 3);
	//cat1.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(20.0, 24.0));

	cat2.Group("cats");
	cat2.AddComponent<TransformComponent>(glm::vec2(90, 295), glm::vec2(2.0, 2.0), 0.0);
	cat2.AddComponent<AnimationComponent>(4, 8, true);
	cat2.AddComponent<MovementStateComponent>(true);
	cat2.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	cat2.AddComponent<SpriteComponent>("npc", 32, 32, 2);
	//cat2.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(10.0, 16.0));

	cat3.Group("cats");
	cat3.AddComponent<TransformComponent>(glm::vec2(160, 270), glm::vec2(2.0, 2.0), 0.0);
	cat3.AddComponent<AnimationComponent>(4, 8, true);
	cat3.AddComponent<MovementStateComponent>(true);
	cat3.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	cat3.AddComponent<SpriteComponent>("npc", 32, 32, 2);
	//cat3.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(10.0, 16.0));
	
	cat4.Group("cats");
	cat4.AddComponent<TransformComponent>(glm::vec2(140, 315), glm::vec2(2.0, 2.0), 0.0);
	cat4.AddComponent<AnimationComponent>(4, 8, true);
	cat4.AddComponent<MovementStateComponent>(true);
	cat4.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	cat4.AddComponent<SpriteComponent>("npc", 32, 32, 4);
	//cat4.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(10.0, 16.0));


	ghost.Group("enemy");
	ghost.AddComponent<TransformComponent>(glm::vec2(540, 400), glm::vec2(2.0, 2.0), 0.0);
	ghost.AddComponent<AnimationComponent>(10, 10, true);
	ghost.AddComponent<MovementStateComponent>(true);
	ghost.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	ghost.AddComponent<SpriteComponent>("ghost", 32, 32, 4);
	ghost.AddComponent<BoxColliderComponent>(32, 32);
	ghost.AddComponent<DamageAreaComponent>(false, 20);

	fire.Group("hazards");
	fire.AddComponent<TransformComponent>(glm::vec2(200, 700), glm::vec2(5.0, 5.0), 0.0);
	fire.AddComponent<MovementStateComponent>(true);
	fire.AddComponent<AnimationComponent>(8, 10, true);
	fire.AddComponent<SpriteComponent>("fire", 24, 32, 4);
	fire.AddComponent<BoxColliderComponent>(15, 5, glm::vec2(25, 32 * 4.2));
	fire.AddComponent<DamageAreaComponent>(false, 20, 1.0);



	chestR.Group("barriers");
	chestR.AddComponent<TransformComponent>(glm::vec2(600, 280), glm::vec2(3.0, 3.0), 0.0);
	chestR.AddComponent<SpriteComponent>("chest", 37, 32, 5);
	chestR.AddComponent<BoxColliderComponent>(37, 32);

	chestL.Group("barriers");
	chestL.AddComponent<TransformComponent>(glm::vec2(0, 280), glm::vec2(3.0, 3.0), 0.0);
	chestL.AddComponent<SpriteComponent>("chest", 37, 32, 5);
	chestL.AddComponent<BoxColliderComponent>(37, 32);

	SDL_Color RED = { 255, 0, 0 };
	healthLabel.AddComponent<TextDisplayComponent>("montserrat", glm::vec2(5, 5), true, "Housecat", RED);

	//TESTING
	//cat1.RemoveComponent<TransformComponent>();
	//cat1.RemoveComponent<RigidBodyComponent>();
	//chest.Kill();
}


void Game::Setup() {
	LoadLevel(1);
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
		housecat->GetSystem<RenderColliderSystem>().Update(rendererGame, camera);

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