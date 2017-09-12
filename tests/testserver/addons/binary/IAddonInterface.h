#pragma once
/*
 *      Copyright (C) 2017 Team KODI, Alwin Esch
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

#include <iostream>
#include <sstream>

#include "BinaryAddon.h"

namespace ADDON
{

class IAddonInterface
{
public:
  IAddonInterface(CBinaryAddon* addon) : m_addon(addon) { }
  virtual ~IAddonInterface() = default;

  virtual bool Create() = 0;
  virtual void Destroy() = 0;
  virtual bool LoggedIn() const { return m_loggedIn; }
  virtual void SetLoggedIn(bool loggedIn) { m_loggedIn = loggedIn; }
  virtual void SendMessage(const std::stringstream& in, std::stringstream& ret) = 0;

  inline CBinaryAddon* GetAddon() { return m_addon; }

private:
  bool m_loggedIn;
  CBinaryAddon* m_addon;
};

}
