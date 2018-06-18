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

#include <iostream>
#include "slw/Script.hpp"

int main()
{
	slw::Script script("./example/scripts/example1.lua");

	script.getApi().registerFunction("write", [](lua_State* L) {
		std::cout << lua_tostring(L, 1) << std::endl;
		return 0;
	});

	script.call<slw::Returns<std::string, slw::Number>, slw::Number, slw::Number>(
		"magic_write_sum", 1, -1.5, [](std::string const& str, slw::Number const& num) -> void {
			std::cout << str << " " << num << std::endl;
			return;
		}
	);

	return 0;
}