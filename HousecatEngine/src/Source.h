#pragma once

#include <SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>


//----------------------------------------------------//
//                    SOURCE CLASS                    //
// Initial interface for Housecat game engine,        //
// providing options to launch the game or editor.    //
//----------------------------------------------------//


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




/**
 *
 * @class Source
 * @brief Entry point for the Housecat game engine, presenting options to launch the game or the editor.
 *
 * This class manages the initial window where the user can choose to start the game, open the level editor, or exit.
 * It sets up SDL and ImGui for rendering this initial interface and handles all user inputs to make the selection.
 * It is responsible for initializing SDL, creating the main window and renderer, and handling the event loop until
 * a selection is made or the application is closed.
 *
 * Usage:
 * - The instance of Source is created in the main application function.
 * - It initializes SDL and ImGui, then enters a loop where it waits for user input.
 * - Depending on user selection, it either launches the game or the editor.
 *
 * Example:
 *   int main(int argc, char* argv[]) {
 *       Source source;
 *       source.Initialize();
 *       source.Run();
 *       source.Destroy();
 *       return 0;
 *   }
 *
 * Key Components:
 * - `SDL_Window*` and `SDL_Renderer*`: Handles rendering operations.
 * - `ImGuiContext*`: For rendering initial selection UI.
 *
 * Key Methods:
 * - Initialize(): Sets up the SDL environment and ImGui context.
 * - Run(): Starts the loop that handles input and rendering until a selection is made.
 * - Destroy(): Cleans up resources, ensuring a proper shutdown.
 *
 * Note:
 * - This class is the first point of interaction when launching the Housecat engine and acts as a gateway to either
 *   the game or the editor based on user choice.
 * 
 */