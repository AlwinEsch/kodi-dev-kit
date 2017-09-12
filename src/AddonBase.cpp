#include "Addon.h"

#include "AddonBase.h"

#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#include <msgpack.hpp>
#include <sstream>

namespace kodi
{

const std::string& GetAddonIdentUUID()
{
  return CAddon::m_main.GetUsedUUID();
}

bool Init(addon_properties& props)
{
  return CAddon::m_main.Connect(props);
}

bool Init(const std::string& addonXML)
{
  fprintf(stderr, "Hello World\n");
  return false;
}

void DeInit()
{
  CAddon::m_main.Disconnect();
}

void Log(const addonLog loglevel, const char* format, ...)
{
  char buffer[16384];
  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);

  std::stringstream in;
  std::stringstream out;
  msgpack::pack(in, stream_msg_ident("kodi_log", groupId::grKodi, funcIdKodi::kodi_log));
  msgpack::pack(in, stream_msg_kodi_log(static_cast<int>(loglevel), buffer));
  CAddon::m_main.SendMessage(in, out);
}

}
