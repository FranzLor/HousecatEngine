#pragma once

#include <list>
#include <map>
#include <typeindex>
#include <memory>
#include <functional>

#include "../events/Event.h"
#include "../logger/Logger.h"



//----------------------------------------------------//
//                  EVENT MANAGER CLASS               //
//    Manages events and notifications across various  //
//       systems and components in the application.   //
//----------------------------------------------------//




class IEventFunction {
private:
	virtual void Call(Event& e) = 0;

public:
	virtual ~IEventFunction() = default;

	void Execute(Event& e) {
		Call(e);
	}
};

template <typename TOwner, typename TEvent>
class EventFunction: public IEventFunction {
private:
	typedef void (TOwner::*CallbackFunction)(TEvent&);

	TOwner* ownerInstance;
	CallbackFunction callbackFunction;

	virtual void Call(Event& e) override {
		std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
	}

public:
	EventFunction(TOwner* ownerInstance, CallbackFunction callbackFunction) {
		this->ownerInstance = ownerInstance;
		this->callbackFunction = callbackFunction;
	}

	virtual ~EventFunction() override = default;
};

//respond to events
typedef std::list<std::unique_ptr<IEventFunction>> EventHandlers;

class EventManager {
private:
	//map [type event], [list of callback functs.]
	std::map<std::type_index, std::unique_ptr<EventHandlers>> listeners;

public:
	EventManager() {
		//Logger::Lifecycle("EventManager Constructor Called!");
	}

	~EventManager() {
		//Logger::Lifecycle("EventManager Destructor Called1");
	}

	//clears listener list
	void Reset() {
		listeners.clear();
	}

	//-------------------------------------------------------------------//
	//                          EVENT TRIGGER                            //
	//              if event happens this triggers all the               //
	//                  listeners callback functions                     //
	//  EX: eventManager->TriggerEvent<CollisionEvent>(entityA, entityB) //
	//-------------------------------------------------------------------//
	template <typename TEvent, typename ...TArgs>
	void TriggerEvent(TArgs&& ...args) {
		auto handlers = listeners[typeid(TEvent)].get();

		if (handlers) {
			for (auto iterator = handlers->begin(); iterator != handlers->end(); iterator++) {
				auto handler = iterator->get();
				TEvent event(std::forward<TArgs>(args)...);
				handler->Execute(event);
			}
		}
	}

	//----------------------------------------------------------------------------------//
	//                                 EVENT LISTENER                                   //
	//              system listeners subscribe to certain event by type <T>             //
	//  EX: eventManager->ListenToEvent<CollisionEvent>(this, &Game::HandleCollision);  //
	//----------------------------------------------------------------------------------//
	template <typename TEvent, typename TOwner>
	void ListenToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
		//create new key 
		if (!listeners[typeid(TEvent)].get()) {
			listeners[typeid(TEvent)] = std::make_unique<EventHandlers>();
		}

		//create then push, moving ownership in unique ptr
		auto listener = std::make_unique<EventFunction<TOwner, TEvent>>(ownerInstance, callbackFunction);	
		listeners[typeid(TEvent)]->push_back(std::move(listener));
	}
};





/**
 *
 * @class EventManager
 * @brief Handles dynamic event subscription and dispatching throughout the application.
 *
 * The EventManager facilitates a publish-subscribe (observer) pattern, decoupling the event
 * sources from the event listeners. It supports dynamic subscription to events using templates
 * and function pointers, allowing systems to react to specific events without hard dependencies.
 * The manager uses type safety and run-time efficiency as core principles, utilizing templates
 * and polymorphism to handle different event types generically.
 *
 * Usage:
 * - Systems or components can subscribe to specific events using the ListenToEvent method,
 *   specifying the event type and a callback function.
 * - Events can be triggered using TriggerEvent, which will notify all subscribed listeners
 *   appropriately.
 *
 * General Example:
 * 	EventManager eventManager;
 * 
 * 	eventManager.ListenToEvent<CollisionEvent>(this, &GameSystem::HandleCollision);
 * 	eventManager.TriggerEvent<CollisionEvent>(entityA, entityB);
 *
 * Key Methods:
 * - ListenToEvent<TEvent>(owner, callback): Subscribes a system to listen for an event of type TEvent.
 * - TriggerEvent<TEvent>(args...): Dispatches an event of type TEvent to all registered listeners.
 * - Reset(): Clears all subscriptions, useful for cleanup or reinitializing the event handling.
 *
 */

