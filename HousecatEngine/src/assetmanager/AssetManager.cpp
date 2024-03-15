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





TTF_Font* AssetManager::GetFont(const std::string& assetID) {
	return fonts[assetID];
}

void AssetManager::AddFont(const std::string& assetID, const std::string& filePath, int fontSize) {
	fonts.emplace(assetID, TTF_OpenFont(filePath.c_str(), fontSize));
}





Mix_Music* AssetManager::GetMusic(const std::string& assetID) {
	return musics[assetID];
}

void AssetManager::AddMusic(const std::string& assetID, const std::string& filePath) {
	Mix_Music* music = Mix_LoadMUS(filePath.c_str());

	if (!music) {
		Logger::Error("Error Loading Music: " + std::string(Mix_GetError()));
	}
	musics.emplace(assetID, music);
}

void AssetManager::SetVolume(int volume) {
	Mix_VolumeMusic(volume);
}

void AssetManager::PlayMusic(const std::string& assetID, int loop) {
	Mix_Music* music = musics[assetID];
	if (music) {
		Mix_PlayMusic(music, loop);
	}
	else {
		Logger::Error("Error Playing Music: " + std::string(Mix_GetError()));
	}
}

void AssetManager::PauseMusic() {
	Mix_PauseMusic();
}

void AssetManager::StopMusic() {
	Mix_HaltMusic();
}





Mix_Chunk* AssetManager::GetSound(const std::string& assetID) {
	return sounds[assetID];
}
void AssetManager::AddSound(const std::string& assetID, const std::string& filePath) {
	Mix_Chunk* sfx = Mix_LoadWAV(filePath.c_str());
	if (!sfx) {
		Logger::Error("Error Loading Sound: " + std::string(Mix_GetError()));
	}
	sounds.emplace(assetID, sfx);
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

	for (auto music : musics) {
		Mix_FreeMusic(music.second);
	}
	musics.clear();

	for (auto sfx : sounds) {
		Mix_FreeChunk(sfx.second);
	}
	sounds.clear();
}