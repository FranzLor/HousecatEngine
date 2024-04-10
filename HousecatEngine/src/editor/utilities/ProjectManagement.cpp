#include <fstream>
#include <filesystem>
#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>
#include <iomanip>

#include "ProjectManagement.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

#include "../../components/TransformComponent.h"
#include "../../components/SpriteComponent.h"

#include "../../logger/Logger.h"

ProjectManagement::ProjectManagement() {}
ProjectManagement::~ProjectManagement() {}

void ProjectManagement::OpenProject(sol::state& lua, const std::string& fileName, EditorRenderer& renderer, std::shared_ptr<EditorCanvas>& canvas,
	const AssetManagerPtr& assetManager, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath,
	int& tileSize) {

	std::filesystem::path filePath(fileName);
	//map check
	if (filePath.extension() != ".lua") {
		return;
	}

	sol::load_result script = lua.load_file(fileName);

	if (!script.valid()) {
		sol::error error = script;
		std::string errorMessage = error.what();
		Logger::Error("Error Loading Lua File: " + errorMessage);
		return;
	}

	lua.script_file(fileName);

	sol::table project = lua["project"];
	
	int numAssets = 0;
	int numMaps = 0;

	std::string mapFile = "";

	while (true) {
		sol::optional<sol::table> projectAssets = project["assets"][numAssets];
		if (projectAssets == sol::nullopt) {
			break;
		}

		sol::table assets = project["assets"][numAssets];
		std::string assetsID = assets["asset_id"];
		std::string filePath = assets["file_path"];

		assetID.push_back(assetsID);
		assetFilePath.push_back(filePath);

		assetManager->AddEditorTexture(renderer, std::move(assetsID), std::move(filePath));
		numAssets++;
	}

	while (true) {
		sol::optional<sol::table> projectMaps = project["maps"][numMaps];
		if (projectMaps == sol::nullopt) {
			break;
		}

		sol::table maps = project["maps"][numMaps];
		mapFile = maps["file_path"];
		numMaps++;
	}

	sol::optional<sol::table> luaCanvas = project["canvas"];
	if (luaCanvas != sol::nullopt) {
		int canvasWidth = project["canvas"]["canvas_width"];
		int canvasHeight = project["canvas"]["canvas_height"];
		tileSize = project["canvas"]["tile_size"];

		canvas->SetCanvasWidth(std::move(canvasWidth));
		canvas->SetCanvasHeight(std::move(canvasHeight));
	}
	LoadMap(assetManager, mapFile);
}

void ProjectManagement::SaveProject(const std::string& fileName, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath,
	const int& canvasWidth, const int& canvasHeight, const int& tileSize) {

	std::fstream projectFile;
	projectFile.open(fileName, std::ios::out | std::ios::trunc);

	if (!projectFile.is_open()) {
		//TODO
		//err handle
		return;
	}
	//Logger::Log("Saving project started: " + fileName);

	LuaExporter luaExporter;

	luaExporter.StartDocument();

	luaExporter.SeparationLine(projectFile);
	luaExporter.CommentLine("", projectFile);
	luaExporter.SeparationLine(projectFile);

	int numAssets = 0;

	luaExporter.DeclareTable("project", projectFile);
	luaExporter.DeclareTable("assets", projectFile);

	for (const auto& asset : assetID) {
		luaExporter.WriteStartTable(numAssets, false, projectFile);
		luaExporter.WriteKeyAndQuotedValue("asset_id", asset, projectFile, true);
		luaExporter.WriteKeyAndQuotedValue("file_path", assetFilePath[numAssets], projectFile, true);
		luaExporter.EndTable(false, projectFile);
		numAssets++;
	}
	
	luaExporter.EndTable(false, projectFile);

	//map
	std::filesystem::path filePath(fileName);
	filePath.replace_extension(".map");

	luaExporter.DeclareTable("maps", projectFile);
	luaExporter.WriteStartTable(0, false, projectFile);
	luaExporter.WriteKeyAndQuotedValue("file_path", filePath.string(), projectFile);
	luaExporter.EndTableSeparation(false, projectFile);
	luaExporter.EndTable(false, projectFile);

	luaExporter.DeclareTable("canvas", projectFile);
	luaExporter.WriteKeyAndUnquotedValue("canvas_width", canvasWidth, projectFile, false, false);
	luaExporter.WriteKeyAndUnquotedValue("canvas_height", canvasHeight, projectFile, false, false);
	luaExporter.WriteKeyAndUnquotedValue("tile_size", tileSize, projectFile, false, false);

	luaExporter.EndTable(false, projectFile);
	luaExporter.EndTable(false, projectFile);

	luaExporter.EndDocument(projectFile);

	projectFile.close();

	std::fstream mapFile;
	mapFile.open(filePath, std::ios::out);

	if (!mapFile.is_open()) {
		//TODO
		//err handling
		return;
	}

	SaveMap(filePath);
	//Logger::Log("Saving project completed: " + fileName);

}

