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

#include "ui/IconsFontAwesome6.h"


Editor::Editor()
	: isRunning(true),
	isDarkMode(false),
	millisecsPreviousFrame(0),
	deltaTime(0.0f),
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

	//fonts
	ImGuiIO& IO = ImGui::GetIO();
	//IO.Fonts->AddFontDefault();


	float textFontSize = 18.0f;
	ImFont* robotoFont = IO.Fonts->AddFontFromFileTTF("assets/fonts/roboto.regular.ttf", textFontSize);
	if (!robotoFont) {
		Logger::Error("Failed to load font: assets/fonts/roboto.regular.ttf");
	}

	float baseFontSize = 22.0f;
	float iconFontSize = baseFontSize * 2.0f / 3.0f;

	ImFontConfig config;
	config.MergeMode = true;
	config.PixelSnapH = true;
	config.GlyphMinAdvanceX = iconFontSize;
	static const ImWchar icons_ranges[] = { ICON_MIN_FA , ICON_MAX_FA , 0 };

	ImFont* FAIconsFont = IO.Fonts->AddFontFromFileTTF("assets/fonts/fa-solid-900.ttf", iconFontSize, &config, icons_ranges);
	if (!FAIconsFont) {
		Logger::Error("Failed to load font: assets/fonts/fa-solid-900.ttf");
	}

	IO.Fonts->Build();

	IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	IO.ConfigWindowsMoveFromTitleBarOnly = true;




	//TODO
	assetManager = std::make_unique<AssetManager>();
	//textures
	assetManager->AddEditorTexture(editorRenderer, "pan", "./assets/icon/panV2.png");

	//SYSTEMS
	//call Housecat to add systems for editor
	auto& housecat = Housecat::GetInstance();
	housecat.AddSystem<RenderSystem>();
	housecat.AddSystem<EditorUIRendering>();
	housecat.AddSystem<RenderColliderSystem>();
	housecat.AddSystem<AnimationSystem>();
}



void Editor::ProcessInput() {
	//keyboard states
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

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
			break;
		}

		//CTRL
		//zoom shortcuts - keyboard
		if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL]) {
			if (keyState[SDL_SCANCODE_EQUALS]) {
				AdjustZoom(1.4);
			}
			if (keyState[SDL_SCANCODE_MINUS]) {
				AdjustZoom(-1.4);
			}
		}

		//shift
		//camera movement
		if (keyState[SDL_SCANCODE_LSHIFT]) {
			KeyboardCameraController(event);
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
	deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;
	//store curr. frame time
	millisecsPreviousFrame = SDL_GetTicks();

	Housecat::GetInstance().Update();

	//styling - dark mode
	if (Housecat::GetInstance().GetSystem<EditorUIRendering>().GetDarkMode()) {
		isDarkMode = true;
	}
	//light mode
	else {
		isDarkMode = false;
	}

	if (Housecat::GetInstance().GetSystem<EditorUIRendering>().GetExit()) {
		isRunning = false;
	}
}


void Editor::Render() {
	//styling
	if (!isDarkMode) {
		SDL_SetRenderDrawColor(editorRenderer.get(), 185, 194, 202, 255);
	}
	else {
		SDL_SetRenderDrawColor(editorRenderer.get(), 45, 51, 56, 255);
	}
	SDL_RenderClear(editorRenderer.get());

	//render editor
	Housecat::GetInstance().GetSystem<EditorUIRendering>().RenderGrid(editorRenderer, camera, zoom);

	Housecat::GetInstance().GetSystem<RenderSystem>().UpdateEditor(editorRenderer.get(), assetManager, camera, zoom);


	//TODO
	//render collider
	//render animation


	Housecat::GetInstance().GetSystem<EditorUIRendering>().Update(editorRenderer, assetManager, camera, mouseTile,
		event, zoom, deltaTime);


	SDL_RenderPresent(editorRenderer.get());
}

void Editor::CameraController(SDL_Event& event) {
	if (event.type == SDL_MOUSEWHEEL) {
		AdjustZoom(event.wheel.y);
	}
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
			camera.y += camSpeed;
			break;
		case SDLK_a:
			camera.x += camSpeed;
			break;
		case SDLK_s:
			camera.y -= camSpeed;
			break;
		case SDLK_d:
			camera.x -= camSpeed;
			break;
		}
	}
}

void Editor::AdjustZoom(double direction) {
	constexpr float zoomStep = 0.1f;

	if (direction > 0) {
		zoom = std::min(zoom + zoomStep, 2.8f);
	}
	else if (direction < 0) {
		zoom = std::max(zoom - zoomStep, 0.2f);
	}

	camera.h = static_cast<int>(windowEditorHeight * zoom);
	camera.w = static_cast<int>(windowEditorWidth * zoom);
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