var kodi = require("./kodidevkit");

var props = new kodi.addon_properties;
props.id              = "demo_javascript_addon";
props.type            = "xbmc.addon.executable";
props.version         = "0.0.1";
props.name            = "Demo JavaScript add-on";
props.license         = "GPL2";
props.summary         = "";
props.description     = "Hello World";
props.path            = "";
props.libname         = "";
props.author          = "";
props.source          = "";
props.icon            = "";
props.disclaimer      = "";
props.changelog       = "";
props.fanart          = "";
props.independent     = false;

kodi.Init(props);

kodi.Log(kodi.LOG_DEBUG, "Hello LOG_DEBUG");
kodi.Log(kodi.LOG_INFO, "Hello LOG_INFO");
kodi.Log(kodi.LOG_NOTICE, "Hello LOG_NOTICE");
kodi.Log(kodi.LOG_WARNING, "Hello LOG_WARNING");
kodi.Log(kodi.LOG_ERROR, "Hello LOG_ERROR");
kodi.Log(kodi.LOG_SEVERE, "Hello LOG_SEVERE");
kodi.Log(kodi.LOG_FATAL, "Hello LOG_FATAL");
kodi.Log(kodi.LOG_DEBUG, "Hello formatted entry: " + "tata " + 123 + " " +  0.10101);
