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

#include "BinaryAddon.h"
#include "IAddonInterface.h"
#if (defined TARGET_WINDOWS)
#  include "intfc-shared/SharedMemoryWindows.h"
#elif (defined TARGET_POSIX)
#  include "intfc-shared/SharedMemoryPosix.h"
#endif
#include "tools.h"
#include "utils/log.h"

#include <stdlib.h>
#include <time.h>

using namespace ADDON;

CBinaryAddon::CBinaryAddon(const std::string& id)
  : m_id(id),
    m_addonInterface(nullptr),
    m_independent(false),
    m_addonPID(0)
{
  srand(clock());
  m_usedRand = std::rand();
}

CBinaryAddon::~CBinaryAddon()
{
  delete m_addonInterface;
}

bool CBinaryAddon::IsActive() const
{
  return m_addonInterface ? m_addonInterface->LoggedIn() : false;
}

bool CBinaryAddon::Create(bool independent, uint64_t addonPID)
{
  m_independent = independent;
  m_addonPID = addonPID;

#if (defined TARGET_WINDOWS)
  m_addonInterface = new CBinaryAddonSharedMemoryWindows(this, m_usedRand);
#elif (defined TARGET_POSIX)
  m_addonInterface = new CBinaryAddonSharedMemoryPosix(this, m_usedRand);
#endif
  return m_addonInterface->Create();
}

bool CBinaryAddon::HandleMessage(int group, int func, const msgpack::unpacked& in, std::stringstream& out)
{
  switch (group)
  {
    case groupId::grKodi:
      return HandleMessageGroupKodi(func, in, out);
    case groupId::grKodiGUI:
      break;
    case groupId::grKodiNet:
      break;
    case groupId::grKodiVFS:
      break;
    default:
      CLog::Log(LOGERROR, "CBinaryAddon::%s: addon called with unknown group id '%i' with function '%i'", __FUNCTION__, group, func);
      return false;
  }

  return true;
}

bool CBinaryAddon::HandleMessageGroupKodi(int func, const msgpack::unpacked& in, std::stringstream& out)
{
  switch (func)
  {
    case funcIdKodi::kodi_log:
    {
      stream_msg_kodi_log t = in.get().as<decltype(t)>();
      fprintf(stderr, "--------- level %i - %s\n", t.first, t.second.c_str());
      msgpack::pack(out, bool(true));
      break;
    }
    default:
      CLog::Log(LOGERROR, "CBinaryAddon::%s: addon called with unknown function id '%i' on group 'kodi'", __FUNCTION__, func);
      return false;
  }

  return true;
}
