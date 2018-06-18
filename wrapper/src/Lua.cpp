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
slw::Lua::registerFunction(std::string const& name, slw::Lua::CFunction callback) const
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

int
slw::Lua::pCall(int nargs, int nresults, int errFunc) const
{
	return lua_pcall(_state, nargs, nresults, errFunc);
}

void
slw::Lua::pushLightUserData(slw::Lua::LightUserData* lud) const
{
	lua_pushlightuserdata(_state, lud);
}

void
slw::Lua::pushNumber(slw::Lua::Number number) const
{
	lua_pushnumber(_state, number);
}

void
slw::Lua::pushInteger(slw::Lua::Integer integer) const
{
	lua_pushinteger(_state, integer);
}

std::string
slw::Lua::pushString(slw::Lua::String string) const
{
	return lua_pushstring(_state, string);
}

void
slw::Lua::pushBoolean(slw::Lua::Boolean boolean) const
{
	lua_pushboolean(_state, boolean);
}

void
slw::Lua::pushNil() const
{
	lua_pushnil(_state);
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

	template <>
	Lua::LightUserData
	Lua::to<Lua::LightUserData>(int idx) const
	{
		return lua_touserdata(_state, idx);
	}

	template <>
	Lua::LightUserDataConst
	Lua::to<Lua::LightUserDataConst>(int idx) const
	{
		return lua_topointer(_state, idx);
	}

	template <>
	Lua::Boolean
	Lua::to<Lua::Boolean>(int idx) const
	{
		return static_cast<Lua::Boolean>(lua_toboolean(_state, -1));
	}

	template <>
	Lua::Integer
	Lua::to<Lua::Integer>(int idx) const
	{
		if (!lua_isinteger(_state, -1)) {
			throw std::runtime_error("unable to get a variable, not an integer");
		}
		return lua_tointeger(_state, -1);
	}

	template <>
	Lua::Number
	Lua::to<Lua::Number>(int idx) const
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
		return static_cast<float>(to<Lua::Number>(idx));
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