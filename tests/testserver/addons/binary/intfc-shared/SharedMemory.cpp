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

#include "SharedMemory.h"
#include "addons/binary/BinaryAddon.h"
#include "utils/log.h"

#include "kodi/definitions.h"

#include <msgpack.hpp>

namespace ADDON
{

CBinaryAddonSharedMemory::CBinaryAddonSharedMemory(CBinaryAddon* addon, int randNumber, size_t size /* = DEFAULT_SHARED_MEM_SIZE*/)
  : IAddonInterface(addon),
    m_randomConnectionNumber(randNumber),        // Connection number used here and on add-on to identify shared memory
    m_sharedMemSize(size),                       // The memory size used for shared place of Kodi and add-on
    m_sharedMem_AddonToKodi(nullptr),            // Shared memory pointer used for Communication from Add-on to Kodi
    m_sharedMem_KodiToAddon(nullptr),            // Shared memory pointer used for Communication from Kodi to Add-on
    m_LoggedIn(false)                            // LockedIn value, used to prevent not wanted locks on operaion thread
{
}

CBinaryAddonSharedMemory::~CBinaryAddonSharedMemory()
{
  StopThread();
}

void CBinaryAddonSharedMemory::SendMessage(const std::stringstream& in, std::stringstream& ret)
{
  if (!m_LoggedIn)
    return;

  ///TODO add support for bigger streams
  int size = in.str().size();
  m_sharedMem_KodiToAddon->bigger = size > DEFAULT_SHARED_MEM_ARRAY_SIZE;
  m_sharedMem_KodiToAddon->size = m_sharedMem_KodiToAddon->bigger ? DEFAULT_SHARED_MEM_ARRAY_SIZE : size;
  memcpy(m_sharedMem_KodiToAddon->data, in.str().data(), m_sharedMem_KodiToAddon->size);
  Unlock_KodiToAddon_Addon();
  Lock_KodiToAddon_Kodi();
  ret.write(m_sharedMem_KodiToAddon->data, m_sharedMem_KodiToAddon->size);
}

void* CBinaryAddonSharedMemory::Process(void)
{
  std::stringstream ret;

  while (!IsStopped() && m_LoggedIn)
  {
    if (Lock_AddonToKodi_Kodi())
    {
      if (IsStopped() || !m_LoggedIn)
      {
        break;
      }

      std::size_t offset = 0;
      msgpack::unpacked ident = msgpack::unpack(m_sharedMem_AddonToKodi->data, m_sharedMem_AddonToKodi->size, offset);
      stream_msg_ident id = ident.get().as<decltype(id)>();
      int group = std::get<1>(id);
      int func = std::get<2>(id);

      switch (func)
      {
        case funcIdKodi::kodi_unregister:
        {
          Unlock_AddonToKodi_Addon();
          CLog::Log(LOGDEBUG, "CBinaryAddonSharedMemory::%s: Addon '%s' sended stop signal and handling becomes closed", __FUNCTION__, GetAddon()->ID().c_str());
          Destroy();
          return nullptr;
        }
        default:
        {
          auto input = msgpack::unpack(m_sharedMem_AddonToKodi->data, m_sharedMem_AddonToKodi->size, offset);
          if (!GetAddon()->HandleMessage(group, func, input, ret))
          {
            Unlock_AddonToKodi_Addon();
            continue;
          }
        }
      }

      m_sharedMem_AddonToKodi->size = ret.str().size();
      memcpy(m_sharedMem_AddonToKodi->data, ret.str().data(), m_sharedMem_AddonToKodi->size);
    }

    Unlock_AddonToKodi_Addon();
  }

  return nullptr;
}

} /* namespace ADDON */
