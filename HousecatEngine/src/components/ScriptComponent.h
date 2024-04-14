#pragma once

#include <sol/sol.hpp>

//----------------------------------------------------//
//                     COMPONENT                      //
//      Allows dynamic scripting for entities using   //
//                  the Lua programming language.     //
//----------------------------------------------------//



struct ScriptComponent {
	sol::function function;

	ScriptComponent(sol::function function = sol::lua_nil) {
		this->function = function;
	}
};




/**
 *
 * @struct ScriptComponent
 * @brief Holds a Lua function that can dictate the behavior of an entity.
 *
 * This component embeds a Lua function as part of an entity's definition, enabling complex and dynamic
 * behavior modifications at runtime. It is utilized by the ScriptSystem to execute Lua scripts that can
 * manipulate various aspects of an entity, such as position, velocity, and visual states, based on
 * game logic or player interactions.
 *
 * Usage:
 * - function: A sol::function representing the Lua script associated with the entity.
 *
 * Example:
 * 	enemy.AddComponent<ScriptComponent>(lua["script"][0]);
 * 	
 *  This will attach a predefined Lua script from a Lua table that manages movement patterns.
 * 
 * Example in Lua Table:
 * script = {
        [0] =
            function(entity, delta_time, ellapsed_time)
                local current_position_x, current_position_y = get_position(entity)
                local current_velocity_x, current_velocity_y = get_velocity(entity)

                --define the movement area
                if current_position_x < 35  or current_position_x > 400 then
                    set_velocity(entity, current_velocity_x * -1, 0 );
                    if current_velocity_x * -1 > 0 then
                        --flip on horizontal axis
                        set_sprite_flip(entity, 1);
                    else
                        --no flip
                        set_sprite_flip(entity, 0);
                    end
                else
                    set_velocity(entity, current_velocity_x, 0);
                    if current_velocity_x > 0 then
                        --flip to right
                        set_sprite_flip(entity, 1);
                    else
                        --no flip
                        set_sprite_flip(entity, 0);
                    end
                end
            end
    }
 *  This will move the entity back and forth within the specified range, flipping the sprite when changing direction.
 *
 * Note:
 * - The ScriptComponent must be accompanied by the ScriptSystem for the Lua script execution to take place.
 * - Scripts can control virtually any component attached to the entity, allowing for flexible and dynamic
 *   game mechanics that can be altered without recompiling the C++ code.
 * 
 */