#pragma once

#include "../editor/utilities/SDLUtility.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <map>
#include <string>
#include <memory>


//----------------------------------------------------//
//                  ASSET MANAGER CLASS               //
//   Manages loading, accessing, and managing game    //
//   resources like textures, fonts, music, and SFX.  //
//   This is also used by the Editor to manage        //
//                  tile textures.                    //
//----------------------------------------------------//


class AssetManager {
private:
	std::unique_ptr<AssetManager> AssetManagerPtr;

	std::map<std::string, SDL_Texture*> textures;

	std::map<std::string, EditorTexture> editorTextures;

	std::map<std::string, TTF_Font*> fonts;

	std::map<std::string, Mix_Music*> musics;
	std::map<std::string, Mix_Chunk*> sounds;

public:
	AssetManager();
	~AssetManager();

	//use for game projects
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



	//---------------------------------------------------------------------------------------------------------------------// 

	
	//use for editor projects
	void AddEditorTexture(EditorRenderer& renderer, const std::string& assetID, const std::string& filePath);
	const EditorTexture& ReturnEditorTexture(const std::string& assetID);
	bool EditorHasTexture(const std::string& assetID);


	//---------------------------------------------------------------------------------------------------------------------// 


	//usable for both
	void ClearAssets();
};

//used by the Editor
typedef std::unique_ptr<AssetManager> AssetManagerPtr;



/**
 * @class AssetManager
 * @brief Manages and centralizes access to game assets like textures, fonts, and sounds.
 *
 * AssetManager provides a way to load, access, and manage game assets across different
 * parts of the game or editor. It handles textures, fonts, music, and sound effects, ensuring that
 * these resources are loaded efficiently and are easily accessible through unique identifiers. This
 * class simplifies resource management and prevents the reloading of assets multiple times.
 *
 * Usage:
 * - Load and retrieve textures and fonts as needed for game objects.
 * - Manage audio playback for music and sound effects with controls for volume and looping.
 * - Serve as a bridge between low-level media loading and high-level game functions.
 *
 * Example:
 * 	AssetManager assetManager;
 * 	assetManager.AddTexture(renderer, "playerSprite", "path/to/texture.png");
 * 	assetManager.AddMusic("backgroundMusic", "path/to/music.ogg");
 * 	assetManager.PlayMusic("backgroundMusic", -1);
 *
 * Key Methods:
 * - AddTexture(renderer, assetID, filePath): Loads a texture from a file and stores it with an asset identifier.
 * - GetTexture(assetID): Retrieves a loaded texture by its identifier.
 * - AddFont(assetID, filePath, fontSize): Loads a TTF font with a specified size.
 * - PlayMusic(assetID, loop): Plays a music track with options to loop.
 * - PlaySound(assetID, volume, loop): Plays a sound effect with specified volume and loop settings.
 * - ClearAssets(): Frees all loaded assets, useful during cleanup.
 *
 * Note:
 * Use 'AddTexture' for game-related projects to manage game textures. Use 'AddEditorTexture' for developing editor tools or interfaces,
 * ensuring resources are optimized separately for each environment. This distinction helps maintain efficiency and performance across
 * different use cases.
 */