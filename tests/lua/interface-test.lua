---- importing ----
if string.sub(_VERSION,1,7)=='Lua 5.0' then
	-- lua5.0 doesnt have a nice way to do this
	lib=loadlib('kodi-lua.dll','luaopen_kodi') or loadlib('kodi-lua.so','luaopen_kodi')
	assert(lib)()
else
	-- lua 5.1 does
	require('kodi-lua')
end

props = kodi.addon_properties();
props.id = "demo_lua_addon";
props.type = "xbmc.addon.executable";
props.version = "0.0.1";
props.name = "Demo LUA add-on";
props.license = "GPL2";
props.summary = "";
props.description = "Hello World";
props.path = "";
props.libname = "";
props.author = "";
props.source = "";
props.icon = "";
props.disclaimer = "";
props.changelog = "";
props.fanart = "";
props.independent = false;
kodi.Init(props);

kodi.Log(kodi.LOG_DEBUG, "Hello LOG_DEBUG")
kodi.Log(kodi.LOG_INFO, "Hello LOG_INFO");
kodi.Log(kodi.LOG_NOTICE, "Hello LOG_NOTICE");
kodi.Log(kodi.LOG_WARNING, "Hello LOG_WARNING");
kodi.Log(kodi.LOG_ERROR, "Hello LOG_ERROR");
kodi.Log(kodi.LOG_SEVERE, "Hello LOG_SEVERE");
kodi.Log(kodi.LOG_FATAL, "Hello LOG_FATAL");
kodi.Log(kodi.LOG_DEBUG, string.format("Hello formatted entry: '%s' %i %f", "tata", 123, 0.10101));
