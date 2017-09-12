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

#include "BinaryAddonManager.h"
#include "BinaryAddon.h"
#include "tools.h"

#include "threads/SingleLock.h"
#include "utils/log.h"
#include "utils/JobManager.h"
#include "kodi/definitions.h"
#include "network/Network.h"

#include <msgpack.hpp>
#include <sstream>
#if (defined TARGET_POSIX)
#include <signal.h>
#include "linux/XTimeUtils.h"
#endif

using namespace ADDON;

class CExeAddonOpenJob : public CJob
{
public:
  CExeAddonOpenJob(int socket, struct sockaddr_in sin)
  : m_socket(socket), m_sin(std::move(sin)) {}
  ~CExeAddonOpenJob() override = default;
  const char *GetType() const override { return "ExeAddonOpenJob"; }

  bool DoWork() override;

  const BinaryAddonPtr& GetCreatedAddon() { return m_addon; }

private:
  ssize_t read(void *buffer, size_t size);
  ssize_t write(const void *buffer, size_t size, bool more_data = false);

  int m_socket;
  struct sockaddr_in m_sin;
  BinaryAddonPtr m_addon;
};

bool CExeAddonOpenJob::DoWork(void)
{
  int val = 1;
  if (setsockopt(m_socket, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)) == SOCKET_ERROR)
  {
    CLog::Log(LOGERROR, "CExeAddonOpenJob::%s: Unable to set socket option: %d", __FUNCTION__, errno);
    return false;
  }

  uint32_t dataLength;
  if (!read(reinterpret_cast<uint32_t*>(&dataLength), sizeof(uint32_t)))
  {
    close(m_socket);
    return false;
  }

  dataLength = ntohl(dataLength);
  if (dataLength > 200000 || dataLength == 0) // a random sanity limit
  {
    CLog::Log(LOGERROR, "CExeAddonOpenJob::%s: invalid data Length %i!", __FUNCTION__, dataLength);
    close(m_socket);
    return false;
  }

  char* data = nullptr;
  try
  {
    data = static_cast<char*>(malloc(dataLength));
  }
  catch (const std::bad_alloc &)
  {
    CLog::Log(LOGERROR, "CExeAddonOpenJob::%s: data buffer error", __FUNCTION__);
    close(m_socket);
    return false;
  }

  if (!read(data, dataLength))
  {
    CLog::Log(LOGERROR, "CExeAddonOpenJob::%s: Could not read data", __FUNCTION__);
    free(data);
    close(m_socket);
    return false;
  }

  std::size_t offset = 0;
  auto und = msgpack::unpack(data, dataLength, offset);
  stream_msg_ident ident = und.get().as<decltype(ident)>();
  if (std::get<1>(ident) != groupId::grStart)
  {
    CLog::Log(LOGERROR, "CExeAddonOpenJob::%s: called with invalid start command '%s'", __FUNCTION__, std::get<0>(ident).c_str());
    free(data);
    close(m_socket);
    return false;
  }

  und = msgpack::unpack(data, dataLength, offset);
  stream_msg_kodi_register props = und.get().as<decltype(props)>();
  bool independent = (props["independent"] == "true") ? true : false;
  uint32_t pid = std::stoul(props["pid"], nullptr, 0);

  m_addon = std::make_shared<CBinaryAddon>(props["id"]);
  bool ret = m_addon->Create(independent, pid);

  std::stringstream out;
  msgpack::pack(out, ret);
  msgpack::pack(out, m_addon->UsedRand());
  msgpack::pack(out, true); // localhost

  uint32_t size = htonl(out.str().size());
  write(&size, sizeof(uint32_t));
  write(out.str().data(), out.str().size());

  free(data);
  close(m_socket);
  return ret;
}

