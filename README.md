# Simple Lua Wrapper

The goal of this library is to provide a simple way to execute Lua scripts in a perfect osmosis along with C++ source code.

---

You can easily load a script from a file
``` cpp
slw::Script script("./example/scripts/example1.lua");
```

Register some C function...
``` cpp
static int l_write(lua_State* L)
{
    std::cout << lua_tostring(L, 1) << std::endl;
    return 0;
}

...

script.getApi().registerFunction("write", l_write);
```
...And call it from Lua !
``` lua
write("Hello world!")
```
Output:
```
Hello world!
```

You even can call a Lua function from C++, and use all the power of Lua (multiple return values included)
``` cpp
script.call<slw::Returns<std::string, slw::Number>, slw::Number, slw::Number>(
    "magic_write_sum", 1, -1.5, [](std::string const& str, slw::Number const& num) -> void {
        std::cout << str << " " << num << std::endl;
        return;
    }
);
```
``` lua
function magic_write_sum(a, b)
    write(sum(a, b))
    return "hello world!", 42
end

function sum(a, b)
    return a + b
end
```
Output:
```
-0.5
hello world! 42
```
