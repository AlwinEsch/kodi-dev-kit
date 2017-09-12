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

#include "addons/binary/IAddonInterface.h"
#include "threads/Thread.h"

#include "kodi/definitions.h"

#include <string>

struct apiShareData;

namespace ADDON
{

  class CBinaryAddonSharedMemoryPosix;
  class CBinaryAddonSharedMemoryWindows;
  class CBinaryAddon;

  class CBinaryAddonSharedMemory : public IAddonInterface, protected CThread
  {
  public:
    CBinaryAddonSharedMemory(CBinaryAddon* addon, int randNumber, size_t size = DEFAULT_SHARED_MEM_SIZE);
    virtual ~CBinaryAddonSharedMemory();

    bool LoggedIn() const override { return m_LoggedIn; }
    void SendMessage(const std::stringstream& in, std::stringstream& ret) override;

    const int m_randomConnectionNumber;

    const size_t m_sharedMemSize;

  protected:
    virtual void* Process(void);

    virtual bool Lock_AddonToKodi_Kodi() = 0;
    virtual void Unlock_AddonToKodi_Kodi() = 0;
    virtual void Unlock_AddonToKodi_Addon() = 0;

    virtual bool Lock_KodiToAddon_Kodi() = 0;
    virtual void Unlock_KodiToAddon_Kodi() = 0;
    virtual void Unlock_KodiToAddon_Addon() = 0;

    apiShareData* m_sharedMem_AddonToKodi;
    apiShareData* m_sharedMem_KodiToAddon;
    bool m_LoggedIn;
  };

} /* namespace ADDON */
