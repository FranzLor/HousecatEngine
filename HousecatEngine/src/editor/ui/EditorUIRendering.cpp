#include <imgui/imgui.h>

#include "../utilities/SDLUtility.h"

#include "EditorUIManager.h"

#include "EditorCanvas.h"
#include "EditorUIRendering.h"

#include "../src/logger/Logger.h"
#include <imgui/imgui_impl_sdlrenderer2.h>
#include <imgui/imgui_impl_sdl2.h>


EditorUIRendering::EditorUIRendering()
	: canvasWidth(960),
	canvasHeight(640),
	canvasPreviousWidth(canvasWidth),
	canvasPreviousHeight(canvasHeight),
	tileSize(32),
	tilePrevSize(tileSize),
	createdTiles(false),
	removedTiles(false),
	gridX(0),
	gridY(0),
	gridSnap(false) {

	canvas = std::make_shared<EditorCanvas>(canvasWidth, canvasHeight);
	mouse = std::make_shared<Mouse>();
	editorUIManager = std::make_shared<EditorUIManager>(mouse);
	editManager = std::make_unique<EditManager>();

	//call ImGui setup
	editorUIManager->InitImGui();
	editorUIManager->Setup();

	canvasPreviousWidth = 960;
	canvasPreviousHeight = 640;

	Logger::Lifecycle("ImGuiRendering Constructor Called!");
}

EditorUIRendering::~EditorUIRendering() {
	Logger::Lifecycle("ImGuiRendering Destructor Called!");
}


void EditorUIRendering::Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, const float& zoom, const float& dT) {
	//start frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			editorUIManager->ShowFileMenu(renderer, assetManager, canvas, tileSize);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {
			//show edit menu
			if (ImGui::MenuItem("Undo", "CTRL + Z")) {
				editManager->Undo();
			}
			if (ImGui::MenuItem("Redo", "CTRL + Y")) {
				editManager->Redo();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			//show view menu
			//call View();

			//if (ImGui::Checkbox("Show Grid", &grid) {
			// 
			//}
			//if (ImGui::Checkbox("Snap to Grid", &grid) {
			// 
			//}
			if (ImGui::MenuItem("Zoom In", "CTRL + +")) {

			}
			if (ImGui::MenuItem("Zoom Out", "CTRL + -")) {

			}
			if (ImGui::MenuItem("Fit to View")) {

			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Project")) {
			//show project menu

			//clamp
			//if (ImGui::InputInt("Tile Size", &tileSize, x, x)) {
			//	if (tileSize <= x) {
			//		tileSize = x;
			//}

			//if (ImGui::InputInt("Canvas Width", &canvasWidth, &tileSize, &tileSize)) {
			//	if width increase

			//clamp
			//	if (canvasWidth <= x) {
			//    canvasWidth = x;
			//	  SetWidth
			//	}
			//}

			//if (ImGui::InputInt("Canvas Height", &canvasHeight, &tileSize, &tileSize)) {
			//	if width increase

			//clamp
			//	if (canvasHeight <= x) {
			//    canvasHeight = x;
			//	  SetHeight
			//	}
			//}
			ImGui::EndMenu();
		}

	}

	ImGui::EndMainMenuBar();


	//render imgui
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

}

void EditorUIRendering::RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom) {
	//used for changing grid size with canvas
	auto tilesX = (canvas->GetCanvasWidth() / tileSize);
	auto tilesY = (canvas->GetCanvasHeight() / tileSize);

	//grid lines
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);

	for (int i = 0; i < canvas->GetCanvasWidth(); i += tileSize) {
		SDL_Rect line = { i - camera.x, -camera.y, 1, canvas->GetCanvasHeight() };
		SDL_RenderFillRect(renderer.get(), &line);
	}
	for (int i = 0; i < canvas->GetCanvasHeight(); i += tileSize) {
		SDL_Rect line = { -camera.x, i - camera.y, canvas->GetCanvasWidth(), 1 };
		SDL_RenderFillRect(renderer.get(), &line);
	}

	//tile squares and collider
	SDL_SetRenderDrawColor(renderer.get(), 125, 125, 125, 255);

	for (int i = 0; i < tilesY; i++) {
		for (int j = 0; j < tilesX; j++) {
			SDL_Rect newRect = {
				(std::floor(j * tileSize * zoom)) - camera.x,
				(std::floor(i * tileSize * zoom)) - camera.y,
				std::ceil(tileSize * zoom),
				std::ceil(tileSize * zoom)
			};

			SDL_RenderFillRect(renderer.get(), &newRect);
		}
	}
}


void EditorUIRendering::CreateNewCanvas() {
	//resetting canvas
	tileSize = 32;
	canvasWidth = 960;
	canvasHeight = 640;
	createdTiles = true;
	gridSnap = false;

	for (auto& entity : GetSystemEntities()) {
		entity.Kill();
	}

	editManager->Clear();
}

void EditorUIRendering::UpdateCanvas() {
	canvasWidth = canvas->GetCanvasWidth();
	canvasHeight = canvas->GetCanvasHeight();
}

void EditorUIRendering::ShowMouseLocation(SDL_Rect& mouseTile, SDL_Rect& camera) {
	//show mouse on canvas
	if (!mouse->MouseOutOfBounds() && (createdTiles)) {
		gridX = static_cast<int>(mouse->GetMousePosition().x) / tileSize;
		gridY = static_cast<int>(mouse->GetMousePosition().y) / tileSize;

		ImGui::TextColored(ImVec4(0, 255, 255, 1), "Grid: %d, %d", gridX, gridY);
		ImGui::Spacing();

		if (gridSnap) {
			ImGui::TextColored(ImVec4(0, 255, 255, 1), "Mouse Tile: %d, %d", tileSize * gridX, tileSize * gridY);
		}
		else {
			ImGui::TextColored(ImVec4
				(0, 255, 255, 1),
				"Mouse Tile: %d, %d", 
				static_cast<int>(mouse->GetMousePosition().x),
				static_cast<int>(mouse->GetMousePosition().y)
			);
		}
	}
}

const bool EditorUIRendering::MouseOutOfBounds() const {
	if (mouse->GetMousePosition().x > canvasWidth - (tileSize / 3) || mouse->GetMousePosition().y > canvasHeight - (tileSize / 3)) {
		return true;
	}
	return false;
}
