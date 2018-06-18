#pragma once

#include <iostream>
#include "Lua.hpp"
#include "Returns.hpp"

namespace slw {

	class Script {
	public:
		Script() = default;
		Script(std::string const& filename);

		template <typename RETURNS, typename... ARGS>
		void call(std::string const& functionName, ARGS const&... args, typename RETURNS::Callback const& callback)
		{
			unsigned int argsNb;
			unsigned int returnsNb;

			_api.getGlobal(functionName);

			argsNb = _api.pushMany<ARGS...>(args...);
			returnsNb = RETURNS::countReturns();

			_api.pCall(argsNb, returnsNb, 0);

			RETURNS()(_api, callback);

			_api.clearStack();
		};

		Lua const& getApi() const;

	private:
		Lua _api;
	};
}
