#pragma once

#include <SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include "./utilities/SDLUtility.h"

#include "../assetmanager/AssetManager.h"


//-----------------------------------------------------//
//                      Editor                         //
//    Main class for the Housecat game editor that     //
//    handles initialization, input processing,       //
//    updating, and rendering.                         //
//-----------------------------------------------------//

class Editor {
private:
	//editor window
	static const int windowBar = 25;
	static const int windowEditorWidth = 1920;
	static const int windowEditorHeight = 1080 - windowBar;

	const int EDITOR_FPS = 144;
	const int EDITOR_MILLISECS_PER_FRAME = 1000 / EDITOR_FPS;
	int millisecsPreviousFrame;

	float deltaTime;

	//camera
	const int defaultCamX = -350;
	const int defaultCamY = -170;
	const int defaultZoom = 1;
	const int camSpeed = 5;

	bool isRunning;

	bool isDarkMode;

	float zoom;

	SDL_Rect mouseTile;

	SDL_Rect camera;

	SDL_Event event;

	EditorWindow editorWindow;
	EditorRenderer editorRenderer;

	//ImGui
	ImGuiContext* editorImGuiContext;

	//AssetManager ptr
	AssetManagerPtr assetManager;

	void CameraController(SDL_Event& event);
	void KeyboardCameraController(SDL_Event& event);

	inline const bool& GetDarkMode() const {
		return isDarkMode; 
	}

	inline void SetDarkMode(bool darkMode) {
		isDarkMode = darkMode;
	}

public:
	Editor();
	~Editor();

	void Initialize();
	void Run();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	void AdjustZoom(double direction);

	bool IsRunning() const { return isRunning; }
	void SetRunning(bool running) { isRunning = running; }

};



/**
 * @file Editor.h
 * @brief Manages the lifecycle of the Housecat game editor.
 *
 * The Editor class initializes and manages the SDL and ImGui contexts,
 * orchestrates the main loop, handles user input, updates game/editor state,
 * and performs rendering. It serves as the entry point for the editor's
 * operations and integrates various subsystems such as rendering, UI management,
 * and asset management.
 *
 * Key Responsibilities:
 * - Initialize and configure SDL and ImGui.
 * - Handle main event loop including input processing.
 * - Update game/editor states and manage rendering calls.
 * - Clean up and shut down the editor properly.
 */