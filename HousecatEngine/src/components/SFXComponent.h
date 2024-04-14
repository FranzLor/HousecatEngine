#pragma once

#include <SDL_mixer.h>

#include <map>
#include <string>


//----------------------------------------------------//
//                     COMPONENT                      //
//   Manages sound effects for entities within the    //
//                   game environment.                //
//----------------------------------------------------//



struct SFXComponent {
	std::string soundID;
	int volume;
	int loop;
	bool isPlaying;

	//seconds
	Uint32 delay;
	Uint32 lastPlayed;
	int channel;

	SFXComponent(std::string soundID = "", int volume = 50, int loop = 0, bool isPlaying = false, Uint32 delay = 1, int channel = 0) {
		this->soundID = soundID;
		this->volume = volume;
		this->loop = loop;
		this->isPlaying = isPlaying;
		this->delay = delay;
		this->lastPlayed = 0;
		this->channel = channel;
	}
};




/**
 *
 * @struct SFXComponent
 * @brief Holds properties related to the playback of sound effects for entities.
 *
 * This component is essential for managing sound effects in game entities, storing sound identifiers,
 * playback settings such as volume and looping, and timing controls for sound effect playback delays.
 * It is used extensively by the SoundSystem to trigger sounds based on game events like key presses,
 * collisions, or other game conditions.
 *
 * Usage:
 * - soundID: The identifier for the sound effect to be played, managed by the AssetManager.
 * - volume: Sound playback volume (0-128).
 * - loop: Number of times the sound is repeated; 0 for no loop, -1 for infinite looping.
 * - isPlaying: Flag to check if the sound is currently active.
 * - delay: Minimum time delay (in seconds) between consecutive plays of the sound.
 * - lastPlayed: Timestamp of the last time the sound was played (used with delay to manage timing).
 * - channel: Audio channel on which the sound is played. Multiple channels allow simultaneous sounds.
 *
 * Example:
 * 	enemy.AddComponent<SFXComponent>("enemy_attack", 100, 0, false, 1);
 * 	
 *  This setup allows an enemy attack sound to be played with a delay of 1 second between plays.
 *
 * Note:
 * - This component works in tandem with the SoundSystem, which handles the timing and conditions under
 *   which the sounds are played or stopped based on game logic and events.
 * 
 */