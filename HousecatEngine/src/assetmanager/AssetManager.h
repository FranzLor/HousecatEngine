#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <map>
#include <string>
#include <memory>

class AssetManager {
private:
	std::unique_ptr<AssetManager> AssetManagerPtr;

	std::map<std::string, SDL_Texture*> textures;

	std::map<std::string, TTF_Font*> fonts;

	std::map<std::string, Mix_Music*> musics;
	std::map<std::string, Mix_Chunk*> sounds;

public:
	AssetManager();
	~AssetManager();

	SDL_Texture* GetTexture(const std::string& assetID);
	void AddTexture(SDL_Renderer* renderer, const std::string& assetID, const std::string& filePath);

	TTF_Font* GetFont(const std::string& assetID);
	void AddFont(const std::string& assetID, const std::string& filePath, int fontSize);

	Mix_Music* GetMusic(const std::string& assetID);
	void AddMusic(const std::string& assetID, const std::string& filePath);
	void SetVolume(int volume);
	void PlayMusic(const std::string& assetID, int loop);
	void PauseMusic();
	void StopMusic();

	Mix_Chunk* GetSound(const std::string& assetID);
	void AddSound(const std::string& assetID, const std::string& filePath);
	void PlaySound(const std::string& assetID, int volume, int loop);

	void ClearAssets();

};

//editor method ptr
typedef std::unique_ptr<AssetManager> AssetManagerPtr;