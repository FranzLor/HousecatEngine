
#include <imgui/imgui.h>

#include <algorithm>

#include "EditorUIManager.h"

#include "../utilities/SDLUtility.h"
#include "../utilities/editmanager/EditManager.h"

#include "../ui/IconsFontAwesome6.h"


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
	tilesetLoaded(false),
	isPaintToolActive(false),
	isEraserToolActive(false),
	isFillToolActive(false),
	Undo(false),
	Redo(false),
	isExit(false),
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


	//ImGui UI styling
	ImGuiStyle& style = ImGui::GetStyle();

	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 2.0f;
	style.TabRounding = 0.0f;
	style.ScrollbarRounding = 1.0f;
	style.ScrollbarSize = 12.0f;

	style.WindowMenuButtonPosition = ImGuiDir_Right;
}

void EditorUIManager::Setup() {
	//TODO
	//ImGui
}

//TODO
//menu bar management
void EditorUIManager::ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, sol::state& lua, int& tileSize) {
	//MENU file interact
	if (ImGui::MenuItem(ICON_FA_FILE_CIRCLE_PLUS "New Project", "CTRL+N")) {
		isNewFile = true;
	}
	if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN "Open Project", "CTRL+O")) {
		Open(renderer, assetManager, canvas, lua, tileSize);
	}
	if (ImGui::MenuItem(ICON_FA_FLOPPY_DISK "Save", "CTRL+S")) {
		Save(renderer, assetManager, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
	}
	if (ImGui::MenuItem(ICON_FA_FILE_PEN "Save As", "CTRL+SHIFT+S")) {
		//TODO
		//file management
		std::string file;
		file = fileDialog->SaveFile();

		if (!file.empty()) {
			fileName = file;
			projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
		}
	}

	if (ImGui::MenuItem(ICON_FA_FILE_EXPORT "Export to Lua Table")) {
		std::string luaFileName;
		luaFileName = fileDialog->SaveFile();

		if (!luaFileName.empty()) {
			// Set Lua file to the selected filename
			luaFile = luaFileName;
			projectManagement->SaveAsLua(luaFile, tilesets, tilesetsTarget, tileSize);
		}
	}

	if (ImGui::MenuItem(ICON_FA_FILE_CIRCLE_XMARK "Exit", "ESC")) {
		isExit = true;
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

	if (ImGui::MenuItem(ICON_FA_BOX_OPEN "Add Tileset")) {
		FileDialogue fileDialog;
		imageName = fileDialog.OpenTextureFile();

		if (imageName.empty()) {
			return;
		}
		
		std::filesystem::path path(imageName);
		assetID = path.stem().string();

		for (const auto& assets : tilesets) {
			if (assets == assetID) {
				return;
			}
		}

		assetManager->AddEditorTexture(renderer, assetID, imageName);

		if (SDL_QueryTexture(assetManager->ReturnEditorTexture(assetID).get(), NULL, NULL, &textureWidth, &textureHeight) != 0) {
			const char* error = SDL_GetError();
			loadTileset = false;
		}
		else {
			loadTileset = true;
			tilesets.push_back(assetID);
			tilesetsTarget.push_back(imageName);
			tilesetLoaded = true;
		}

	}
}



//TODO
//tileset management
void EditorUIManager::TilesetWindow(const AssetManagerPtr& assetManager, const glm::vec2& mouseRect) {

	if (ImGui::Begin(ICON_FA_TABLE_COLUMNS "Tileset", &loadTileset, ImGuiWindowFlags_HorizontalScrollbar)) {
		//resize on mouse scroll
		float scrollX = ImGui::GetScrollX();
		float scrollY = ImGui::GetScrollY();

		int imageWidth = textureWidth * 2;
		int imageHeight = textureHeight * 2;

		
		ImGui::Image(assetManager->ReturnEditorTexture(assetID).get(), ImVec2(imageWidth, imageHeight));

		int mousePosX = static_cast<int>(ImGui::GetMousePos().x - ImGui::GetWindowPos().x + scrollX);
		int mousePosY = static_cast<int>(ImGui::GetMousePos().y - ImGui::GetWindowPos().y - titleBar + scrollY);

		int tileCol = imageWidth / static_cast<int>(mouseRect.x * 2);
		int tileRow = imageHeight / static_cast<int>(mouseRect.y * 2);

		//imgui render grid
		auto drawList = ImGui::GetWindowDrawList();
		ImVec2 winPos = ImGui::GetWindowPos();

		//render grid
		for (int c = 1; c < tileCol; c++) {
			drawList->AddLine(
				ImVec2(winPos.x + c * mouseRect.x * 2 - scrollX, winPos.y),
				ImVec2(winPos.x + c * mouseRect.x * 2 - scrollX, winPos.y + imageHeight),
				IM_COL32(125, 125, 125, 100));
		}
		for (int r = 1; r < tileRow; r++) {
			drawList->AddLine(
				ImVec2(winPos.x, winPos.y + r * mouseRect.y * 2 - scrollY),
				ImVec2(winPos.x + imageWidth, winPos.y + r * mouseRect.y * 2 - scrollY),
				IM_COL32(125, 125, 125, 100));
		}
		//selection
		if ((mousePosX >= 0 && mousePosX <= imageWidth) && (mousePosY >= 0 && mousePosY <= imageHeight)) {
			if (ImGui::IsMouseHoveringRect(winPos, ImVec2(winPos.x + imageWidth, winPos.y + imageHeight))) {
				if (ImGui::IsMouseClicked(0)) {
					int selectedCol = mousePosX / (mouseRect.x * 2);
					int selectedRow = mousePosY / (mouseRect.y * 2);
					tileAttributes.srcRectX = selectedCol * static_cast<int>(mouseRect.x);
					tileAttributes.srcRectY = selectedRow * static_cast<int>(mouseRect.y);
				}
			}
		}
	}
	ImGui::End();
}

void EditorUIManager::TilesetTools(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse, bool tileWindow) {
	if (!tileWindow) {
		return;
	}

	if (ImGui::Begin(ICON_FA_HAMMER "Tileset Tools")) {
		ImGuiStyle& style = ImGui::GetStyle();
		float originalItemSpacing = style.ItemSpacing.x;
		style.ItemSpacing.x = 15.0f;

		//toggle paint
		bool pushed = false;
		if (isPaintToolActive) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.6f, 0.4f, 1.0f));
			pushed = true;
		}
		//toggle state
		if (ImGui::Button(ICON_FA_PAINTBRUSH "Paint")) {
			isPaintToolActive = !isPaintToolActive;
			if (isPaintToolActive) {
				isEraserToolActive = false;
				isFillToolActive = false;
			}
		}
		//reset
		if (pushed) {
			ImGui::PopStyleColor(1);
			pushed = false;
		}
		ImGui::SameLine();

		//toggle eraser
		if (isEraserToolActive) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.6f, 0.4f, 1.0f));
			pushed = true;
		}
		if (ImGui::Button(ICON_FA_ERASER "Eraser")) {
			isEraserToolActive = !isEraserToolActive;
			if (isEraserToolActive) {
				isPaintToolActive = false;
				isFillToolActive = false;
			}
		}
		if (pushed) {
			ImGui::PopStyleColor(1);
			pushed = false;
		}
		ImGui::SameLine();

		//toggle fill
		if (isFillToolActive) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.6f, 0.4f, 1.0f));
			pushed = true;
		}
		if (ImGui::Button(ICON_FA_FILL_DRIP "Fill")) {
			isFillToolActive = !isFillToolActive;
			if (isFillToolActive) {
				isPaintToolActive = false;
				isEraserToolActive = false;
			}
		}
		if (pushed) {
			ImGui::PopStyleColor(1);
		}

		//restore original spacing
		style.ItemSpacing.x = originalItemSpacing;
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

			//changing tilesets 
			if (ImGui::BeginCombo("Tilesets", currentTileset.c_str())) {
				for (int set = 0; set < tilesets.size(); set++) {
					bool selected = (currentTileset == tilesets[set]);
					if (ImGui::Selectable(tilesets[set].c_str(), selected)) {
						currentTileset = tilesets[set];
					}
					if (selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			if (currentTileset != "") {
				if (previousTileset != currentTileset) {
					assetID = currentTileset;
					SDL_QueryTexture(assetManager->ReturnEditorTexture(assetID).get(), NULL, NULL, &textureWidth, &textureHeight);
					previousTileset = currentTileset;
				}
				if (currentTileset != assetID) {
					currentTileset = assetID;
				}
			}


			ImGui::Text("Scaling");
			ImGui::SliderInt("Scale X", &tileAttributes.scaleX, 1, 10);
			ImGui::SliderInt("Scale Y", &tileAttributes.scaleY, 1, 10);

			//REMIND
			if (ImGui::InputInt("Layer", &tileAttributes.layer, 1, 50)) {
				if (tileAttributes.layer <= 0) {
					tileAttributes.layer = 0;
				}
				if (tileAttributes.layer >= 50) {
					tileAttributes.layer = 50;
				}
			}

			ImGui::Text("Sprite");
			//clamping to prevent division by 0 at tileset window
			if (ImGui::InputInt("Tile X", &tileAttributes.mouseRectX, 8, 8)) {
				tileAttributes.mouseRectX = max(8, (tileAttributes.mouseRectX / 8) * 8);
			}
			if (ImGui::InputInt("Tile Y", &tileAttributes.mouseRectY, 8, 8)) {
				tileAttributes.mouseRectY = max(8, (tileAttributes.mouseRectY / 8) * 8);
			}

			if (tileWindow) {
				mouse->ApplySprite(assetID, tileWidth, tileHeight, tileAttributes.layer, tileAttributes.srcRectX, tileAttributes.srcRectY);
			}

			if (CheckTransform()) {
				mouse->ApplyTransform(tileAttributes.scaleX, tileAttributes.scaleY);
				mouse->SetMouseTileRect(tileAttributes.mouseRectX, tileAttributes.mouseRectY);
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
void EditorUIManager::Shortcuts(EditorRenderer& renderer, const AssetManagerPtr& assetManager,
	std::shared_ptr<EditorCanvas>& canvas, const std::unique_ptr<EditManager>& editManager, int& tileSize, sol::state& lua) {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	//save shortcut
	if (keyState[SDL_SCANCODE_LCTRL] && keyState[SDL_SCANCODE_S]) {
		Save(renderer, assetManager, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
	}

	//new shortcut
	if (keyState[SDL_SCANCODE_LCTRL] && keyState[SDL_SCANCODE_N]) {
		isNewFile = true;
	}

	//undo shortcut
	if ((keyState[SDL_SCANCODE_LCTRL] && keyState[SDL_SCANCODE_Z])
		&& (!keyState[SDL_SCANCODE_LSHIFT] && !Undo)) {
		editManager->Undo();
		Undo = true;
	}
	else if (!keyState[SDL_SCANCODE_Z] && Undo) {
		Undo = false;
	}

	//redo shortcut
	if ((keyState[SDL_SCANCODE_LCTRL] && (keyState[SDL_SCANCODE_Z])
		&& (keyState[SDL_SCANCODE_LSHIFT])) && !Redo) {
		editManager->Redo();
		Redo = true;
	}
	else if (!keyState[SDL_SCANCODE_Z] && Redo) {
		Redo = false;
	}
}


bool EditorUIManager::CheckTransform() {
	//changes from current attributes to previous attributes
	bool statusChanged = false;

	if (tileAttributes.scaleX != tilePrevAttributes.scaleX)
	{
		tilePrevAttributes.scaleX = tileAttributes.scaleX;
		statusChanged = true;
	}

	if (tileAttributes.scaleY != tilePrevAttributes.scaleY)
	{
		tilePrevAttributes.scaleY = tileAttributes.scaleY;
		statusChanged = true;
	}

	if (tileAttributes.mouseRectX != tilePrevAttributes.mouseRectX)
	{
		tilePrevAttributes.mouseRectX = tileAttributes.mouseRectX;
		tileWidth = tileAttributes.mouseRectX;
		statusChanged = true;
	}

	if (tileAttributes.mouseRectY != tilePrevAttributes.mouseRectY)
	{
		tilePrevAttributes.mouseRectY = tileAttributes.mouseRectY;
		tileHeight = tileAttributes.mouseRectY;
		statusChanged = true;
	}

	return statusChanged;
}

//bool EditorUIManager::CheckSprite() {
//	return false;
//}