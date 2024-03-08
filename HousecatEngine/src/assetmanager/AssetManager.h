#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <map>
#include <string>
#include <memory>

class AssetManager {
private:
	std::map<std::string, SDL_Texture*> textures;
	std::unique_ptr<AssetManager> AssetManagerPtr;
	std::map<std::string, TTF_Font*> fonts;

	//TODO
	//assets to manage
	//sound

public:
	AssetManager();
	~AssetManager();

	SDL_Texture* GetTexture(const std::string& assetID);
	void AddTexture(SDL_Renderer* renderer, const std::string& assetID, const std::string& filePath);
	void ClearAssets();

	TTF_Font* GetFont(const std::string& assetID);

	void AddFont(const std::string& assetID, const std::string& filePath, int fontSize);

};

//editor method ptr
typedef std::unique_ptr<AssetManager> AssetManagerPtr;