#pragma once

#include "Event.h"

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"


//----------------------------------------------------//
//                 PLAY SFX EVENT CLASS               //
// Triggers playback of a sound effect for an entity. //
//----------------------------------------------------//



class PlaySFXEvent : public Event {
public:
	Entity& entity;
	std::string soundID;
	int volume;
	bool loop;
	int channel;

	PlaySFXEvent(Entity& entity, const std::string& soundID, bool loop, int volume, int channel)
		: entity(entity), soundID(soundID), volume(volume), loop(loop), channel(channel) {}
};



/**
 *
 * @class PlaySFXEvent
 * @brief An event that requests the playback of a sound effect with specific properties.
 *
 * This event is used to initiate the playback of a sound effect identified by a soundID
 * for a particular entity. It includes parameters for volume, looping, and the audio channel,
 * allowing for precise control over how the sound is played.
 *
 * Usage:
 * - The event is dispatched when a sound effect needs to be played, typically in response to
 *   game interactions or player actions.
 *
 * Example:
 * 	PlaySFXEvent playEvent(entity, "explosion_sound", true, 100, 1);
 * 	eventManager->TriggerEvent(playEvent);
 *
 * Key Members:
 * - entity: Reference to the entity for which the sound effect is applicable.
 * - soundID: Identifier for the sound effect to be played.
 * - volume: Volume level at which to play the sound.
 * - loop: Whether the sound should loop continuously.
 * - channel: The audio channel on which to play the sound.
 *
 */


//----------------------------------------------------//
//                 STOP SFX EVENT CLASS               //
//              Requests the stopping of a            //
//              sound effect for an entity.           //
//----------------------------------------------------//

class StopSFXEvent : public Event {
public:
	Entity& entity;
	int channel;

	StopSFXEvent(Entity& entity, int channel) : entity(entity), channel(channel) {}
};



/**
 *
 * @class StopSFXEvent
 * @brief An event that requests the stopping of a sound effect for a specific entity.
 *
 * This event is used to stop the playback of a sound effect on a specific audio channel.
 * It's useful for managing sound effects that may need to be interrupted or halted due
 * to game events or user actions.
 *
 * Usage:
 * - The event is dispatched when there is a need to stop a currently playing sound effect.
 *
 * Example:
 * 	StopSFXEvent stopEvent(entity, 1);
 * 	eventManager->TriggerEvent(stopEvent);
 *
 * Key Members:
 * - entity: Reference to the entity for which the sound effect should be stopped.
 * - channel: The audio channel on which to stop the sound.
 * 
 */


//----------------------------------------------------//
//              ADJUST VOLUME EVENT CLASS             //
//   Modifies the volume of a playing sound effect.   //
//----------------------------------------------------//


class AdjustVolumeEvent : public Event {
public:
	Entity& entity;
	int volume;
	int channel;

	AdjustVolumeEvent(Entity& entity, int volume, int channel) : entity(entity), volume(volume), channel(channel) {}
};



/**
 *
 * @class AdjustVolumeEvent
 * @brief An event that adjusts the volume of a sound effect for a specific entity.
 *
 * This event allows dynamic control over the volume of an actively playing sound effect,
 * adjusting the audio output to suit the gameplay needs or user preferences.
 *
 * Usage:
 * - The event is dispatched when the sound effect volume needs adjustment while it is still playing.
 *
 * Example:
 * 	AdjustVolumeEvent volumeEvent(entity, 80, 1);
 * 	eventManager->TriggerEvent(volumeEvent);
 *
 * Key Members:
 * - entity: Reference to the entity for which the volume adjustment is applicable.
 * - volume: New volume level to set.
 * - channel: The audio channel on which to adjust the volume.
 * 
 */