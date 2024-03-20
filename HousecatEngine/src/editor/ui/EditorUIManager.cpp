
#include <imgui/imgui.h>

#include "EditorUIManager.h"

#include "../utilities/SDLUtility.h"
#include "../utilities/editmanager/EditManager.h"

EditorUIManager::EditorUIManager(std::shared_ptr<Mouse>& mouse)
//int tileWidth, tileHeight, scaleX, scaleY, layer, tileOffset, srcRectX, srcRectY
	: tileAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tilePrevAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tileWidth(16),
	tileHeight(16),
	textureWidth(0),
	textureHeight(0),
	loadTileset(false),
	isReset(false),
	isNewFile(false),
	newCanvas(false),
	Undo(false),
	Redo(false),
	fileName(""),
	assetID(""),
	tilesets(),
	tilesetsTarget(),
	mouse(mouse),

	fileDialog(std::make_unique<FileDialogue>()),
	projectManagement(std::make_unique<ProjectManagement>()) {

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

	ImGuiIO& IO = ImGui::GetIO(); (void)IO;

	//TODO
	//KEYS
}

void EditorUIManager::Setup() {
	//TODO
	//ImGui
}

//TODO
//menu bar management
void EditorUIManager::ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, sol::state& lua, int& tileSize) {
	//MENU file interact
	if (ImGui::MenuItem("New Project", "CTRL+N")) {
		isNewFile = true;
	}
	if (ImGui::MenuItem("Open Project", "CTRL+O")) {
		Open(renderer, assetManager, canvas, lua, tileSize);
	}
	if (ImGui::MenuItem("Save", "CTRL+S")) {
		Save(renderer, assetManager, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
	}
	if (ImGui::MenuItem("Save As", "CTRL+SHIFT+S")) {
		//TODO
		//file management
		std::string file;
		file = fileDialog->SaveFile();

		if (!file.empty()) {
			fileName = file;
			projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
		}
	}

	if (ImGui::MenuItem("Export to Lua Table")) {
		std::string luaFileName;
		luaFileName = fileDialog->SaveFile();

		if (!luaFileName.empty()) {
			// Set Lua file to the selected filename
			luaFile = luaFileName;
			projectManagement->SaveAsLua(luaFile, tilesets, tilesetsTarget, tileSize);
		}
	}

	if (ImGui::MenuItem("Exit", "ALT+F4")) {
		//EXIT
	}
}

//void EditorUIManager::ShowEditMenu() {
//	//MENU edit interact
//	if (ImGui::MenuItem("Undo", "CTRL+Z")) {
//		//Undo = true;
//	}
//	if (ImGui::MenuItem("Redo", "CTRL+Y")) {
//		//Redo = true;
//	}
//
//}

//void EditorUIManager::ShowViewMenu() {
//	//MENU view interact
//	if (ImGui::MenuItem("Show Grid", "CTRL+G")) {
//		//TODO
//		//grid management
//	}
//	if (ImGui::MenuItem("Grid Snapping")) {
//		//TODO
//
//	}
//	if (ImGui::MenuItem("Zoom In")) {
//		//TODO
//
//	}
//	if (ImGui::MenuItem("Zoom Out")) {
//		//TODO
//
//	}
//
//}

void EditorUIManager::ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager) {
	//MENU project interact
	//if (ImGui::MenuItem("New Map")) {
	//	//TODO
	//}

	if (ImGui::MenuItem("Add Tileset")) {
		FileDialogue fileDialog;
		imageName = fileDialog.OpenTextureFile();

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
				const char* error = SDL_GetError();
				loadTileset = false;
			}
			else {
				loadTileset = true;
				tilesets.push_back(assetID);
				tilesetsTarget.push_back(imageName);
			}
		}

	}
}



