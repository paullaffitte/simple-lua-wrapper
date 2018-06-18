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

	using CFunction = lua_CFunction;
	using LightUserData = void*;
	using LightUserDataConst = void const*;
	using Number = lua_Number;
	using Integer = lua_Integer;
	using Unsigned = lua_Unsigned;
	using String = char const*;
	using Boolean = bool;
	using Void = struct{};

	class Lua {
	public:
		Lua();
		explicit Lua(std::string const& filename);
		~Lua();

		bool loadFromFile(std::string const& filename) const;

		template <typename DATA>
		DATA get(std::string const& varName) const {
			DATA result;

			this->_putOnStack(varName);
			result = to<DATA>(-1);

			_cleanStack();
			return result;
		}

		Lua const& registerFunction(std::string const& name, CFunction callback) const;

		int getGlobal(std::string const& name) const;
		int pCall(int nargs, int nresults, int errFunc) const;
		void pop(int idx) const;

		template <typename DATA>
		void push(DATA data) const {
			throw std::runtime_error(std::string("Unable to push on stack, type with mangled name '") + typeid(DATA).name() + "' is invalid.");
		}

		template <typename... DATAS>
		unsigned int
		pushMany(DATAS const&... datas)
		{
			return _pushMany<DATAS...>(0, datas...);
		};

		template <typename DATA>
		DATA
		to(int idx) const {
			throw std::runtime_error(std::string("Unable to get from stack, type with mangled name '") + typeid(DATA).name() + "' is invalid.");
		}

		template <typename... DATAS>
		unsigned int
		to(std::function<void (DATAS const&...)> callback)
		{
			return _to<DATAS...>(callback);
		};

	private:
		lua_State* _state;
		std::unordered_map<std::string, CFunction> _functions;

		void _checkState(std::string const& message) const;
		void _putOnStack(std::string const& varName) const;
		void _cleanStack() const;

		template <typename DATA, typename... DATAS>
		unsigned int
		_pushMany(unsigned int datasNb, DATA const& data, DATAS const&... datas)
		{
			this->push<DATA>(data);
			return _pushMany<DATAS...>(datasNb + 1, datas...);
		};

		template <typename DATA>
		unsigned int
		_pushMany(unsigned int datasNb, DATA const& data)
		{
			this->push<DATA>(data);
			return datasNb + 1;
		};

		template <typename=void>
		unsigned int
		_pushMany(unsigned int)
		{
			return 0;
		};

		template <typename DATA, typename... DATAS>
		void
		_to(std::function<void (DATA const&, DATAS const&...)> callback)
		{
			return to<DATA>(callback);
		};
	};
}