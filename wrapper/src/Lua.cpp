#include <iostream>
#include <sstream>
#include "Lua.hpp"

slw::Lua::Lua() : _state(luaL_newstate())
{}

slw::Lua::Lua(std::string const& filename) : _state(luaL_newstate())
{
	if(!this->loadFromFile(filename))
		throw std::runtime_error("Unable to load script at path: " + filename);
}

slw::Lua::~Lua()
{
	lua_close(_state);
}

void
slw::Lua::_cleanStack() const
{
	lua_pop(_state, lua_gettop(_state));
}

slw::Lua const&
slw::Lua::registerFunction(std::string const& name, slw::CFunction callback) const
{
	lua_pushcfunction(_state, callback);
	lua_setglobal(_state, name.c_str());
	return *this;
}

void
slw::Lua::_checkState(std::string const& message) const
{
	if (lua_isnil(_state, -1)) {
		throw std::runtime_error(message);
	}
}

void
slw::Lua::_putOnStack(std::string const& varName) const
{
	std::stringstream tokens(varName);
	std::string token;

	std::getline(tokens, token, '.');
	lua_getglobal(_state, token.c_str());
	_checkState(varName + " not defined.");

	while (std::getline(tokens, token, '.')) {
		lua_getfield(_state, -1, token.c_str());
		_checkState(varName + " not defined.");
	}
}

int
slw::Lua::getGlobal(std::string const& name) const
{
	return lua_getglobal(_state, name.c_str());
}

void
slw::Lua::pop(int idx) const
{
	lua_pop(_state, 1);
}

bool
slw::Lua::loadFromFile(std::string const& filename) const
{
	if (luaL_loadfile(_state, filename.c_str()) || lua_pcall(_state, 0, 0, 0)) {
		return false;
	}

	luaL_openlibs(_state);
	return true;
}

namespace slw {

	int
	Lua::pCall(int nargs, int nresults, int errFunc) const
	{
		return lua_pcall(_state, nargs, nresults, errFunc);
	}

	template <>
	void
	Lua::push(LightUserData* lud) const
	{
		lua_pushlightuserdata(_state, lud);
	}

	template <>
	void
	Lua::push(Number number) const
	{
		lua_pushnumber(_state, number);
	}

	template <>
	void
	Lua::push(Integer integer) const
	{
		lua_pushinteger(_state, integer);
	}

	template <>
	void
	Lua::push(String string) const
	{
		lua_pushstring(_state, string);
	}

	template <>
	void
	Lua::push(Boolean boolean) const
	{
		lua_pushboolean(_state, boolean);
	}

	template <>
	void
	Lua::push(Void a) const
	{
		lua_pushnil(_state);
	}

	template <>
	LightUserData
	Lua::to<LightUserData>(int idx) const
	{
		return lua_touserdata(_state, idx);
	}

	template <>
	LightUserDataConst
	Lua::to<LightUserDataConst>(int idx) const
	{
		return lua_topointer(_state, idx);
	}

	template <>
	Boolean
	Lua::to<Boolean>(int idx) const
	{
		return static_cast<Boolean>(lua_toboolean(_state, -1));
	}

	template <>
	Integer
	Lua::to<Integer>(int idx) const
	{
		if (!lua_isinteger(_state, -1)) {
			throw std::runtime_error("unable to get a variable, not an integer");
		}
		return lua_tointeger(_state, -1);
	}

	template <>
	Number
	Lua::to<Number>(int idx) const
	{
		if (!lua_isnumber(_state, -1)) {
			throw std::runtime_error("unable to get a variable, not a number");
		}
		return lua_tonumber(_state, -1);
	}

	template <>
	float
	Lua::to<float>(int idx) const
	{
		return static_cast<float>(to<Number>(idx));
	}

	template <>
	std::string
	Lua::to<std::string>(int idx) const
	{
		if (!lua_isstring(_state, -1)) {
			throw std::runtime_error("unable to get a variable, not a string");
		}
		return std::string(lua_tostring(_state, -1));
	}
}