void ProjectManagement::SaveAsLua(const std::string& fileName, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath, const int& tileSize) {
	std::fstream project;

	project.open(fileName, std::abs(std::ios::out | std::ios::trunc));

	if (!project.is_open()) {
		return;
	}
	LuaExporter luaExport;

	luaExport.StartDocument();

	luaExport.SeparationLine(project);
	luaExport.CommentLine("", project);
	luaExport.SeparationLine(project);

	luaExport.WriteWords("return {", project, true);
	luaExport.WriteKeyAndUnquotedValue("id", "id", project, false, false);
	luaExport.WriteKeyAndUnquotedValue("name", "", project, false, false);
	luaExport.WriteKeyAndUnquotedValue("tileWidth", tileSize, project, false, false);
	luaExport.WriteKeyAndUnquotedValue("tileHeight", tileSize, project, false, false);

	luaExport.DeclareTable("tiles", project);
	if (Housecat::GetInstance().IsThereGroup("tiles")) {
		int i = 1;

		for (const auto& tile : Housecat::GetInstance().GetGroup("tiles")) {
			luaExport.WriteStartTable(i, false, project);
			luaExport.DeclareTable("components", project);

			if (tile.HasComponent<TransformComponent>()) {
				const auto& transform = tile.GetComponent<TransformComponent>();

				luaExport.DeclareTable("transform", project);
				luaExport.DeclareTable("position", project);
				luaExport.WriteKeyAndValue("x", transform.position.x, false, project);
				luaExport.WriteKeyAndValue("y", transform.position.x, true, project);

				luaExport.EndTable(true, project);

				luaExport.DeclareTable("scale", project);
				luaExport.WriteKeyAndValue("x", transform.scale.x, false, project);
				luaExport.WriteKeyAndValue("y", transform.scale.y, true, project);

				luaExport.EndTable(true, project);

				luaExport.WriteKeyAndUnquotedValue("rotation", transform.rotation, project, false, false);
				luaExport.EndTable(false, project);
			}

			if (tile.HasComponent<SpriteComponent>()) {
				const auto& sprite = tile.GetComponent<SpriteComponent>();

				std::string fixed = "false";

				if (sprite.isFixed) {
					fixed = "true";
				}

				luaExport.DeclareTable("sprite", project);

				luaExport.WriteKeyAndQuotedValue("asset_id", sprite.assetID, project);
				luaExport.WriteKeyAndValue("width", sprite.width, false, project);
				luaExport.WriteKeyAndValue("height", sprite.height, false, project);
				luaExport.WriteKeyAndValue("z_index", sprite.zIndex, false, project);
				luaExport.WriteKeyAndValue("is_fixed", fixed, true, project);

				luaExport.DeclareTable("src_rect", project);
				luaExport.WriteKeyAndValue("x", sprite.srcRect.x, false, project);
				luaExport.WriteKeyAndValue("y", sprite.srcRect.y, true, project);
				luaExport.EndTable(true, project);
				luaExport.EndTable(false, project);
			}

			luaExport.EndTable(false, project);
			luaExport.EndTable(false, project);
			i++;
		}
	}

	luaExport.EndTable(false, project);
	luaExport.EndTable(false, project);
	luaExport.EndDocument(project);
	luaExport.WriteWords("end", project);
	project.close();
}


void ProjectManagement::LoadMap(const AssetManagerPtr& assetManager, const std::string& fileName) {
	std::ifstream mapFile(fileName);
	if (!mapFile.is_open()) {
		Logger::Error("Could Not Open Map File: " + fileName);
		return;
	}

	std::string line;
	while (std::getline(mapFile, line)) {
		std::istringstream iss(line);
		std::string group, assetID;
		int tileWidth, tileHeight, srcRectX, srcRectY, zIndex;
		double posX, posY, scaleX, scaleY;
		//parses with assetID with quotes from saving
		iss >> group >> std::quoted(assetID) >> tileWidth >> tileHeight >> srcRectX >> srcRectY
			>> zIndex >> posX >> posY >> scaleX >> scaleY;

		if (iss.fail()) {
			Logger::Error("Failed to parse line in map file: " + line);
			continue;
		}

		glm::vec2 position(posX, posY);
		glm::vec2 scale(scaleX, scaleY);

		Entity tile = Housecat::GetInstance().CreateEntity();
		tile.Group(group);
		tile.AddComponent<TransformComponent>(position, scale, 0.0);
		tile.AddComponent<SpriteComponent>(assetID, tileWidth, tileHeight, zIndex, false, srcRectX, srcRectY);
	}

	//Logger::Log("Map data loaded successfully.");
	mapFile.close();
}


void ProjectManagement::SaveMap(std::filesystem::path fileName) {
	if (!Housecat::GetInstance().IsThereGroup("tiles")) {
		Logger::Error("Housecat Could Not Find Group: tiles");
		return;
	}

	std::ofstream mapFile;
	mapFile.open(fileName);

	if (!mapFile.is_open()) {
		Logger::Error("Could Not Open Map File: " + fileName.string());
		return;
	}
	//Logger::Log("Saving assets...");

	auto tiles = Housecat::GetInstance().GetGroup("tiles");

	for (const auto& tile : tiles) {
		std::string group = "tiles";
		const auto& transform = tile.GetComponent<TransformComponent>();
		const auto& sprite = tile.GetComponent<SpriteComponent>();

		mapFile << group << " \"" << sprite.assetID << "\" " << sprite.width << " " << sprite.height << " " << sprite.srcRect.x << " " << sprite.srcRect.y << " " << sprite.zIndex << " "
			<< transform.position.x << " " << transform.position.y << " " << transform.scale.x << " " << transform.scale.y << std::endl;
	}

	//Logger::Log("Assets saved successfully. Count: " + std::to_string(tiles.size()));

	mapFile.close();
	//Logger::Log("Map data saved successfully");
}
