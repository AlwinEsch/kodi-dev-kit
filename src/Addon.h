#pragma once
/*
 *      Copyright (C) 2015-2017 Team KODI, Alwin Esch
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
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "definitions.h"
#include <p8-platform/sockets/tcp.h>

class IAddonInterface;

class CAddon
{
public:
  CAddon();
  ~CAddon();

  const std::string& GetUsedUUID() const { return m_uuid; }

  bool Connect(addon_properties& props);
  void SendMessage(const std::stringstream& in, std::stringstream& ret);
  void Disconnect();

  static CAddon m_main;

private:
  bool readData(char* buffer, int totalBytes, int timeout);

  IAddonInterface* m_interface;
  P8PLATFORM::CTcpConnection *m_socket;
  bool m_isLocal;
  int m_usedRand;
  addon_properties m_props;

  static const std::string m_uuid;
};
