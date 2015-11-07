#include <lua.hpp>

int main(int argc,char* argv[])
{
	lua_State* pLuaState{luaL_newstate()};
	if (pLuaState)
	{
		luaL_openlibs(pLuaState);
		lua_close(pLuaState);
	}
	return 0;
}
