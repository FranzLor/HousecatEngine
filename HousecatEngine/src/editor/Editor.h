#pragma once

#include "../input/GlobalInputHandler.h"

#include <SDL.h>
#include <imgui/imgui_impl_sdl.h>

const int EDITOR_FPS = 144;
const int EDITOR_MILLISECS_PER_FRAME = 1000 / EDITOR_FPS;

class Editor {
private:
	bool isRunning;

	int millisecsPreviousFrame;

	SDL_Window* windowEditor;
	SDL_Renderer* rendererEditor;

	ImGuiContext* editorImGuiContext;

public:
	Editor();
	~Editor();

	void Initialize();
	void Run();
	//void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	bool IsRunning() const { return isRunning; }
	void SetRunning(bool running) { isRunning = running; }

	auto GetWindowID();

	static int windowEditorWidth;
	static int windowEditorHeight;

};