ssize_t CExeAddonOpenJob::write(const void* buffer, size_t size, bool more_data)
{
  if(m_socket == -1)
    return -1;

  ssize_t written = static_cast<ssize_t>(size);
  const unsigned char *ptr = reinterpret_cast<const unsigned char*>(buffer);

  while (size > 0)
  {
    ssize_t p = send(m_socket, ptr, size, (more_data ? MSG_MORE : 0));
    if (p <= 0)
    {
      if (errno == EINTR || errno == EAGAIN)
      {
        CLog::Log(LOGDEBUG, "CExeAddonOpenJob::%s: EINTR during write(), retrying", __FUNCTION__);
        continue;
      }
      else if (errno != EPIPE)
      {
        CLog::Log(LOGERROR, "CExeAddonOpenJob::%s: error '%i'", __FUNCTION__, errno);
      }
      return p;
    }

    ptr += p;
    size -= p;
  }

  return written;
}

ssize_t CExeAddonOpenJob::read(void* buffer, size_t size)
{
  if (m_socket == -1)
    return -1;

  int retryCounter = 0;
  ssize_t missing = static_cast<ssize_t>(size);
  unsigned char *ptr = reinterpret_cast<unsigned char*>(buffer);

  while (missing > 0)
  {
    ssize_t p = recv(m_socket, ptr, missing, MSG_WAITALL);
    if (p < 0)
    {
      if (retryCounter < 10 && (errno == EINTR || errno == EAGAIN))
      {
        CLog::Log(LOGDEBUG, "CExeAddonOpenJob::%s: EINTR/EAGAIN during read(), retrying", __FUNCTION__);
        retryCounter++;
        continue;
      }
      CLog::Log(LOGERROR, "CExeAddonOpenJob::%s: error '%i' at %d/%d", __FUNCTION__, errno, size-missing, size);
      return 0;
    }
    else if (p == 0)
    {
      CLog::Log(LOGINFO, "CExeAddonOpenJob::%s: eof, connection closed '%i'", __FUNCTION__, errno);
      return 0;
    }

    retryCounter = 0;
    ptr += p;
    missing -= p;
  }

  return size;
}

class CExeAddonCloseJob : public CJob
{
public:
  CExeAddonCloseJob(BinaryAddonPtr addon)
  : m_addon(addon) { }
  ~CExeAddonCloseJob() override = default;
  const char *GetType() const override { return "ExeAddonCloseJob"; }

  bool DoWork() override;

  const BinaryAddonPtr& GetAddon() { return m_addon; }

private:
  BinaryAddonPtr m_addon;
};

bool CExeAddonCloseJob::DoWork()
{
  bool forcedDelete = false;
  bool present = CBinaryAddonManager::CheckPresenceOfProcess(m_addon->AddonPID());
  bool active = m_addon->IsActive();

  if (!present && active)
  {
    forcedDelete = true;
    CLog::Log(LOGINFO, "Binary AddOn: Enabled addon '%s' with ID %lu marked as present but not running anymore, forcing delete",
              m_addon->ID().c_str(),
              m_addon->AddonPID());
  }
  else if (!active && !m_addon->IsIndependent() && present)
  {
    Sleep(2000);
    if (CBinaryAddonManager::CheckPresenceOfProcess(m_addon->AddonPID()))
    {
      CLog::Log(LOGINFO, "Binary AddOn: Enabled addon '%s' with ID %lu stopped interface and not independent, destroying app",
                m_addon->ID().c_str(),
                m_addon->AddonPID());
      CBinaryAddonManager::KillOfProcess(m_addon->AddonPID());
    }
  }

  return forcedDelete || !active;
}


CBinaryAddonManager::CBinaryAddonManager()
  : m_serverFD(INVALID_SOCKET),
    m_initialized(false)
{

}

CBinaryAddonManager::~CBinaryAddonManager()
{
  StopManager();
}

bool CBinaryAddonManager::StartManager(int port)
{
  m_port = port;
  m_serverFD = CreateTCPServerSocket(m_port, true, 10, "BINARYADDON");
  if (m_serverFD == INVALID_SOCKET)
    return false;

  CreateThread();
  return true;
}

void CBinaryAddonManager::StopManager()
{
  StopThread();

  if (m_serverFD != INVALID_SOCKET)
  {
    shutdown(m_serverFD, SHUT_RDWR);
    close(m_serverFD);
    m_serverFD = INVALID_SOCKET;
  }
}

