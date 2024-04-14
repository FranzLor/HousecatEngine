#pragma once

//----------------------------------------------------//
//                      EVENT CLASS                    //
//      The base class for all events in the system.   //
//        It is inherited by all specific event        //
//               types used in the game.               //
//----------------------------------------------------//


struct Event {
	Event() = default;
};



/**
 * @struct Event
 * @brief Serves as the base class for all specific event types within the application.
 *
 * This class is the foundation for the event system, allowing different parts of the application
 * to communicate with each other without direct dependencies. Derived classes represent specific
 * types of events (e.g., collisions, user input, sound effects) that systems can subscribe to and
 * handle accordingly.
 *
 * Usage:
 * - Derived classes such as CollisionEvent, KeyPressedEvent, KeyReleasedEvent, and SFXEvent
 *   extend this base class to provide additional information relevant to those specific events.
 * - EventManager manages these events, dispatching them to the appropriate listeners when they occur.
 *
 * Example:
 * 	
 * 	struct CollisionEvent : public Event {
 * 	    Entity a;
 * 	    Entity b;
 * 	    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
 * 	};
 * 
 *  Derived event class for handling collisions
 *
 * Key Concept:
 * - The Event class itself does not contain data. It provides a common interface for all events,
 *   ensuring that the event handling system can process different types of events in a uniform manner.
 *
 * This approach allows for a flexible, loosely coupled system where various components can interact
 * through events without needing to know the details of each other's implementation.
 */