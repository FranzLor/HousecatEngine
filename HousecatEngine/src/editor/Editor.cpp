#include "Editor.h"

#include "../logger/Logger.h"

#include <SDL_ttf.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include "ui/EditorUIRendering.h"

Editor::Editor()
	: isRunning(false),
	millisecsPreviousFrame(0),
	zoom(0.0f),
	mouseTile(),
	camera(),
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

	IMGUI_CHECKVERSION();
	//TODO
	//AssetManager Init here


	//ImGui Init
	editorImGuiContext = ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(editorWindow.get(), editorRenderer.get());
	ImGui_ImplSDLRenderer2_Init(editorRenderer.get());

	//TODO
	assetManager = std::make_unique<AssetManager>();

}



void Editor::ProcessInput() {
	SDL_Event sdlEditorEvent;

	while (SDL_PollEvent(&sdlEditorEvent)) {
		//handle ImGui SDL input
		ImGui_ImplSDL2_ProcessEvent(&sdlEditorEvent);
		ImGuiIO& IO = ImGui::GetIO();

		//mouse buttons
		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		IO.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		IO.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		IO.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE);
		IO.MouseDown[2] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

		switch (sdlEditorEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			if (!IO.WantCaptureMouse) {
				//TDOOD
				//zoom -> event
			}
			break;
		case SDL_KEYDOWN:
			if (sdlEditorEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;

			}
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
	//Housecat manager update
	//Grab render gui elements
	//exit?
}


void Editor::Render() {
	SDL_SetRenderDrawColor(editorRenderer.get(), 10, 10, 10, 255);
	SDL_RenderClear(editorRenderer.get());

	//render GUI

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::SetCurrentContext(editorImGuiContext);

	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

	ImGui::EndFrame();

	SDL_RenderPresent(editorRenderer.get());
}

void Editor::CameraController(SDL_Event& event) {
	//TODO
	//sdl event -> mousewheel zoom
}

void Editor::KeyboardCameraController() {
	//todo
	//sdl event -> keydown
	//switch case keys
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