//TODO
//tileset management
void EditorUIManager::TilesetWindow(const AssetManagerPtr& assetManager, const glm::vec2& mouseRect) {

	if (ImGui::Begin("Tileset", &loadTileset, ImGuiWindowFlags_HorizontalScrollbar)) {
		//resize on mouse scroll
		float scrollX = ImGui::GetScrollX();
		float scrollY = ImGui::GetScrollY();

		int imageWidth = tileWidth * 2;
		int imageHeight = tileHeight * 2;

		
		ImGui::Image(assetManager->ReturnEditorTexture(assetID).get(), ImVec2(imageWidth, imageHeight));

		int mousePosX = static_cast<int>(ImGui::GetMousePos().x - ImGui::GetWindowPos().x + scrollX);
		int mousePosY = static_cast<int>(ImGui::GetMousePos().y - ImGui::GetWindowPos().y - titleBar + scrollY);

		int tileCol = imageWidth / (mouseRect.x * 2);
		int tileRow = imageHeight / (mouseRect.y * 2);

		//render tileset textures
		for (int c = 0; c < tileCol; c++) {
			for (int r = 0; r < tileRow; r++) {
				auto drawList = ImGui::GetWindowDrawList();


				//grab desired 2d tile
				if ((mousePosX >= (imageWidth / tileCol) * c && mousePosX <= (imageWidth / tileCol) + ((imageWidth / tileCol) * c))
					&& (mousePosY >= (imageHeight / tileRow) * r && mousePosY <= (imageHeight / tileRow) + ((imageHeight / tileRow) * r))) {

					if (ImGui::IsItemHovered()){

						if (ImGui::IsMouseClicked(0)) {
							tileAttributes.srcRectX = c * mouseRect.x;
							tileAttributes.srcRectY = r * mouseRect.y;
						}
					}
				}
			}
		}
	}
	ImGui::End();
}

void EditorUIManager::TileAttributes(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse, bool tileWindow) {
	std::string tilesetName = "Tileset Attributes";

	if (!tileWindow) {
		return;
	}

	if (ImGui::Begin(tilesetName.c_str())) {

		if (tileWindow) {

			static std::string currentTileset = "";
			static std::string previousTileset = assetID;

			if (ImGui::BeginCombo("Tilesets", currentTileset.c_str())) {
				for (int tileset = 0; tileset < tilesets.size(); tileset++) {
					bool selected = (currentTileset == tilesets[tileset]);
					if (ImGui::Selectable(tilesets[tileset].c_str(), selected)) {
						currentTileset = tilesets[tileset];
					}
					if (selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

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

			if (CheckTransform()) {
				mouse->ApplyTransform(tileAttributes.scaleX, tileAttributes.scaleY);
				mouse->SetMouseTileRect(tileAttributes.mouseRectX, tileAttributes.mouseRectY);
			}

			if (tileWindow) {
				mouse->ApplySprite(assetID, tileWidth, tileHeight, tileAttributes.layer, tileAttributes.srcRectX, tileAttributes.srcRectY);
			}

			ImGui::End();

		}
	}
}

void EditorUIManager::TilesetLayers(const AssetManagerPtr& assetManager) {
	//layers interact
	if (ImGui::MenuItem("Layer")) {

	}
}



//TODO
//file management
void EditorUIManager::NewProject() {

}

void EditorUIManager::Open(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, sol::state& lua, int& tileSize) {
	std::string fileName = fileDialog->OpenFile();

	if (!fileName.empty()) {
		projectManagement->OpenProject(lua, fileName, renderer, canvas, assetManager, tilesets, tilesetsTarget, tileSize);
	}
}

void EditorUIManager::Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize) {
	if (fileName.empty()) {
		fileName = fileDialog->SaveFile();

		if (fileName.empty()) {
			return;
		}
	}
	
	projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvasWidth, canvasHeight, tileSize);
}

void EditorUIManager::OpenNewWindow() {
	if (!isNewFile) {
		return;
	}

	if (ImGui::Begin("New Canvas")) {
		ImGui::Text("Are you sure?");
		ImGui::Spacing();

		if (ImGui::Button("Yes")) {
			newCanvas = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("No")) {
			isNewFile = false;
		}
		ImGui::End();
	}

	if (newCanvas) {
		ResetLoadedFiles();
		isNewFile = false;
		newCanvas = false;
	}
}

void EditorUIManager::ResetLoadedFiles() {
	fileName = "";
	assetID = "";
	imageName = "";
	loadTileset = false;
	tilesets.clear();
	tilesetsTarget.clear();
	isReset = true;
}



//TODO
//shortcut management
void EditorUIManager::ApplyShortcuts() {

}


bool EditorUIManager::CheckTransform() {
	//changes from current attributes to previous attributes
	return tileAttributes.scaleX != tilePrevAttributes.scaleX ||
		tileAttributes.scaleY != tilePrevAttributes.scaleY ||
		tileAttributes.mouseRectX != tilePrevAttributes.mouseRectX ||
		tileAttributes.mouseRectY != tilePrevAttributes.mouseRectY;
}

bool EditorUIManager::CheckSprite() {
	return false;
}