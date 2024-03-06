#pragma once

#include <map>
#include <SDL.h>
#include <string>

class AssetManager {
private:
	std::map<std::string, SDL_Texture*> textures;

	//TODO
	//assets to manage
	//sound
	//fonts

public:
	AssetManager();
	~AssetManager();

	SDL_Texture* GetTexture(const std::string& assetID);
	void AddTexture(SDL_Renderer* renderer, const std::string& assetID, const std::string& filePath);
	void ClearTexture();

};