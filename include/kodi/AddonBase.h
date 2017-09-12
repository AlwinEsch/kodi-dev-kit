#pragma once
/*
 *      Copyright (C) 2005-2017 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "definitions.h"

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
  const std::string& GetAddonIdentUUID();

  bool Init(addon_properties& props);

  bool Init(const std::string& addonXML);

  void DeInit();

  void Log(const addonLog loglevel, const char* format, ...);
}
