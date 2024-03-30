#pragma once

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function function;

	ScriptComponent(sol::function function = sol::lua_nil) {
		this->function = function;
	}
};