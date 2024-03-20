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

const EditorTexture& AssetManager::ReturnEditorTexture(const std::string& assetID) {
	return editorTextures[assetID];
}

bool AssetManager::EditorHasTexture(const std::string& assetID) {
	return editorTextures.find(assetID) != editorTextures.end();
}

void AssetManager::AddTexture(SDL_Renderer* renderer, const std::string& assetID, const std::string& filePath) {
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!surface) {
		Logger::Error("Error Loading Surface: " + std::string(SDL_GetError()));
		return;
	}
	else if (!texture) {
		Logger::Error("Error Loading Texture: " + std::string(SDL_GetError()));
		return;
	}

	textures.emplace(assetID, texture);
}

void AssetManager::AddEditorTexture(EditorRenderer& renderer, const std::string& assetID, const std::string& filePath) {
	if (!EditorHasTexture(assetID)) {
		SDL_Surface* surface = IMG_Load(filePath.c_str());
		EditorTexture texture = EditorTexture(SDL_CreateTextureFromSurface(renderer.get(), surface));
		SDL_FreeSurface(surface);

		editorTextures.emplace(assetID, std::move(texture));

		Logger::Debug("Editor Texture Added: " + assetID);
	}
}






TTF_Font* AssetManager::GetFont(const std::string& assetID) {
	return fonts[assetID];
}

void AssetManager::AddFont(const std::string& assetID, const std::string& filePath, int fontSize) {
	TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
	if (!font) {
		Logger::Error("Error Loading Font: " + std::string(TTF_GetError()));
		return;
	}

	fonts.emplace(assetID, font);
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
void AssetManager::PlaySound(const std::string& assetID, int volume, int loop) {
	Mix_Chunk* sfx = sounds[assetID];
	if (sfx) {
		int channel = Mix_PlayChannel(-1, sfx, loop);
		if (channel != -1) {
			Mix_Volume(channel, volume);
		}
	}
	else {
		Logger::Error("Error Playing Sound: " + std::string(Mix_GetError()));
	}
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