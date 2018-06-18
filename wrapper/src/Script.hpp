/*
 * MIT License
 *
 * Copyright (c) 2018 Paul Laffitte
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
