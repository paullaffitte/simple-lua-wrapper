/*
** EPITECH PROJECT, 2017
** simple-lua-wrapper-example
** File description:
** A file for simple-lua-wrapper-example - Paul Laffitte
*/

#pragma once

#include <lua.h>

namespace slw {

	template <typename... RETURNTYPES>
	class ReturnCallback {
		void operator()(lua_State* state) const;
	};

	template<typename... RETURNTYPES>
	void ReturnCallback<RETURNTYPES...>::operator()(lua_State* state) const
	{

	}
}
