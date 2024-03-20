#include <SDL_ttf.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include "Editor.h"
#include "ui/EditorUIRendering.h"

#include "../logger/Logger.h"

#include "../systems/RenderSystem.h"
#include "../systems/RenderColliderSystem.h"
#include "../systems/AnimationSystem.h"

Editor::Editor()
	: isRunning(false),
	millisecsPreviousFrame(0),
	zoom(1),
	mouseTile(),
	camera(),
	event(),
	editorWindow(nullptr),
	editorRenderer(nullptr),
	editorImGuiContext(nullptr) {

	Logger::Lifecycle("Editor Constructor Called!");
}

Editor::~Editor() {

	Logger::Lifecycle("Editor Destructor Called!");
}

void Editor::Initialize() {
	//SDL Window Init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Error("Error Initializing SDL Editor!");
		return;
	}
	if (TTF_Init() != 0) {
		Logger::Error("Error Initializing TTF Editor!");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	editorWindow = EditorWindow(SDL_CreateWindow(
		"Housecat Editor",
		0,
		windowBar,
		windowEditorWidth,
		windowEditorHeight,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	));

	if (!editorWindow) {
		Logger::Error("Error Creating SDL Editor Window!");
		return;
	}

	//SDL Renderer Init
	editorRenderer = EditorRenderer(SDL_CreateRenderer(
		editorWindow.get(),
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	));

	if (!editorRenderer) {
		Logger::Error("Error Creating Editor Renderer!");
		return;
	}

	SDL_SetWindowFullscreen(editorWindow.get(), SDL_FALSE);
	isRunning = true;

	//mouse
	//x, y, w, h
	mouseTile = { 0, 0, 1, 1 };

	//camera
	camera = { defaultCamX, defaultCamY, windowEditorWidth, windowEditorHeight };


	//ImGui Init
	IMGUI_CHECKVERSION();
	editorImGuiContext = ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(editorWindow.get(), editorRenderer.get());
	ImGui_ImplSDLRenderer2_Init(editorRenderer.get());

	ImGuiIO& IO = ImGui::GetIO(); (void)IO;


	//TODO
	assetManager = std::make_unique<AssetManager>();
	//textures
	//assetManager->AddTexture(editorRenderer.get(), "x", "x");

	//SYSTEMS
	//call Housecat to add systems for editor
	auto& housecat = Housecat::GetInstance();
	housecat.AddSystem<RenderSystem>();
	housecat.AddSystem<EditorUIRendering>();
	housecat.AddSystem<RenderColliderSystem>();
	housecat.AddSystem<AnimationSystem>();
}



void Editor::ProcessInput() {
	while (SDL_PollEvent(&event)) {
		//handle ImGui SDL input
		ImGui_ImplSDL2_ProcessEvent(&event);
		ImGuiIO& IO = ImGui::GetIO();

		//mouse buttons
		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		IO.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		IO.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		IO.MouseDown[2] = buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE);
		IO.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			if (!IO.WantCaptureMouse) {
				CameraController(event);
			}
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;

			}
			KeyboardCameraController(event);
			break;
		}
	}
}

void Editor::Update() {
	//Framerate capped at 144
	int waitingTime = EDITOR_MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (waitingTime > 0 && waitingTime <= EDITOR_MILLISECS_PER_FRAME) {
		SDL_Delay(waitingTime);
	}
	//diff. in ticks since last frame converted to secs
	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
	//store curr. frame time
	millisecsPreviousFrame = SDL_GetTicks();

	//TODO
	Housecat::GetInstance().Update();

	//TODO
	//exit
	/*if (Housecat::GetInstance().GetSystem<ImGuiRendering>().Exit()) {
		isRunning = false;
	}*/

	//TODO
}


void Editor::Render() {
	SDL_SetRenderDrawColor(editorRenderer.get(), 155, 155, 155, 255);
	SDL_RenderClear(editorRenderer.get());

	//render editor
	Housecat::GetInstance().GetSystem<RenderSystem>().Update(editorRenderer.get(), assetManager, camera);

	Housecat::GetInstance().GetSystem<EditorUIRendering>().RenderGrid(editorRenderer, camera, zoom);

	//TODO
	//render collider
	//render animation


	Housecat::GetInstance().GetSystem<EditorUIRendering>().Update(editorRenderer, assetManager, camera, mouseTile,
		event, zoom, millisecsPreviousFrame);


	SDL_RenderPresent(editorRenderer.get());
}

void Editor::CameraController(SDL_Event& event) {
	constexpr float zoomStep = 0.4f;

	if (event.wheel.y > 0) {
		zoom = std::min(zoom + zoomStep, 2.2f);
	}
	else if (event.wheel.y < 0) {
		zoom = std::max(zoom - zoomStep, 0.4f);
	}

	camera.h *= zoom;
	camera.w *= zoom;
}

void Editor::KeyboardCameraController(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			camera.x = defaultCamX;
			camera.y = defaultCamY;
			zoom = defaultZoom;
			break;
		case SDLK_w:
			camera.y -= camSpeed;
			break;
		case SDLK_a:
			camera.x -= camSpeed;
			break;
		case SDLK_s:
			camera.y += camSpeed;
			break;
		case SDLK_d:
			camera.x += camSpeed;
			break;
		}
	}
}

void Editor::Run() {
	//Setup();
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Editor::Destroy() {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(editorRenderer.get());
	SDL_DestroyWindow(editorWindow.get());
	SDL_Quit();
}