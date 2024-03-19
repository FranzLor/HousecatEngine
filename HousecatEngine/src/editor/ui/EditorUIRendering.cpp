#include <imgui/imgui.h>


#include "../utilities/SDLUtility.h"

#include "EditorUIManager.h"

#include "EditorCanvas.h"
#include "EditorUIRendering.h"

#include "../src/logger/Logger.h"
#include <imgui/imgui_impl_sdlrenderer2.h>
#include <imgui/imgui_impl_sdl2.h>
#include "../utilities/AddTile.h"
#include "../utilities/RemoveTile.h"
#include "../utilities/EditCanvasSize.h"


EditorUIRendering::EditorUIRendering()
	: canvasWidth(960),
	canvasHeight(640),
	canvasPreviousWidth(canvasWidth),
	canvasPreviousHeight(canvasHeight),
	tileSize(32),
	tilePrevSize(tileSize),
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

	canvasPreviousWidth = 960;
	canvasPreviousHeight = 640;

	//sol lua libraries here
	//TODO

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

			if (ImGui::Checkbox("New Tileset", &createTiles)) {
				createTiles = true;
			}

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
		editorUIManager->TilesetWindow(assetManager, mouse->GetMousePosition());
		editorUIManager->TileAttributes(assetManager, mouse, true);

		if (!MouseOutOfBounds()) {
			mouse->CreateTile(renderer, assetManager, camera, mouseTile, event);
		}

		if (mouse->TileAdded()) {
			editManager->Execute(std::make_shared<AddTile>(mouse));
			mouse->SetTileAdded(false);
			removedTile = false;
		}

		if (mouse->TileRemoved()) {
			editManager->Execute(std::make_shared<RemoveTile>(mouse));
			mouse->SetRemovedTile(false);
			removedTile = true;
		}
	}

	//update mouse
	mouse->UpdateMousePosition(camera);
	mouse->MousePanCamera(renderer, camera, assetManager, dT);
	mouse->UpdateZoom(zoom);
	mouse->UpdateGridSize(tileSize);
	mouse->SetGridSnap(gridSnap);

	ImGuiIO& IO = ImGui::GetIO();
	if (IO.WantCaptureMouse) {
		mouse->MouseOverWindow(true);
	}
	else {
		mouse->MouseOverWindow(false);
	}

	UpdateCanvas();

	//render imgui
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void EditorUIRendering::RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom) {

	//if (!gridShow) {
	//	return;
	//}

	//auto xTiles = (canvas->GetCanvasWidth() / tileSize);
	//auto yTiles = (canvas->GetCanvasHeight() / tileSize);

	//for (int i = 0; i < yTiles; i++)
	//{
	//	for (int j = 0; j < xTiles; j++)
	//	{
	//		// Create a checkerboard
	//		if ((j - i) % 2 == 0 && (i - j) % 2 == 0)
	//			SDL_SetRenderDrawColor(renderer.get(), 125, 125, 125, 70);
	//		else
	//			SDL_SetRenderDrawColor(renderer.get(), 200, 200, 200, 70);

	//		SDL_Rect newRect = { (std::floor(j * tileSize * zoom)) - camera.x, (std::floor(i * tileSize * zoom)) - camera.y, std::ceil(tileSize * zoom), std::ceil(tileSize * zoom) };

	//		SDL_RenderFillRect(renderer.get(), &newRect);
	//	}
	//}

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

	createTiles = false;
	gridSnap = true;

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
