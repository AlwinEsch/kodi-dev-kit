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

#include "SharedMemory.h"

#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <msgpack.hpp>

CBinaryAddonSharedMemory::CBinaryAddonSharedMemory(int randomConnectionNumber, size_t size /* = DEFAULT_SHARED_MEM_SIZE*/)
  : m_sharedMem_AddonToKodi(nullptr),
    m_sharedMem_KodiToAddon(nullptr),
    m_randomConnectionNumber(randomConnectionNumber == -1 ? std::rand() : randomConnectionNumber),
    m_sharedMem_Size(size),
    m_loggedIn(false)
{

}

void CBinaryAddonSharedMemory::SendMessage(const std::stringstream& in, std::stringstream& ret)
{
  ///TODO add support for bigger streams
  int size = in.str().size();
  m_sharedMem_AddonToKodi->bigger = size > DEFAULT_SHARED_MEM_ARRAY_SIZE;
  m_sharedMem_AddonToKodi->size = m_sharedMem_AddonToKodi->bigger ? DEFAULT_SHARED_MEM_ARRAY_SIZE : size;
  memcpy(m_sharedMem_AddonToKodi->data, in.str().data(), m_sharedMem_AddonToKodi->size);
  Unlock_AddonToKodi_Kodi();
  Lock_AddonToKodi_Addon();
  ret.write(m_sharedMem_AddonToKodi->data, m_sharedMem_AddonToKodi->size);
}

void* CBinaryAddonSharedMemory::Process(void)
{
  std::stringstream ret;

  while (!IsStopped() && m_loggedIn)
  {
    if (Lock_KodiToAddon_Addon())
    {
      if (IsStopped() || !m_loggedIn)
        break;

      std::size_t offset = 0;
      auto und = msgpack::unpack(m_sharedMem_AddonToKodi->data, m_sharedMem_AddonToKodi->size, offset);
      std::pair<std::string, int> id = und.get().as<decltype(id)>();

      switch (id.second)
      {
        case funcIdAddon::addon_get_status:
        {
          ret.clear();
          bool status = true;
          msgpack::pack(ret, status);
          m_sharedMem_AddonToKodi->size = ret.str().size();
          memcpy(m_sharedMem_AddonToKodi->data, ret.str().data(), m_sharedMem_AddonToKodi->size);
          break;
        }
        default:
          break;
      }
    }
    Unlock_KodiToAddon_Kodi();
  }

  return nullptr;
}
