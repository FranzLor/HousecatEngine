
#include <imgui/imgui.h>

#include "EditorUIManager.h"

#include "../utilities/SDLUtility.h"
#include "../editmanager/EditManager.h"

EditorUIManager::EditorUIManager()
//int tileWidth, tileHeight, scaleX, scaleY, layer, tileOffset, srcRectX, srcRectY
	: tileAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tilePrevAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tileWidth(16),
	tileHeight(16),
	textureWidth(0),
	textureHeight(0),
	Undo(false),
	Redo(false),
	file(""),
	assetID(""),
	tilesets(),
	tilesetsTarget(),
	editManager(std::make_unique<EditManager>()) {

	//Logger::Lifecycle("ImGuiFunctions Constructor Called!");
}

EditorUIManager::~EditorUIManager() {
	//Logger::Lifecycle("ImGuiFunctions Destructor Called!");
}

//TODO
//ImGui management
void EditorUIManager::InitImGui() {
	//TODO
	//ImGui
}

//TODO
//menu bar management
void EditorUIManager::ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, int& tileSize) {
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("New Project", "CTRL+N")) {
			NewProject();
		}
		if (ImGui::MenuItem("Open Project", "CTRL+O")) {
			OpenProject(renderer, assetManager, canvas, tileSize);
		}
		if (ImGui::MenuItem("Save", "CTRL+S")) {
			Save(renderer, assetManager, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);

			//TODO 
			//file management
		}
		if (ImGui::MenuItem("Exit", "ALT+F4")) {
			//EXIT
		}
		ImGui::EndMenu();
	}
}

void EditorUIManager::ShowEditMenu() {
	if (ImGui::BeginMenu("Edit")) {
		if (ImGui::MenuItem("Undo", "CTRL+Z")) {
			//Undo = true;
		}
		if (ImGui::MenuItem("Redo", "CTRL+Y")) {
			//Redo = true;
		}
		ImGui::EndMenu();
	}
}

void EditorUIManager::ShowViewMenu() {
	if (ImGui::BeginMenu("View")) {
		if (ImGui::MenuItem("Show Grid", "CTRL+G")) {
			//TODO
			//grid management
		}
		if (ImGui::MenuItem("Grid Snapping")) {
			//TODO

		}
		if (ImGui::MenuItem("Zoom In")) {
			//TODO

		}
		if (ImGui::MenuItem("Zoom Out")) {
			//TODO

		}
		ImGui::EndMenu();
	}
}

void EditorUIManager::ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager) {
	if (ImGui::BeginMenu("Add Tileset")) {
		//TODO
		//file management


	}
	ImGui::EndMenu();
}

//TODO
//file management
void EditorUIManager::NewProject() {

}

void EditorUIManager::OpenProject(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, int& tileSize) {

}

void EditorUIManager::Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize) {

}

//TODO
//tileset management
void EditorUIManager::TileAttributes(const AssetManagerPtr& assetManager) {

}

void EditorUIManager::SetTileset(const AssetManagerPtr& assetManager) {

}


//TODO
//shortcut management
void EditorUIManager::ApplyShortcuts() {

}
