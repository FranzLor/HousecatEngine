
#include <imgui/imgui.h>

#include <algorithm>

#include "EditorUIManager.h"

#include "../utilities/SDLUtility.h"
#include "../utilities/editmanager/EditManager.h"

#include "../ui/IconsFontAwesome6.h"
#include "EditorUIRendering.h"


EditorUIManager::EditorUIManager(std::shared_ptr<Mouse>& mouse)
//int tileWidth, tileHeight, scaleX, scaleY, layer, tileOffset, srcRectX, srcRectY
	: tileAttributes{ 32, 32, 1, 1, 0, {0, 0}, 0, 0 },
	tilePrevAttributes{ 32, 32, 1, 1, 0, {0, 0}, 0, 0 },
	tileWidth(32),
	tileHeight(32),
	textureWidth(0),
	textureHeight(0),
	loadTileset(false),
	isReset(false),
	isNewFile(false),
	newCanvas(false),
	tilesetLoaded(false),
	isShortcutPressed(false),
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
	//used for new project popup
	ImFont* robotoFontLarge = IO.Fonts->AddFontFromFileTTF("assets/fonts/roboto.regular.ttf", 30);


	//ImGui UI styling
	ImGuiStyle& style = ImGui::GetStyle();

	style.FrameRounding = 2.0f;
	style.FrameBorderSize = 2.0f;
	style.TabRounding = 0.0f;
	style.ScrollbarRounding = 2.0f;
	style.ScrollbarSize = 12.0f;
	style.TabRounding = 2.0f;
	style.GrabRounding = 2.0f;

	style.WindowMenuButtonPosition = ImGuiDir_Right;
	style.Alpha = 1.0f;
	style.FrameRounding = 3.0f;
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);

	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.576f, 0.612f, 0.639f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.576f, 0.612f, 0.639f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.576f, 0.612f, 0.639f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.576f, 0.612f, 0.639f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);

	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);

	style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);

	style.ItemSpacing.x = 10;
	style.ItemSpacing.y = 8;
	style.FramePadding.x = 5;
	style.FramePadding.y = 5;

	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);

	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

	style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

}

