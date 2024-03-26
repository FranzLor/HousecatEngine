#include "Source.h"
#include "logger/Logger.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

int Source::windowSourceWidth;
int Source::windowSourceHeight;

Source::Source() 
	: isRunning(false),
	launchGame(false),
	launchEditor(false),
	millisecsPreviousFrame(0),
	windowSource(nullptr),
	rendererSource(nullptr),
	sourceImGuiContext(0) {

	Logger::SDLVersion();
	Logger::ImGuiVersion();

	Logger::Lifecycle("Source Constructor Called!");
}

Source::~Source() {
	Logger::Lifecycle("Source Destructor Called!");
}


void Source::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Error("Error Initializing Source SDL!");
		return;
	}

	if (TTF_Init() != 0) {
		Logger::Error("Error Initializing Source Font!");
		return;
	}

	SDL_DisplayMode sourceDisplayMode;
	SDL_GetCurrentDisplayMode(0, &sourceDisplayMode);
	windowSourceWidth = 400;
	windowSourceHeight = 400;

	windowSource = SDL_CreateWindow(
		"Housecat",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowSourceWidth,
		windowSourceHeight,
		0
	);

	if (!windowSource) {
		Logger::Error("Error Creating SDL Source Window!");
		return;
	}

	rendererSource = SDL_CreateRenderer(windowSource, -1, 0);
	if (!rendererSource) {
		Logger::Error("Error Creating SDL Source Renderer!");
		return;
	}
	SDL_SetWindowFullscreen(windowSource, SDL_FALSE);
	isRunning = true;

	IMGUI_CHECKVERSION();
	sourceImGuiContext = ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(windowSource, rendererSource);
	ImGui_ImplSDLRenderer2_Init(rendererSource);

	//fonts
	ImGuiIO& IO = ImGui::GetIO();

	float textFontSize = 19.0f;
	ImFont* robotoFont = IO.Fonts->AddFontFromFileTTF("assets/fonts/roboto.regular.ttf", textFontSize);
	if (!robotoFont) {
		Logger::Error("Failed to load font : assets/fonts/roboto.regular.ttf");
	}

	IO.Fonts->Build();
}





void Source::Input() {
	SDL_Event sdlSourceEvent;

	while (SDL_PollEvent(&sdlSourceEvent)) {
		//handle ImGui SDL input
		ImGui_ImplSDL2_ProcessEvent(&sdlSourceEvent);
		ImGuiIO& IO = ImGui::GetIO();

		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		IO.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		IO.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		IO.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

		//handle core SDL events (close win, key pressed, etc...)
		switch (sdlSourceEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlSourceEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			break;
		}
	}
}



void Source::Update() {
	//capped frame rate
	int timeToWait = SOURCE_MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	//frame delay
	if (timeToWait > 0 && timeToWait <= SOURCE_MILLISECS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}
	//diff. in ticks since last frame converted to secs
	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
	//store current frame time
	millisecsPreviousFrame = SDL_GetTicks();
}




void Source::Render() {
	SDL_SetRenderDrawColor(rendererSource, 21, 21, 21, 255);
	SDL_RenderClear(rendererSource);

	ImGui::SetCurrentContext(sourceImGuiContext);

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags windowFlags = (
		ImGuiWindowFlags_NoTitleBar,
		ImGuiWindowFlags_NoResize,
		ImGuiWindowFlags_NoMove,
		ImGuiWindowFlags_NoScrollbar,
		ImGuiWindowFlags_NoScrollWithMouse,
		ImGuiWindowFlags_NoCollapse,
		ImGuiWindowFlags_NoBackground,
		ImGuiWindowFlags_NoNavInputs,
		ImGuiWindowFlags_NoDecoration
	);

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(windowSourceWidth), static_cast<float>(windowSourceHeight)), ImGuiCond_Always);

	ImGui::Begin("Housecat", nullptr, windowFlags);
	float totalButtonHeight = 3 * 110;
	float spacing = (windowSourceHeight - totalButtonHeight) / 2;
	float buttonWidth = static_cast<float>(windowSourceWidth) - 15;

	ImGui::Text("Housecat Game Engine v1");
	
	if (ImGui::Button("GAME", ImVec2(buttonWidth, 110))) {
		launchGame = true;
		isRunning = false;
	}
	ImGui::Dummy(ImVec2(0, 0));
	if (ImGui::Button("EDITOR", ImVec2(buttonWidth, 110))) {
		launchEditor = true;
		isRunning = false;
	}
	ImGui::Dummy(ImVec2(0, 0));
	if (ImGui::Button("EXIT", ImVec2(buttonWidth, 110))) {
		isRunning = false;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(rendererSource);

}



void Source::Run() {
	while (isRunning) {
		Input();
		Update();
		Render();
	} 
}

void Source::Destroy() {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(rendererSource);
	SDL_DestroyWindow(windowSource);
	SDL_Quit();
}
