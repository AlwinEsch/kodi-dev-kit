#pragma once


#include <string>

typedef enum addonLog
{
  LOG_DEBUG = 0,
  LOG_INFO = 1,
  LOG_NOTICE = 2,
  LOG_WARNING = 3,
  LOG_ERROR = 4,
  LOG_SEVERE = 5,
  LOG_FATAL = 6
} addonLog;

namespace kodi
{
  void Log(const addonLog loglevel, const char* format, ...);
}