//TODO
//menu bar management
void EditorUIManager::ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, sol::state& lua, int& tileSize) {
	//MENU file interact
	if (ImGui::MenuItem(ICON_FA_FILE_CIRCLE_PLUS "   New Project", "CTRL+N")) {
		isNewFile = true;
	}
	if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN "   Open", "CTRL+O")) {
		Open(renderer, assetManager, canvas, lua, tileSize);
	}
	if (ImGui::MenuItem(ICON_FA_FLOPPY_DISK "   Save", "CTRL+S")) {
		Save(renderer, assetManager, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
	}
	if (ImGui::MenuItem(ICON_FA_FILE_PEN "   Save As", "CTRL+SHIFT+S")) {
		//TODO
		//file management
		std::string file = fileDialog->SaveFile();

		if (file == "") {
			return;
		}
		fileName = file;
		projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
	}

	if (ImGui::MenuItem(ICON_FA_FILE_EXPORT "   Export to Lua Table")) {
		std::string file = fileDialog->SaveFile();

		if (file == "") {
			// Set Lua file to the selected filename
			return;
		}
		luaFile = file;
		projectManagement->SaveAsLua(luaFile, tilesets, tilesetsTarget, tileSize);
	}

	if (ImGui::MenuItem(ICON_FA_FILE_CIRCLE_XMARK "   Exit", "ESC")) {
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

	if (ImGui::MenuItem(" " ICON_FA_BOX_OPEN "   Add Tileset")) {
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
	auto tilesetWindowFlags = ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysVerticalScrollbar;
	if (ImGui::Begin(ICON_FA_TABLE_COLUMNS "   Tileset", &loadTileset, tilesetWindowFlags)) {
		//resize on mouse scroll
		float scrollX = ImGui::GetScrollX();
		float scrollY = ImGui::GetScrollY();

		int imageWidth = textureWidth * 2;
		int imageHeight = textureHeight * 2;
		ImVec2 imageSize = ImVec2(textureWidth * 2, textureHeight * 2);

		//display the tileset texture with a border
		ImGui::Image(assetManager->ReturnEditorTexture(assetID).get(), imageSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(1, 0, 0, 1));

		int mousePosX = static_cast<int>(ImGui::GetMousePos().x - ImGui::GetWindowPos().x + scrollX);
		int mousePosY = static_cast<int>(ImGui::GetMousePos().y - ImGui::GetWindowPos().y - titleBar + scrollY);

		int tileCol = imageWidth / static_cast<int>(mouseRect.x * 2);
		int tileRow = imageHeight / static_cast<int>(mouseRect.y * 2);

		//render tileset
		for (int i = 0; i < tileCol; i++) {
			for (int j = 0; j < tileRow; j++) {
				auto drawList = ImGui::GetWindowDrawList();

				if ((mousePosX >= (imageWidth / tileCol) * i && mousePosX <= (imageWidth / tileCol) + ((imageWidth / tileCol) * i))
					&& (mousePosY >= (imageHeight / tileRow) * j && mousePosY <= (imageHeight / tileRow) + ((imageHeight / tileRow) * j))) {
					if (ImGui::IsItemHovered()) {

						if (ImGui::IsMouseClicked(0)) {
							tileAttributes.srcRectX = i * mouseRect.x;
							tileAttributes.srcRectY = j * mouseRect.y;
						}
					}
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

	if (ImGui::Begin(ICON_FA_HAMMER "   Tileset Tools", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
		ImGuiStyle& style = ImGui::GetStyle();
		//center window text
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

		float windowVisibleWidth = ImGui::GetContentRegionAvail().x;

		// Assuming each button + spacing occupies roughly 100 pixels, adjust based on your actual UI
		float totalButtonsWidth = 3 * 100.0f; // 3 buttons
		float startingPosX = (windowVisibleWidth - totalButtonsWidth) * 0.5f;
		startingPosX = startingPosX > 0 ? startingPosX : 0; // Ensure startingPosX is not negative

		// Adjust spacing for aesthetics if needed
		float originalItemSpacing = style.ItemSpacing.x;
		style.ItemSpacing.x = 22.0f;

		// Create initial spacing to center buttons
		ImGui::Dummy(ImVec2(startingPosX, 0));
		ImGui::SameLine();


		//toggle paint
		bool pushed = false;
		if (isPaintToolActive) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.24f, 0.52f, 0.88f, 1.0f));
			pushed = true;
		}
		//toggle state
		if (ImGui::Button("     " ICON_FA_PAINTBRUSH "     ")) {
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
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.24f, 0.52f, 0.88f, 1.0f));
			pushed = true;
		}
		if (ImGui::Button("     " ICON_FA_ERASER "     ")) {
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
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.24f, 0.52f, 0.88f, 1.0f));
			pushed = true;
		}
		if (ImGui::Button("     " ICON_FA_FILL_DRIP "     ")) {
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
	ImGuiStyle& style = ImGui::GetStyle();
	//center window text
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	std::string tilesetName = ICON_FA_SLIDERS "   Tileset Attributes";

	if (!tileWindow) {
		return;
	}

	if (ImGui::Begin(tilesetName.c_str(), nullptr, ImGuiWindowFlags_NoMove)) {

		if (tileWindow) {
			static std::string currentTileset = "";
			static std::string previousTileset = "";

			//currentTileset with the first tileset if it's not already set and if there are tilesets available
			if (currentTileset.empty() && !tilesets.empty()) {
				currentTileset = tilesets[0];
				assetID = currentTileset;
				SDL_QueryTexture(assetManager->ReturnEditorTexture(assetID).get(), NULL, NULL, &textureWidth, &textureHeight);
				previousTileset = currentTileset;
			}

			//changing tilesets 
			if (ImGui::BeginCombo("Tilesets", currentTileset.c_str())) {
				for (const auto& set : tilesets) {
					bool isSelected = (currentTileset == set);
					if (ImGui::Selectable(set.c_str(), isSelected)) {
						currentTileset = set;
						if (previousTileset != currentTileset) {
							//update texture for the new tileset added
							assetID = currentTileset;
							SDL_QueryTexture(assetManager->ReturnEditorTexture(assetID).get(), NULL, NULL, &textureWidth, &textureHeight);
							previousTileset = currentTileset;
						}
					}
					if (isSelected) {
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

			ImGui::Text("Mouse Scale");
			//clamping to prevent division by 0 at tileset window
			if (ImGui::InputInt("Tile X", &tileAttributes.mouseRectX, 8, 8)) {
				tileAttributes.mouseRectX = max(8, (tileAttributes.mouseRectX / 8) * 8);
			}
			if (ImGui::InputInt("Tile Y", &tileAttributes.mouseRectY, 8, 8)) {
				tileAttributes.mouseRectY = max(8, (tileAttributes.mouseRectY / 8) * 8);
			}

			ImGui::Text("Sprite Scale");
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


			if (tileWindow) {
				mouse->ApplySprite(assetID, tileWidth, tileHeight, tileAttributes.layer, tileAttributes.srcRectX, tileAttributes.srcRectY);
				mouse->ApplyTransform(tileAttributes.scaleX, tileAttributes.scaleY);
				mouse->SetMouseTileRect(tileAttributes.mouseRectX, tileAttributes.mouseRectY);
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
	fileName = fileDialog->OpenFile();

	if (fileName == "") {
		return;
	}
	projectManagement->OpenProject(lua, fileName, renderer, canvas, assetManager, tilesets, tilesetsTarget, tileSize);
}

void EditorUIManager::Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize) {
	if (fileName == "") {
		fileName = fileDialog->SaveFile();

		if (fileName == "") {
			return;
		}
		projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvasWidth, canvasHeight, tileSize);
	}
	else {
		projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvasWidth, canvasHeight, tileSize);
	}
}

void EditorUIManager::OpenNewWindow() {
	if (!isNewFile) {
		return;
	}

	//centering window
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	ImGui::SetNextWindowSize(ImVec2(330, 190));
	ImGuiWindowFlags newWindowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;

	if (ImGui::Begin("New Project", nullptr, newWindowFlags)) {
		//padding for top
		ImGui::Dummy(ImVec2(0.0f, 30.0f));
		
		ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
		//center text
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Create New Project?").x) * 0.5f);
		ImGui::Text("Create New Project?");
		ImGui::PopFont();

		ImGui::Spacing();

		//calc button pos
		float buttonWidth = 100;
		float buttonHeight = 0;
		float totalWidth = 2 * buttonWidth + ImGui::GetStyle().ItemSpacing.x;
		float buttonPosX = (ImGui::GetWindowSize().x - totalWidth) * 0.5f;

		ImGui::SetCursorPosX(buttonPosX);
		if (ImGui::Button("Yes", ImVec2(buttonWidth, buttonHeight))) {
			newCanvas = true;
		}

		ImGui::SameLine(0, 10);

		if (ImGui::Button("No", ImVec2(buttonWidth, buttonHeight))) {
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

	//tools
	static bool shortcutBPressed = false;
	static bool shortcutEPressed = false;
	static bool shortcutFPressed = false;

	bool isBPressed = keyState[SDL_SCANCODE_B];
	bool isEPressed = keyState[SDL_SCANCODE_E];
	bool isFPressed = keyState[SDL_SCANCODE_F];

	if (isBPressed && !shortcutBPressed) {
		isPaintToolActive = !isPaintToolActive;

		isEraserToolActive = false;
		isFillToolActive = false;
	}
	shortcutBPressed = isBPressed;

	if (isEPressed && !shortcutEPressed) {
		isEraserToolActive = !isEraserToolActive;

		isPaintToolActive = false;
		isFillToolActive = false;
	}
	shortcutEPressed = isEPressed;

	if (isFPressed && !shortcutFPressed) {
		isFillToolActive = !isFillToolActive;

		isPaintToolActive = false;
		isEraserToolActive = false;
	}
	shortcutFPressed = isFPressed;
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