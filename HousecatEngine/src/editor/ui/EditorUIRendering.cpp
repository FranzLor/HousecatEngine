#include <imgui/imgui.h>

#include "../utilities/SDLUtility.h"

#include "EditorUIManager.h"

#include "EditorCanvas.h"
#include "EditorUIRendering.h"

#include "../src/logger/Logger.h"


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

	canvasPreviousWidth = canvasWidth;
	canvasPreviousHeight = canvasHeight;

	Logger::Lifecycle("ImGuiRendering Constructor Called!");
}

EditorUIRendering::~EditorUIRendering() {
	Logger::Lifecycle("ImGuiRendering Destructor Called!");
}


void EditorUIRendering::Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, const float& zoom, const float& dT) {
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
		}

	}

	ImGui::EndMainMenuBar();


}

void EditorUIRendering::RenderGrid(SDL_Renderer& renderer, SDL_Rect& camera, const float& zoom) {
	//render
	//for tiles y
	//for tiles x
}


void EditorUIRendering::CreateNewCanvas() {
	//default val

	//destroy
}

void EditorUIRendering::UpdateCanvas() {
	//update val?
}
