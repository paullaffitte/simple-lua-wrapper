#include <iostream>
#include "slw/Script.hpp"
#include "slw/ReturnCallback.hpp"

static int l_write(lua_State* L)
{
	std::cout << lua_tostring(L, 1) << std::endl;
	return 0;
}

int main()
{
	slw::Script script("./example/scripts/example1.lua");

	script.getApi().registerFunction("write", l_write);
	script.call<slw::ReturnCallback<std::string>, slw::Number, slw::Number>("write_sum", 1, -1.5);
	return 0;
}