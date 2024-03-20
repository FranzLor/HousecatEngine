#pragma once

#include "Event.h"

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"

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

class StopSFXEvent : public Event {
public:
	Entity& entity;
	int channel;

	StopSFXEvent(Entity& entity, int channel) : entity(entity), channel(channel) {}
};

class AdjustVolumeEvent : public Event {
public:
	Entity& entity;
	int volume;
	int channel;

	AdjustVolumeEvent(Entity& entity, int volume, int channel) : entity(entity), volume(volume), channel(channel) {}
};