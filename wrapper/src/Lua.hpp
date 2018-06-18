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

		template <typename... DATAS>
		using ToManyCallback = std::function<void (DATAS const&...)>;

		bool loadFromFile(std::string const& filename) const;

		template <typename DATA>
		DATA get(std::string const& varName) const {
			DATA result;

			this->_putOnStack(varName);
			result = to<DATA>(-1);

			clearStack();
			return result;
		}

		Lua const& registerFunction(std::string const& name, CFunction callback) const;

		int getGlobal(std::string const& name) const;
		int pCall(int nargs, int nresults, int errFunc) const;
		void pop(int idx) const;
		void clearStack() const;

		template <typename DATA>
		void push(DATA) const {
			throw std::runtime_error(std::string("Unable to push on stack, type with mangled name '") + typeid(DATA).name() + "' is invalid.");
		}

		template <typename... DATAS>
		unsigned int
		pushMany(DATAS const&... datas)
		{
			_pushMany<DATAS...>(datas...);
			return sizeof...(DATAS);
		};

		template <typename DATA>
		DATA
		to(int idx) const {
			throw std::runtime_error(std::string("Unable to get from stack, type with mangled name '") + typeid(DATA).name() + "' is invalid.");
		}

		template <typename... DATAS>
		void
		toMany(ToManyCallback<DATAS...> const& callback)
		{
			_toMany<DATAS...>(callback, -1 - sizeof...(DATAS));
		};

	private:
		lua_State* _state;
		std::unordered_map<std::string, CFunction> _functions;

		void _checkState(std::string const& message) const;
		void _putOnStack(std::string const& varName) const;

		template <typename=void> void _pushMany() {};
		template <typename DATA, typename... DATAS>
		void
		_pushMany(DATA const& data, DATAS const&... datas)
		{
			this->push<DATA>(data);
			_pushMany<DATAS...>(datas...);
		};

		template <typename=void> void _toMany(std::function<void ()> const& callback, int) { callback(); };
		template <typename DATA, typename... DATAS>
		void
		_toMany(std::function<void (DATA const&, DATAS const&...)> const& callback, int idx)
		{
			_toMany<DATAS...>(ToManyCallback<DATAS...>([this, &callback, idx](DATAS const&... args) {
				callback(to<DATA>(idx), args...);
			}), ++idx);
		};
	};
}
