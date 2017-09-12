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

#include "SharedMemoryPosix.h"

#if (defined TARGET_POSIX)

#include "tools.h"

#include <string.h>
#include <sys/shm.h>

CBinaryAddonSharedMemoryPosix::CBinaryAddonSharedMemoryPosix(int randomConnectionNumber, size_t size /* = DEFAULT_SHARED_MEM_SIZE*/)
 : CBinaryAddonSharedMemory(randomConnectionNumber, size),
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
  if ((m_shmId_FromAddonToKodi = shmget(m_randomConnectionNumber, m_sharedMem_Size, IPC_CREAT | 0666)) < 0)
  {
    fprintf(stderr, "Binary AddOn: Request of interface 'Add-on to Kodi (id %i)' shared memory (size %lu) failed with error '%i': %s\n",
                  m_randomConnectionNumber, m_sharedMem_Size, errno, SystemErrorString(errno).c_str());
    return false;
  }

  if ((m_sharedMem_AddonToKodi = static_cast<apiShareData*>(shmat(m_shmId_FromAddonToKodi, nullptr, 0))) == reinterpret_cast<apiShareData*>(-1))
  {
    fprintf(stderr, "Binary AddOn: Connect of interface 'Add-on to Kodi' shared memory failed with error '%i': %s\n",
                  errno, SystemErrorString(errno).c_str());
    return false;
  }

  /*
   * Interface from Kodi to Addon
   */
  if ((m_shmId_FromKodiToAddon = shmget(m_randomConnectionNumber+1, m_sharedMem_Size, IPC_CREAT | 0666)) < 0)
  {
    fprintf(stderr, "Binary AddOn: Request of interface 'Kodi to Add-on (id %i)' shared memory (size %lu) failed with error '%i': %s\n",
                  m_randomConnectionNumber+1, m_sharedMem_Size, errno, SystemErrorString(errno).c_str());
    return false;
  }

  if ((m_sharedMem_KodiToAddon = static_cast<apiShareData*>(shmat(m_shmId_FromKodiToAddon, nullptr, 0))) == reinterpret_cast<apiShareData*>(-1))
  {
    fprintf(stderr, "Binary AddOn: Connect of interface 'Kodi to Add-on' shared memory failed with error '%i': %s\n",
                  errno, SystemErrorString(errno).c_str());
    return false;
  }

  m_loggedIn = true;
  CreateThread();

  return true;
}

void CBinaryAddonSharedMemoryPosix::Destroy()
{
  m_loggedIn = false;

  if (m_sharedMem_KodiToAddon)
  {
    sem_post(&m_sharedMem_KodiToAddon->shmSegmentToKodi);
    sem_post(&m_sharedMem_KodiToAddon->shmSegmentToAddon);
  }

  StopThread();

  if (m_sharedMem_AddonToKodi != nullptr)
  {
    if (shmdt(m_sharedMem_AddonToKodi) != 0)
      fprintf(stderr, "Binary AddOn: Detach of shared memory 'Add-on to Kodi' failed with error '%i': %s\n",
                    errno, SystemErrorString(errno).c_str());
    m_sharedMem_AddonToKodi = nullptr;
  }

  if (m_sharedMem_KodiToAddon != nullptr)
  {
    if (shmdt(m_sharedMem_KodiToAddon) != 0)
      fprintf(stderr, "Binary AddOn: Detach of shared memory 'Kodi to Add-on' failed with error '%i': %s\n",
                    errno, SystemErrorString(errno).c_str());
    m_sharedMem_KodiToAddon = nullptr;
  }
}

void CBinaryAddonSharedMemoryPosix::Unlock_AddonToKodi_Kodi()
{
  sem_post(&m_sharedMem_AddonToKodi->shmSegmentToKodi);
}

bool CBinaryAddonSharedMemoryPosix::Lock_AddonToKodi_Addon()
{
  int32_t err = sem_wait(&m_sharedMem_AddonToKodi->shmSegmentToAddon);
  if (err != 0)
  {
    fprintf(stderr, "Binary AddOn: LockAddon of interface 'Add-on to Kodi' failed with error '%i': %s\n",
                  errno, SystemErrorString(errno).c_str());
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

bool CBinaryAddonSharedMemoryPosix::Lock_KodiToAddon_Addon()
{
  int32_t err = sem_wait(&m_sharedMem_KodiToAddon->shmSegmentToAddon);
  if (err != 0)
  {
    fprintf(stderr, "Binary AddOn: LockAddon of interface 'Kodi to Add-on' failed with error '%i': %s\n",
                  errno, SystemErrorString(errno).c_str());
    return false;
  }

  return true;
}

#endif /* (defined TARGET_POSIX) */
