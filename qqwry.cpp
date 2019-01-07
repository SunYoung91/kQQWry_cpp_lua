#include <stdlib.h>
#include <string.h>
#include "ip_finder.h"

extern "C" {
	
#include <lua.h>
#include <lauxlib.h>



static CIpFinder* DataBase = NULL;



	static int open_data_base(lua_State *L)
	{
		if (DataBase){
			delete DataBase; 
		}
		
		size_t klen;
		const char *fp = luaL_checklstring(L, 1, &klen);
		if (klen < 1) {
			return luaL_error(L, "filePath is not avild");
		}
		
		DataBase = new CIpFinder();
		bool isOpen = DataBase->Open(fp);
		lua_pushboolean(L,isOpen);
		return 1;
	}


	static int getip_info(lua_State *L)
	{
		size_t klen;
		const char *ip = luaL_checklstring(L, 1, &klen);
		
		if (klen < 1) {
			return luaL_error(L, "ip is not avild");
		}
		
		if (!DataBase){
			lua_pushstring(L,"database not open");
			return 1;
		}
		
		{
			std::string strCountry;
			std::string strLocation;
			DataBase->GetAddressByIp(ip,strCountry,strLocation);
			strCountry += ",";
			strCountry += strLocation;
			lua_pushstring(L,strCountry.c_str());
			return 1;
		}
		
	}
	
	

	
	/*
	** Assumes the table is on top of the stack.
	*/
	static void set_info (lua_State *L) {
		lua_pushliteral (L, "_COPYRIGHT");
		lua_pushliteral (L, "Copyright (C) 2017-2018 KADIN");
		lua_settable (L, -3);
		lua_pushliteral (L, "_DESCRIPTION");
		lua_pushliteral (L, "KADIN");
		lua_settable (L, -3);
		lua_pushliteral (L, "_VERSION");
		lua_pushliteral (L, "kQQWRY 1.0");
		lua_settable (L, -3);
	}


	static struct luaL_Reg qqwry[] = {
	  {"open", open_data_base},
	  {"query", getip_info},
	  {NULL, NULL}
	};


	int luaopen_qqwry_core(lua_State *L) {
	  lua_newtable(L);
	  luaL_setfuncs(L, qqwry, 0);
	  set_info (L);
	  return 1;
	}

}