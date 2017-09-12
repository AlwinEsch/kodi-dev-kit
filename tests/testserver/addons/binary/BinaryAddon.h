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

#include "addons/IAddon.h"

#include <memory>
#include <msgpack.hpp>

namespace ADDON
{

  class IAddonInterface;
  class CBinaryAddon;
  typedef std::shared_ptr<CBinaryAddon> BinaryAddonPtr;

  class CBinaryAddon : public IAddon
  {
  public:
    CBinaryAddon(const std::string& id);
    ~CBinaryAddon();

    bool Create(bool independent, uint64_t addonPID);
    bool HandleMessage(int group, int func, const msgpack::unpacked& in, std::stringstream& out);
    bool HandleMessageGroupKodi(int func, const msgpack::unpacked& in, std::stringstream& out);

    const std::string& ID() const { return m_id; }
    bool IsActive() const;
    bool IsIndependent() const { return m_independent; }
    const uint64_t AddonPID() const { return m_addonPID; }
    int UsedRand() const { return m_usedRand; }

  private:
    const std::string m_id;
    IAddonInterface* m_addonInterface;
    int m_usedRand;
    bool m_independent;
    uint64_t m_addonPID;
  };

}