#define PROCESS_KILL_COUNTDOWN 5*1000 // seconds
void* CBinaryAddonManager::Process(void)
{
  fd_set fds;
  struct timeval tv;
  P8PLATFORM::CTimeout killTimeout(PROCESS_KILL_COUNTDOWN);

  m_initialized = true;
  while (!IsStopped())
  {
    if (killTimeout.TimeLeft() == 0)
    {
      killTimeout.Init(PROCESS_KILL_COUNTDOWN);

      CSingleLock lock(m_critSection);
      // remove disconnected clients
      for (const auto& addon : m_addons)
      {
        bool present = CheckPresenceOfProcess(addon->AddonPID());
        if ((!addon->IsActive() && !addon->IsIndependent()) || !present)
        {
          CJobManager::GetInstance().AddJob(new CExeAddonCloseJob(addon), this);
        }
      }
    }

    FD_ZERO(&fds);
    FD_SET(m_serverFD, &fds);

    tv.tv_sec = 0;
    tv.tv_usec = 250*1000;

    int res = select(m_serverFD + 1, &fds, nullptr, nullptr, &tv);
    if (res < 0)
    {
      CLog::Log(LOGERROR, "failed during select");
      continue;
    }
    else if (res > 0)
    {
      struct sockaddr_in sin;
      socklen_t len = sizeof(sin);
      int socket = accept(m_serverFD, reinterpret_cast<struct sockaddr*>(&sin), &len);
      if (socket != INVALID_SOCKET)
      {
        CJobManager::GetInstance().AddJob(new CExeAddonOpenJob(socket, std::move(sin)), this);
      }
      else
      {
        CLog::Log(LOGERROR, "CBinaryAddonManager::%s: Accept of new connection failed: %d", __FUNCTION__, errno);
        if (EBADF == errno)
        {
          Sleep(1000);
          StartManager(m_port);
          break;
        }
      }
    }
  }

  for (const auto addon : m_addons)
  {
    if (!addon->IsIndependent() &&
        CheckPresenceOfProcess(addon->AddonPID()))
    {
      KillOfProcess(addon->AddonPID());
    }
  }

  m_initialized = false;
  return nullptr;
}

void CBinaryAddonManager::OnJobComplete(unsigned int jobID, bool success, CJob *job)
{
  if (job && success)
  {
    if (strcmp(job->GetType(), "ExeAddonOpenJob") == 0)
    {
      CExeAddonOpenJob *exeJob = dynamic_cast<CExeAddonOpenJob*>(job);
      BinaryAddonPtr addon = exeJob->GetCreatedAddon();
      CSingleLock lock(m_critSection);
      m_addons.push_back(addon);
    }
    else if (strcmp(job->GetType(), "ExeAddonCloseJob") == 0)
    {
      CExeAddonCloseJob *exeJob = dynamic_cast<CExeAddonCloseJob*>(job);

      std::string id = exeJob->GetAddon()->ID();
      CSingleLock lock(m_critSection);

      auto itAddon = std::find_if(m_addons.begin(), m_addons.end(),
        [&id](const BinaryAddonPtr& addon)
        {
          return addon->ID() == id;
        });

      if (itAddon != m_addons.end())
      {
        m_addons.erase(itAddon);
      }
    }
  }
}

bool CBinaryAddonManager::KillOfProcess(uint64_t processId)
{
  fprintf(stderr, "KillOfProcess\n");
#if (defined TARGET_WINDOWS)
  HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
  if (hProcess == nullptr)
      return false;

  return TerminateProcess(hProcess, 1);
#elif (defined TARGET_POSIX)
  return (kill(processId, SIGTERM) == 0) ? true : false;
#endif
}

bool CBinaryAddonManager::CheckPresenceOfProcess(uint64_t processId)
{
#if (defined TARGET_WINDOWS)
  HANDLE hProcess = OpenProcess(SYNCHRONIZE, FALSE, processId);
  DWORD ret = WaitForSingleObject(hProcess, 0);
  CloseHandle(hProcess);
  return ret == WAIT_TIMEOUT;
#elif (defined TARGET_POSIX)
  return (kill(processId, 0) == 0) ? true : false;
#endif
}
