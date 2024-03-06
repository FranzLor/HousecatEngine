#pragma once

#include <SDL.h>
#include <imgui/imgui_impl_sdl.h>

class Source {
private:
	bool isRunning;
	bool launchGame;
	bool launchEditor;

	int millisecsPreviousFrame;
	
	SDL_Window* windowSource;

	SDL_Renderer* rendererSource;

	ImGuiContext* sourceImGuiContext;

public:
	Source();
	~Source();

	const int SOURCE_FPS = 60;
	const int SOURCE_MILLISECS_PER_FRAME = 1000 / SOURCE_FPS;

	void Initialize();
	void Run();
	void Input();
	void Update();
	void Render();
	void Destroy();

	bool LaunchGame() const { return launchGame; }
	bool LaunchEditor() const { return launchEditor; }

	static int windowSourceWidth;
	static int windowSourceHeight;

};

