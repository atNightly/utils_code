#include <iostream>
#include <lua.hpp>

using namespace std;

class Lua
{
	private:
		lua_State* m_pLuaState{nullptr};
	public:
		Lua()
			: m_pLuaState{luaL_newState()}
		{
			if(m_pLuaState)
			{
				luaL_openlibs(m_pLuaState);
			}
		}
		~Lua()
		{
			lua_close(m_pLuaState);
		}
		Lua(const Lua& other) = delete;
		Lua& operator=(const Lua& other) = delete;
		Lua(Lua&& rvalue) = delete;
		Lua& operator=(Lua&& ravlue) = delete;
		bool IsValid const
		{
			return m_pLuaState != nullptr;
		}
		int LoadFile(const string& filename)
		{
			int status
		}
}
