#include <imgui/imgui.h>


#include "../utilities/SDLUtility.h"

#include "EditorUIManager.h"

#include "EditorCanvas.h"
#include "EditorUIRendering.h"

#include "../src/logger/Logger.h"
#include <imgui/imgui_impl_sdlrenderer2.h>
#include <imgui/imgui_impl_sdl2.h>
#include "../utilities/EditTile.h"
#include "../utilities/RemoveTile.h"
#include "../utilities/EditCanvasSize.h"


EditorUIRendering::EditorUIRendering()
	: canvasWidth(960),
	canvasHeight(640),
	canvasPreviousWidth(960),
	canvasPreviousHeight(640),
	tileSize(32),
	tilePrevSize(32),
	createTiles(false),
	removedTile(false),
	gridX(0),
	gridY(0),
	gridSnap(true),
	gridShow(true) {

	canvas = std::make_shared<EditorCanvas>(canvasWidth, canvasHeight);
	mouse = std::make_shared<Mouse>();
	editorUIManager = std::make_shared<EditorUIManager>(mouse);
	editManager = std::make_unique<EditManager>();

	//call ImGui setup
	editorUIManager->InitImGui();
	editorUIManager->Setup();

	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);

	Logger::Lifecycle("ImGuiRendering Constructor Called!");
}

EditorUIRendering::~EditorUIRendering() {
	Logger::Lifecycle("ImGuiRendering Destructor Called!");
}


void EditorUIRendering::Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile,
	SDL_Event& event, const float& zoom, const float& dT) {

	//start frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			editorUIManager->ShowFileMenu(renderer, assetManager, canvas, lua, tileSize);
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
			ImGui::Checkbox("Show Grid", &gridShow);

			ImGui::Checkbox("Snap to Grid", &gridSnap);

			ImGui::Spacing();
			ImGui::Spacing();

			if (ImGui::MenuItem("Zoom In", "CTRL + +")) {

			}
			if (ImGui::MenuItem("Zoom Out", "CTRL + -")) {

			}
			if (ImGui::MenuItem("Fit to View")) {

			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Project")) {
			editorUIManager->ShowProjectMenu(renderer, assetManager);

			ImGui::Spacing;
			ImGui::Spacing;
			ImGui::Spacing;

			if (ImGui::MenuItem("Tilset Window")) {
				createTiles = !createTiles;
			}

			ImGui::Spacing;
			ImGui::Spacing;
			ImGui::Spacing;
			ImGui::Spacing;

			if (ImGui::InputInt("Tile Size", &tileSize, 8, 8)) {
				if (tileSize <= 8) {
					tileSize = 8;
				}
			}

			if (ImGui::InputInt("Canvas Width", &canvasWidth, tileSize, tileSize)) {

				if (canvasPreviousWidth != canvasWidth) {
					canvas->SetCanvasWidth(canvasWidth);
					editManager->Execute(std::make_shared<EditCanvasSize>(canvas, canvasPreviousWidth, canvasPreviousHeight));
					canvasPreviousWidth = canvasWidth;
				}

				if (canvasWidth <= 960) {
					canvasWidth = 960;
					canvas->SetCanvasWidth(canvasWidth);
					canvasPreviousWidth = canvasWidth;
				}

			}

			if (ImGui::InputInt("Canvas Height", &canvasHeight, tileSize, tileSize)) {

				if (canvasPreviousHeight != canvasHeight) {
					canvas->SetCanvasHeight(canvasHeight);
					editManager->Execute(std::make_shared<EditCanvasSize>(canvas, canvasPreviousWidth, canvasPreviousHeight));
					canvasPreviousHeight = canvasHeight;
				}

				if (canvasHeight <= 640) {
					canvasHeight = 640;
					canvas->SetCanvasHeight(canvasHeight);
					canvasPreviousHeight = canvasHeight;
				}

			}
			ImGui::EndMenu();
		}

		ShowMouseLocation(mouseTile, camera);

		ImGui::EndMainMenuBar();
	}

	editorUIManager->OpenNewWindow();

	if (editorUIManager->FileReset()) {
		CreateNewCanvas();
		editorUIManager->SetFileReset(false);
	}

	if (createTiles) {
		editorUIManager->TilesetWindow(assetManager, mouse->GetMouseRect());
		editorUIManager->TileAttributes(assetManager, mouse, true);
		editorUIManager->TilesetTools(assetManager, mouse, true);

		if (!MouseOutOfBounds()) {
			if (editorUIManager->IsPaintToolActive()) {
				
				mouse->CreateTile(renderer, assetManager, camera, mouseTile, event);
			}
			else if (editorUIManager->IsEraserToolActive()) {
				mouse->RemoveTile(renderer, assetManager, camera, mouseTile, event);
			}
			//TODO
			//fill
			else if (editorUIManager->IsFillToolActive()) {
				//mouse->MultiTile(mouse->GetMousePosition());
			}
			

		}

		if (mouse->TileAdded()) {
			editManager->Execute(std::make_shared<EditAddTile>(mouse));
			mouse->SetTileAdded(false);
			removedTile = false;
		}

		if (mouse->TileRemoved()) {
			editManager->Execute(std::make_shared<EditRemoveTile>(mouse));
			mouse->SetRemovedTile(false);
			removedTile = true;
		}
	}

	//update mouse
	mouse->MousePanCamera(renderer, camera, assetManager, dT);
	mouse->UpdateMousePosition(camera);
	mouse->UpdateZoom(zoom);
	mouse->UpdateGridSize(tileSize);
	mouse->SetGridSnap(gridSnap);

	//render imgui
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());


	ImGuiIO& IO = ImGui::GetIO();
	if (IO.WantCaptureMouse) {
		mouse->MouseOverWindow(true);
	}
	else {
		mouse->MouseOverWindow(false);
	}

	UpdateCanvas();
}

void EditorUIRendering::RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom) {
	//Logger::Debug("Rendering Grid!");

	//calc full tiles in canvas
	int xTiles = canvas->GetCanvasWidth() / tileSize;
	int yTiles = canvas->GetCanvasHeight() / tileSize;


	if (gridShow) {
		
		SDL_SetRenderDrawColor(renderer.get(), 140, 140, 140, SDL_ALPHA_OPAQUE);

		//vertical
		for (int i = 0; i <= xTiles; i++) {
			int x = std::floor(i * tileSize * zoom) - camera.x;
			SDL_RenderDrawLine(renderer.get(), x, 0 - camera.y, x, (yTiles * tileSize * zoom) - camera.y);
		}

		//horizontal
		for (int j = 0; j <= yTiles; j++) {
			int y = std::floor(j * tileSize * zoom) - camera.y;
			SDL_RenderDrawLine(renderer.get(), 0 - camera.x, y, (xTiles * tileSize * zoom) - camera.x, y);
		}
	}

	//boundary
	SDL_SetRenderDrawColor(renderer.get(), 37, 39, 41, SDL_ALPHA_OPAQUE);
	SDL_Rect boundaryRect = { 0 - camera.x, 0 - camera.y, xTiles * tileSize * zoom, yTiles * tileSize * zoom };
	SDL_RenderDrawRect(renderer.get(), &boundaryRect);
}


void EditorUIRendering::CreateNewCanvas() {
	//resetting canvas
	createTiles = false;
	gridSnap = true;

	tileSize = 32;
	canvasWidth = 960;
	canvasHeight = 640;

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
	if (!mouse->MouseOutOfBounds() && (createTiles)) {
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
