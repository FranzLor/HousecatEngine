#include "Editor.h"

#include "../input/GlobalInputHandler.h"
#include "../logger/Logger.h"

#include <SDL_ttf.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

int Editor::windowEditorWidth;
int Editor::windowEditorHeight;

Editor::Editor() : isRunning(false), millisecsPreviousFrame(0), windowEditor(nullptr), rendererEditor(nullptr), editorImGuiContext(nullptr) {
	Logger::Lifecycle("Editor Constructor Called!");
}

Editor::~Editor() {
	Logger::Lifecycle("Editor Destructor Called!");
}

void Editor::Initialize() {
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

	//editor window
	int windowEditorWidth = 1800;
	int windowEditorHeight = 900;

	windowEditor = SDL_CreateWindow(
		"Housecat Editor",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowEditorWidth,
		windowEditorHeight,
		0
	);

	if (!windowEditor) {
		Logger::Error("Error Creating SDL Editor Window!");
		return;
	}
	rendererEditor = SDL_CreateRenderer(windowEditor, -1, 0);
	if (!rendererEditor) {
		Logger::Error("Error Creating Editor Renderer!");
		return;
	}

	SDL_SetWindowFullscreen(windowEditor, SDL_FALSE);
	isRunning = true;

	IMGUI_CHECKVERSION();
	editorImGuiContext = ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(windowEditor, rendererEditor);
	ImGui_ImplSDLRenderer2_Init(rendererEditor);
}



void Editor::ProcessInput() {
	SDL_Event sdlEditorEvent;

	//handle ImGui SDL input
	ImGui_ImplSDL2_ProcessEvent(&sdlEditorEvent);
	ImGuiIO& io = ImGui::GetIO();

	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

	while (SDL_PollEvent(&sdlEditorEvent)) {
		switch (sdlEditorEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEditorEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;

			}
			break;
		}
	}
}


auto Editor::GetWindowID(){
	return SDL_GetWindowID(windowEditor);
}

void Editor::Update() {
	//capped frames
	int waitingTime = EDITOR_MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (waitingTime > 0 && waitingTime <= EDITOR_MILLISECS_PER_FRAME) {
		SDL_Delay(waitingTime);
	}
	//diff. in ticks since last frame converted to secs
	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
	//store curr. frame time
	millisecsPreviousFrame = SDL_GetTicks();

}

void Editor::Render() {
	SDL_RenderClear(rendererEditor);
	SDL_SetRenderDrawColor(rendererEditor, 10, 10, 10, 255);

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::SetCurrentContext(editorImGuiContext);

	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

	ImGui::EndFrame();

	SDL_RenderPresent(rendererEditor);
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

	SDL_DestroyRenderer(rendererEditor);
	SDL_DestroyWindow(windowEditor);
	SDL_Quit();
}