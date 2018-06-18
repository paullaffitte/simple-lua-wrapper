#pragma once

#include <iostream>
#include "Lua.hpp"

namespace slw {

	class Script {
	public:
		Script() = default;
		Script(std::string const& filename);

		template <typename RETURN_CALLBACK, typename... ARGS>
		void call(std::string const& functionName, ARGS const&... args)
		{
			unsigned int argsNb;

			_api.getGlobal(functionName);

			argsNb = _api.pushMany<ARGS...>(args...);

			_api.pCall(argsNb, 1, 0);
			std::cout << _api.to<std::string>(-1) << std::endl;
			_api.pop(1);
		};

		Lua const& getApi() const;

	private:
		Lua _api;
	};
}
