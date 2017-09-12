#include <stdio.h>
#include <kodi/AddonBase.h>
#include <unistd.h>

int main()
{
  addon_properties props;
  props.id              = "demo_binary_addon";
  props.type            = "xbmc.addon.executable";
  props.version         = "0.0.1";
  props.name            = "Demo binary add-on";
  props.license         = "GPL2";
  props.summary         = "";
  props.description     = "Hallo";
  props.path            = "";
  props.libname         = "";
  props.author          = "";
  props.source          = "";
  props.icon            = "";
  props.disclaimer      = "";
  props.changelog       = "";
  props.fanart          = "";
  props.independent     = false;

  if (!kodi::Init(props))
  {
    fprintf(stderr, "ERROR: Kodi interface initialization failed!\n");
    return -1;
  }

  kodi::Log(LOG_DEBUG, "Hello 1 World with UUID %s", kodi::GetAddonIdentUUID().c_str());
  kodi::Log(LOG_DEBUG, "Hello 2 World with UUID %s", kodi::GetAddonIdentUUID().c_str());
  kodi::Log(LOG_DEBUG, "Hello 3 World with UUID %s", kodi::GetAddonIdentUUID().c_str());
  kodi::Log(LOG_DEBUG, "Hello 4 World with UUID %s", kodi::GetAddonIdentUUID().c_str());

//   sleep(2);
  for (unsigned int i = 0; i < 15; i++)
    kodi::Log(LOG_DEBUG, "Hello %i World with UUID %s", i, kodi::GetAddonIdentUUID().c_str());

  kodi::DeInit();
//   sleep(15);
  return 0;
}
