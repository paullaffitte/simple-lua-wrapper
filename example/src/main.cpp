#include <iostream>
#include "slw/Script.hpp"

static int l_write(lua_State* L)
{
	std::cout << lua_tostring(L, 1) << std::endl;
	return 0;
}

int main()
{
	slw::Script script("./example/scripts/example1.lua");

	script.getApi().registerFunction("write", l_write);

	script.call<slw::Returns<std::string, slw::Number>, slw::Number, slw::Number>(
		"magic_write_sum", 1, -1.5, [](std::string const& str, slw::Number const& num) -> void {
			std::cout << str << " " << num << std::endl;
			return;
		}
	);

	return 0;
}