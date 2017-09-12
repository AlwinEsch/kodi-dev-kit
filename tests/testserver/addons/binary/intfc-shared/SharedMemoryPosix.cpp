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

#if (defined TARGET_POSIX)

#include "SharedMemoryPosix.h"
#include "addons/binary/tools.h"
#include "utils/log.h"

#include <sys/ipc.h>
#include <sys/shm.h>

namespace ADDON
{

CBinaryAddonSharedMemoryPosix::CBinaryAddonSharedMemoryPosix(CBinaryAddon* addon, int randNumber, size_t size /* = DEFAULT_SHARED_MEM_SIZE*/)
 : CBinaryAddonSharedMemory(addon, randNumber, size),
   m_shmId_FromAddonToKodi(-1),
   m_shmId_FromKodiToAddon(-1)
{

}

CBinaryAddonSharedMemoryPosix::~CBinaryAddonSharedMemoryPosix()
{
  Destroy();
}

bool CBinaryAddonSharedMemoryPosix::Create()
{
  /*
   * Interface from Addon to Kodi
   */
  if ((m_shmId_FromAddonToKodi = shmget(m_randomConnectionNumber, m_sharedMemSize, IPC_CREAT | 0666)) < 0)
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Request of interface 'Add-on to Kodi' shared memory failed with error '%i': %s",
                __FUNCTION__, errno, strerror(errno));
    return false;
  }

  if ((m_sharedMem_AddonToKodi = static_cast<apiShareData*>(shmat(m_shmId_FromAddonToKodi, nullptr, 0))) == reinterpret_cast<apiShareData*>(-1))
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Connect of interface 'Add-on to Kodi' shared memory failed with error '%i': %s",
                __FUNCTION__, errno, strerror(errno));
    return false;
  }

  if (sem_init(&m_sharedMem_AddonToKodi->shmSegmentToKodi, 1, 0) != 0)
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Creation of interface 'Add-on to Kodi' Lock to Kodi failed with error '%i': %s",
                __FUNCTION__, errno, strerror(errno));
    return false;
  }

  if (sem_init(&m_sharedMem_AddonToKodi->shmSegmentToAddon, 1, 0) != 0)
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Creation of interface 'Add-on to Kodi' Lock to Add-on failed with error '%i': %s",
                __FUNCTION__, errno, strerror(errno));
    return false;
  }

  /*
   * Interface from Kodi to Addon
   */
  if ((m_shmId_FromKodiToAddon = shmget(m_randomConnectionNumber+1, m_sharedMemSize, IPC_CREAT | 0666)) < 0)
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Request of interface 'Kodi to Add-on' shared memory failed with error '%i': %s",
                __FUNCTION__, errno, strerror(errno));
    return false;
  }

  if ((m_sharedMem_KodiToAddon = static_cast<apiShareData*>(shmat(m_shmId_FromKodiToAddon, nullptr, 0))) == reinterpret_cast<apiShareData*>(-1))
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Connect of interface 'Kodi to Add-on' shared memory failed with error '%i': %s",
                __FUNCTION__, errno, strerror(errno));
    return false;
  }

  if (sem_init(&m_sharedMem_KodiToAddon->shmSegmentToKodi, 1, 0) != 0)
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Creation of interface 'Kodi to Add-on' Lock to Kodi failed with error '%i': %s",
                __FUNCTION__, errno, strerror(errno));
    return false;
  }

  if (sem_init(&m_sharedMem_KodiToAddon->shmSegmentToAddon, 1, 0) != 0)
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Creation of interface 'Kodi to Add-on' Lock to Add-on failed with error '%i': %s",
                __FUNCTION__, errno, strerror(errno));
    return false;
  }

  m_LoggedIn = true;
  CreateThread();

  return true;
}

void CBinaryAddonSharedMemoryPosix::Destroy()
{
  if (!m_LoggedIn)
    return;

  m_LoggedIn = false;

  if (m_sharedMem_AddonToKodi)
  {
    sem_post(&m_sharedMem_AddonToKodi->shmSegmentToKodi);
    sem_post(&m_sharedMem_AddonToKodi->shmSegmentToAddon);
  }
  if (m_sharedMem_KodiToAddon)
  {
    sem_post(&m_sharedMem_KodiToAddon->shmSegmentToKodi);
    sem_post(&m_sharedMem_KodiToAddon->shmSegmentToAddon);
  }

  /* freeing the reference to the semaphore */
  if (m_sharedMem_AddonToKodi)
  {
    usleep(1);
    sem_close(&m_sharedMem_AddonToKodi->shmSegmentToKodi);
    sem_close(&m_sharedMem_AddonToKodi->shmSegmentToAddon);

    if (shmdt(m_sharedMem_AddonToKodi) != 0)
      CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Detach of shared memory from Add-on failed with error '%i': %s",errno, strerror(errno));

    m_sharedMem_AddonToKodi = nullptr;
  }

  if (m_sharedMem_KodiToAddon)
  {
    usleep(1);
    sem_close(&m_sharedMem_KodiToAddon->shmSegmentToKodi);
    sem_close(&m_sharedMem_KodiToAddon->shmSegmentToAddon);

    if (shmdt(m_sharedMem_KodiToAddon) != 0)
      CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Detach of shared memory from Kodi failed with error '%i': %s",errno, strerror(errno));

    m_sharedMem_KodiToAddon = nullptr;
  }
}

bool CBinaryAddonSharedMemoryPosix::Lock_AddonToKodi_Kodi()
{
  int32_t err = sem_wait(&m_sharedMem_AddonToKodi->shmSegmentToKodi);
  if (err != 0)
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: LockAddon of interface 'Add-on to Kodi' failed with error '%i': %s", errno, strerror(errno));
    return false;
  }

  return true;
}

void CBinaryAddonSharedMemoryPosix::Unlock_AddonToKodi_Kodi()
{
  sem_post(&m_sharedMem_AddonToKodi->shmSegmentToAddon);
}

void CBinaryAddonSharedMemoryPosix::Unlock_AddonToKodi_Addon()
{
  sem_post(&m_sharedMem_AddonToKodi->shmSegmentToAddon);
}

bool CBinaryAddonSharedMemoryPosix::Lock_KodiToAddon_Kodi()
{
  int32_t err = sem_wait(&m_sharedMem_KodiToAddon->shmSegmentToKodi);
  if (err != 0)
  {
    CLog::Log(LOGERROR, "CBinaryAddonSharedMemoryPosix::%s: Lock Kodi of interface 'Kodi to Add-on' failed with error '%i': %s", errno, strerror(errno));
    return false;
  }

  return true;
}

void CBinaryAddonSharedMemoryPosix::Unlock_KodiToAddon_Kodi()
{
  sem_post(&m_sharedMem_KodiToAddon->shmSegmentToKodi);
}

void CBinaryAddonSharedMemoryPosix::Unlock_KodiToAddon_Addon()
{
  sem_post(&m_sharedMem_KodiToAddon->shmSegmentToAddon);
}

} /* namespace ADDON */

#endif /* (defined TARGET_POSIX) */
