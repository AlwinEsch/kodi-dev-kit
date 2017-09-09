#include "kodi.h"

#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

namespace kodi
{

void Log(const addonLog loglevel, const char* format, ...)
{
  char buffer[16384];
  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);

  fprintf(stderr, "--------- level %i - %s\n", loglevel, buffer);
}

}
