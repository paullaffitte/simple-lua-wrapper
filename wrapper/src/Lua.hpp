#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <functional>
#include <unordered_map>

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

namespace slw {

	class Lua {
	public:
		Lua();
		explicit Lua(std::string const& filename);
		~Lua();

		using CFunction = lua_CFunction;
		using LightUserData = void*;
		using LightUserDataConst = void const*;
		using Number = lua_Number;
		using Integer = lua_Integer;
		using Unsigned = lua_Unsigned;
		using String = const char*;
		using Boolean = bool;

		bool loadFromFile(std::string const& filename) const;

		template <typename Data>
		Data get(std::string const& varName) const {
			Data result;

			this->_putOnStack(varName);
			result = to<Data>(-1);

			_cleanStack();
			return result;
		}

		Lua const& registerFunction(std::string const& name, CFunction callback) const;

		int getGlobal(std::string const& name) const;
		int pCall(int nargs, int nresults, int errFunc) const;
		void pop(int idx) const;

		void pushLightUserData(LightUserData *lud) const;
		void pushNumber(Number number) const;
		void pushInteger(Integer integer) const;
		std::string pushString(String string) const;
		void pushBoolean(Boolean boolean) const;
		void pushNil() const;

		template <typename Data>
		Data to(int idx) const {
			throw std::runtime_error(std::string("Unable to get from stack, type with mangled name '") + typeid(Data).name() + "' is invalid.");
		}

	private:
		lua_State* _state;
		std::unordered_map<std::string, CFunction> _functions;

		void _checkState(std::string const& message) const;
		void _putOnStack(std::string const& varName) const;
		void _cleanStack() const;
	};
}