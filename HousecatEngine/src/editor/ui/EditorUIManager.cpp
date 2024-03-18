
#include <imgui/imgui.h>

#include "EditorUIManager.h"

#include "../utilities/SDLUtility.h"
#include "../utilities/editmanager/EditManager.h"

EditorUIManager::EditorUIManager(class std::shared_ptr<Mouse>& mouse)
//int tileWidth, tileHeight, scaleX, scaleY, layer, tileOffset, srcRectX, srcRectY
	: tileAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tilePrevAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tileWidth(16),
	tileHeight(16),
	textureWidth(0),
	textureHeight(0),
	isImageLoaded(false),
	Undo(false),
	Redo(false),
	fileName(""),
	assetID(""),
	tilesets(),
	tilesetsTarget(),
	mouse(mouse),
	editManager(std::make_unique<EditManager>()) {

	//Logger::Lifecycle("ImGuiFunctions Constructor Called!");
}

EditorUIManager::~EditorUIManager() {
	//Logger::Lifecycle("ImGuiFunctions Destructor Called!");
}

//TODO
//ImGui management
void EditorUIManager::InitImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//ImGuiIO& io = ImGui::GetIO(); (void)io;

	//TODO
	//KEYS
}

void EditorUIManager::Setup() {
	//TODO
	//ImGui
}

//TODO
//menu bar management
void EditorUIManager::ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, int& tileSize) {
	//MENU file interact
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
	if (ImGui::MenuItem("Save As", "CTRL+SHIFT+S")) {
		//TODO
		//file management
		std::string file = fileDialog->SaveFile();

		if (file != "") {
			//change filename to dialog filename
			fileName = file;
			projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
		}
	}

	if (ImGui::MenuItem("Export to Lua Table")) {
		std::string tileName = fileDialog->SaveFile();

		if (fileName != "" || !fileName.empty()) {
			luaFile = fileName;
			projectManagement->SaveAsLua(luaFile, tilesets, tilesetsTarget, tileSize);
		}
	}

	if (ImGui::MenuItem("Exit", "ALT+F4")) {
		//EXIT
	}
}

void EditorUIManager::ShowEditMenu() {
	//MENU edit interact
	if (ImGui::MenuItem("Undo", "CTRL+Z")) {
		//Undo = true;
	}
	if (ImGui::MenuItem("Redo", "CTRL+Y")) {
		//Redo = true;
	}

}

void EditorUIManager::ShowViewMenu() {
	//MENU view interact
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

}

void EditorUIManager::ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager) {
	//MENU project interact
	if (ImGui::MenuItem("Change Map")) {
		//TODO
	}

	if (ImGui::MenuItem("New Tileset")) {
		FileDialogue fileDialog;
		imageName = fileDialog.OpenFile();

		if (imageName != "" || !imageName.empty()) {
			std::filesystem::path path(imageName);
			assetID = path.stem().string();

			for (const auto& assets : tilesets) {
				if (assets == assetID) {
					return;
				}
			}

			assetManager->AddEditorTexture(renderer, assetID, imageName);

			if (SDL_QueryTexture(assetManager->ReturnEditorTexture(assetID).get(), NULL, NULL, &tileWidth, &tileHeight) != 0) {
				isImageLoaded = false;
			}
			else {
				isImageLoaded = true;
				tilesets.push_back(assetID);
				tilesetsTarget.push_back(imageName);
			}
		}

	}
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
void EditorUIManager::TilesetWindow(const AssetManagerPtr& assetManager, const glm::vec2& mouseRect) {
	std::string currentTileset = "Tileset";

	if (ImGui::Begin(currentTileset.c_str())) {

		ImGui::Text("Scaling");
		ImGui::SliderInt("Scale X", &tileAttributes.scaleX, 1, 10);
		ImGui::SliderInt("Scale Y", &tileAttributes.scaleY, 1, 10);


		ImGui::Text("Sprite");
		if (ImGui::InputInt("Tile X", &tileAttributes.mouseRectX, 8, 8)) {
			tileAttributes.mouseRectX = (tileAttributes.mouseRectX / 8) * 8;
			if (tileAttributes.mouseRectX <= 0) {
				tileAttributes.mouseRectX = 0;
			}
		}
		if (ImGui::InputInt("Tile Y", &tileAttributes.mouseRectY, 8, 8)) {
			tileAttributes.mouseRectY = (tileAttributes.mouseRectY / 8) * 8;
			if (tileAttributes.mouseRectY <= 0) {
				tileAttributes.mouseRectY = 0;
			}
		}



		////resize on mouse scroll
		//float scrollX = ImGui::GetScrollX();
		//float scrollY = ImGui::GetScrollY();
		//int imageWidth = textureWidth * 2;
		//int imageHeight = textureHeight;

		//ImGui::Image(assetManager->GetTexture(assetID), ImVec2(imageWidth, imageHeight));

		//int mousePosX = static_cast<int>(ImGui::GetMousePos().x - ImGui::GetWindowPos().x + scrollX);
		//int mousePosY = static_cast<int>(ImGui::GetMousePos().y - ImGui::GetWindowPos().y + scrollY);

		//int tileCol = imageWidth / (mouseRect.x * 2);
		//int tileRow = imageHeight / (mouseRect.y * 2);

		////store highlighted tiles
		//auto highlightTiles = ImGui::GetWindowDrawList();

		////render tileset textures
		//for (int c = 0; c < tileCol; c++) {
		//	for (int r = 0; r < tileRow; r++) {
		//		// Calculate tile boundaries
		//		int tileAX = (imageWidth / tileCol) * c;
		//		int tileAY = (imageHeight / tileRow) * r;
		//		int tileBX = tileAX + (imageWidth / tileCol);
		//		int tileBY = tileAX + (imageHeight / tileRow);

		//		//wihtin tile area
		//		if (mousePosX >= tileAX && mousePosX <= tileBX && mousePosY >= tileAY && mousePosY <= tileBY) {
		//			//highlight blueish
		//			highlightTiles->AddRectFilled(ImVec2(tileAX, tileAY), ImVec2(tileBX, tileBY), IM_COL32(0, 0, 255, 100));

		//			if (ImGui::IsMouseClicked(0)) {
		//				tileAttributes.srcRectX = c * (int)mouseRect.x * 2;
		//				tileAttributes.srcRectY = r * (int)mouseRect.y * 2;
		//			}
		//		}
		//	}
		//}
		ImGui::End();
	}
}

void EditorUIManager::TileAttributes(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse) {
	//tile attributes interact
	if (ImGui::MenuItem("Tilesets")) {
		//multiple tilesets
	}
	if (ImGui::MenuItem("Transform")) {
		//scale
	}
	if (ImGui::MenuItem("Sprite")) {
		//mouse x mouse y

	}
}

void EditorUIManager::TilesetLayers(const AssetManagerPtr& assetManager) {
	//layers interact
	if (ImGui::MenuItem("Layer")) {

	}
}


//TODO
//shortcut management
void EditorUIManager::ApplyShortcuts() {

}
