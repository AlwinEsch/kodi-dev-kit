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

#include "BinaryAddon.h"

#include "threads/CriticalSection.h"
#include "threads/Thread.h"
#include "utils/Job.h"

#include <list>
#include <set>
#include <kodi/definitions.h>

struct sockaddr_in;

namespace ADDON
{

  class CBinaryAddonManager : protected CThread, public IJobCallback
  {
  public:
    CBinaryAddonManager();
    ~CBinaryAddonManager() override;

    bool StartManager(int port = KODI_API_CONNECTION_PORT);
    void StopManager();

    // implementation of IJobCallback
    void OnJobComplete(unsigned int jobID, bool success, CJob *job) override;

    static bool CheckPresenceOfProcess(uint64_t processId);
    static bool KillOfProcess(uint64_t processId);

  protected:
    void* Process(void) override;

  private:
    CCriticalSection m_critSection;
    std::list<BinaryAddonPtr> m_addons;
    int m_serverFD;
    int m_port;
    bool m_initialized;
  };

}
