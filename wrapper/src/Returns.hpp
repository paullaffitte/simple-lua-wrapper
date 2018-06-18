/*

#pragma once

#include <functional>
#include "Lua.hpp"

namespace slw {

	template <typename... RETURNS>
	class Returns {
	public:

		using Callback = Lua::ToManyCallback<RETURNS...>;

		void
		operator()(Lua& api, Callback callback)
		{
			api.toMany<RETURNS...>(callback);
		}

		static constexpr unsigned int
		countReturns()
		{
			return sizeof...(RETURNS);
		}
	};
}
