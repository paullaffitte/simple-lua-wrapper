#include "Script.hpp"

slw::Script::Script(std::string const& filename) : _api(filename)
{}

slw::Lua const&
slw::Script::getApi() const
{
	return _api;
}
