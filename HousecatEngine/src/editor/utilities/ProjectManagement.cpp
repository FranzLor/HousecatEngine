#include <fstream>
#include <filesystem>
#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>

#include "ProjectManagement.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

#include "../../components/TransformComponent.h"
#include "../../components/SpriteComponent.h"

ProjectManagement::ProjectManagement() {}
ProjectManagement::~ProjectManagement() {}

void ProjectManagement::OpenProject(const std::string& fileName, EditorRenderer& renderer, std::shared_ptr<EditorCanvas>& canvas,
	const AssetManagerPtr& assetManager, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath,
	int& tileSize) {

	std::filesystem::path filePath = fileName;
	//map check
	if (filePath.extension() != ".map") {
		return;
	}

	//TODO map
	mapManagement->LoadMap(assetManager, fileName);

}

void ProjectManagement::SaveProject(const std::string& fileName, const std::vector<std::string>& assetID, const std::vector<std::string>& assetFilePath,
	const int& canvasWidth, const int& canvasHeight, const int& tileSize) {

	std::fstream projectFile;
	projectFile.open(fileName, std::ios::out | std::ios::trunc);

	if (!projectFile.is_open()) {
		//TODO
		//err handle
		return;
	}

	//map
	std::filesystem::path filePath(fileName);
	filePath.replace_extension(".map");

	//TODO
	//make method
	//write

	projectFile.close();

	std::fstream mapFile;
	mapFile.open(filePath, std::ios::out);

	if (!mapFile.is_open()) {
		//TODO
		//err handling
		return;
	}

	mapManagement->SaveMap(filePath);

}

void ProjectManagement::SaveAsLua(const std::string& fileName, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath, const int& tileSize) {
	std::fstream project;

	project.open(fileName, std::abs(std::ios::out | std::ios::trunc));

	if (project.is_open()) {
		LuaExporter luaExport;

		luaExport.StartDocument();

		luaExport.SeparationLine(project);
		luaExport.CommentLine("", project);
		luaExport.SeparationLine(project);

		luaExport.WriteWords("return {", project, true);
		luaExport.WriteKeyAndUnquotedValue("id", "id", project, false, false);
		luaExport.WriteKeyAndUnquotedValue("value", "", project, false, false);
		luaExport.WriteKeyAndUnquotedValue("tileWidth", tileSize, project, false, false);
		luaExport.WriteKeyAndUnquotedValue("tileHeight", tileSize, project, false, false);
		
		luaExport.DeclareTable("tiles", project);

		if (Housecat::GetInstance().IsThereGroup("tles")) {
			int i = 0;

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

					if (sprite.isFixed) {
						//TODO
					}

					luaExport.DeclareTable("sprite", project);

					luaExport.WriteKeyAndQuotedValue("asset_id", sprite.assetID, project);
					luaExport.WriteKeyAndValue("width", sprite.width, false, project);
					luaExport.WriteKeyAndValue("height", sprite.height, false, project);
					luaExport.WriteKeyAndValue("z_index", sprite.zIndex, false, project);
					//luaExport.WriteKeyAndValue("is_fixed", fixed, true, project);

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
		luaExport.WriteWords("End", project);
		project.close();
	}
}