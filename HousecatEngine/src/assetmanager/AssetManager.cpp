#include "AssetManager.h"
#include "../logger/Logger.h"

#include <SDL_image.h>

AssetManager::AssetManager() {
	Logger::Lifecycle("AssetManager Constructor Called!");
}

AssetManager::~AssetManager() {
	ClearAssets();
	Logger::Lifecycle("AssetManager Destructor Called!");
}

SDL_Texture* AssetManager::GetTexture(const std::string& assetID) {
	return textures[assetID];
}

void AssetManager::AddTexture(SDL_Renderer* renderer, const std::string& assetID, const std::string& filePath) {
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	textures.emplace(assetID, texture);
}

void AssetManager::ClearAssets() {
	for (auto texture : textures) {
		//makes sure to deallocate texture!
		SDL_DestroyTexture(texture.second);
	}
	//only clears map
	textures.clear();

	for (auto font : fonts) {
		TTF_CloseFont(font.second);
	}
	fonts.clear();
}

TTF_Font* AssetManager::GetFont(const std::string& assetID) {
	return fonts[assetID];
}

void AssetManager::AddFont(const std::string& assetID, const std::string& filePath, int fontSize) {
	fonts.emplace(assetID, TTF_OpenFont(filePath.c_str(), fontSize));
}