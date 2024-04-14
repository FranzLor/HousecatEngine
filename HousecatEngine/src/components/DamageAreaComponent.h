#pragma once

//----------------------------------------------------//
//                     COMPONENT                      //
//      Manages damage properties for game entities   //
//            that can inflict or receive damage.     //
//----------------------------------------------------//



struct DamageAreaComponent {
	bool isFriendly;
	int hitPercentDamage;
	double damageDelay;
	double lastDamageTimer;

	DamageAreaComponent(bool isFriendly = false, int hitPercentDamage = 0, double damageDelay = 0.0) {
		this->isFriendly = isFriendly;
		this->hitPercentDamage = hitPercentDamage;
		this->damageDelay = damageDelay;
		this->lastDamageTimer = 0.0;
	}
};




/**
 * @struct DamageAreaComponent
 * @brief Encapsulates damage-dealing properties for entities.
 *
 * This component is used to mark entities that can inflict damage to others,
 * used with a BoxColliderComponent to define the
 * physical space in which these interactions can occur. It holds properties
 * that define the damage mechanics, like damage magnitude, delay between
 * damage applications, and friendliness (doesn't harm player).
 *
 * Usage:
 * - isFriendly: Flag indicating if the entity does not harm the player or allies.
 * - hitPercentDamage: The percentage of health to be deducted on a successful hit.
 * - damageDelay: Minimum time interval (in seconds) required between successive
 *                damage applications to prevent rapid damage.
 * - lastDamageTimer: Tracks the time when the last damage was inflicted.
 *
 * Example:
 * 	fireTrap.AddComponent<BoxColliderComponent>(...);
 * 	fireTrap.AddComponent<DamageAreaComponent>(false, 10, 1.0);
 * 	
 *  This sets up a trap that causes 10% damage every 1 second to any entity that collides with it.
 *
 * Note:
 * - This component works closely with the DamageSystem, which handles the detection
 *   of collisions and applies the damage based on the specifications of this component.
 * - The system also manages damage timing to ensure that the damageDelay is respected,
 *   preventing excessive damage application within a short time frame.
 * 
 */