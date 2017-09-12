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

#include "Addon.h"
#include "IAddonInterface.h"
#include "tools.h"
#if (defined TARGET_WINDOWS)
#  include "SharedMemoryWindows.h"
#elif (defined TARGET_POSIX)
#  include "SharedMemoryPosix.h"
#endif

#include <p8-platform/util/timeutils.h>
#include <msgpack.hpp>

CAddon CAddon::m_main;
const std::string CAddon::m_uuid = CreateUUID();

CAddon::CAddon()
  : m_interface(nullptr),
    m_socket(nullptr),
    m_isLocal(true),
    m_usedRand(-1)
{
}

CAddon::~CAddon()
{
  Disconnect();
  delete m_socket;
}

bool CAddon::Connect(addon_properties& props)
{
  ssize_t writeResult;

  Disconnect();

  if (props.id.empty())
  {
    fprintf(stderr, "CAddon::%s: Started without present ID\n", __FUNCTION__);
    return false;
  }

  m_props = props;

  uint64_t iNow = P8PLATFORM::GetTimeMs();
  uint64_t iTarget = iNow + KODI_API_CONNECTION_TIMEOUT * 1000;

  if (!m_socket)
    m_socket = new P8PLATFORM::CTcpConnection("localhost", KODI_API_CONNECTION_PORT);

  while (!m_socket->IsOpen() && iNow < iTarget)
  {
    if (!m_socket->Open(iTarget - iNow))
      P8PLATFORM::CEvent::Sleep(100);
    iNow = P8PLATFORM::GetTimeMs();
  }

  if (!m_socket->IsOpen())
  {
    fprintf(stderr, "CAddon::%s: Failed to open net stream socket (%s)\n", __FUNCTION__, m_socket->GetError().c_str());
    return false;
  }

#if (defined TARGET_WINDOWS)
  uint64_t pid = (unit64_t)_getpid();
#elif (defined TARGET_POSIX)
  uint64_t pid = (uint64_t)getpid();
#endif

  stream_msg_kodi_register login;
  login["uuid"] = m_uuid;
  login["id"] = m_props.id;
  login["type"] = m_props.type;
  login["version"] = m_props.version;
  login["name"] = m_props.name;
  login["license"] = m_props.license;
  login["summary"] = m_props.summary;
  login["description"] = m_props.description;
  login["path"] = m_props.path;
  login["libname"] = m_props.libname;
  login["author"] = m_props.author;
  login["source"] = m_props.source;
  login["icon"] = m_props.icon;
  login["disclaimer"] = m_props.disclaimer;
  login["changelog"] = m_props.changelog;
  login["fanart"] = m_props.fanart;
  login["independent"] = m_props.independent ? "true" : "false";
  login["pid"] = std::to_string(pid);

  std::stringstream in;
  try
  {
    msgpack::pack(in, stream_msg_ident("kodi_register", groupId::grStart, funcIdKodi::kodi_register));
    msgpack::pack(in, stream_msg_kodi_register(login));
  }
  catch (...)
  {
    fprintf(stderr, "CAddon::%s: msgpack::pack generated exception fault and app becomes closed!\n", __FUNCTION__);
    exit(1);
  }

  u_int32_t size = htonl(in.str().size());
  writeResult = m_socket->Write(&size, sizeof(size)); // Write packet size
  if (writeResult == sizeof(size))
    writeResult = m_socket->Write(const_cast<char*>(in.str().data()), in.str().size()); // Write packet
  if (writeResult != in.str().size())
  {
    fprintf(stderr, "CAddon::%s: Failed to write packet (%s), bytes written: %ld of total: %ld\n",
              __FUNCTION__, m_socket->GetError().c_str(), writeResult, in.str().size());
    return false;
  }

  if (!readData(reinterpret_cast<char*>(&size), sizeof(size), 1000))
  {
    fprintf(stderr, "CAddon::%s: Failed to read size packet (%s)\n", __FUNCTION__, m_socket->GetError().c_str());
    return false;
  }
  size = ntohl(size);

  char mem[100];
  if (!readData(mem, size, 1000))
  {
    fprintf(stderr, "CAddon::%s: Failed to read data packet (%s)\n", __FUNCTION__, m_socket->GetError().c_str());
    return false;
  }

  std::size_t offset = 0;
  bool ret = false;
  try
  {
    ret = msgpack::unpack(mem, size, offset).get().as<decltype(ret)>();
    m_usedRand = msgpack::unpack(mem, size, offset).get().as<decltype(m_usedRand)>();
    m_isLocal = msgpack::unpack(mem, size, offset).get().as<decltype(m_isLocal)>();
  }
  catch (...)
  {
    fprintf(stderr, "CAddon::%s: msgpack::unpack generated exception fault and app becomes closed!\n", __FUNCTION__);
    exit(1);
  }

  if (!ret)
  {
    fprintf(stderr, "CAddon::%s: Failed to create communication interface on Kodi side\n", __FUNCTION__);
    return false;
  }

  if (m_isLocal)
  {
#if (defined TARGET_WINDOWS)
    m_interface = new CBinaryAddonSharedMemoryWindows(m_usedRand);
#elif (defined TARGET_POSIX)
    m_interface = new CBinaryAddonSharedMemoryPosix(m_usedRand);
#endif
  }
  else
  {
    fprintf(stderr, "CAddon::%s: Other as shared memory not supported\n", __FUNCTION__);
    return false;
  }

  if (!m_interface || !m_interface->Create())
  {
    fprintf(stderr, "CAddon::%s: Failed to create communication interface on addon side\n", __FUNCTION__);
    return false;
  }

  return true;
}

void CAddon::SendMessage(const std::stringstream& in, std::stringstream& ret)
{
  if (m_interface)
    m_interface->SendMessage(in, ret);
}

void CAddon::Disconnect()
{
  if (m_interface)
  {
    std::stringstream in;
    std::stringstream out;
    msgpack::pack(in, stream_msg_ident("kodi_unregister", groupId::grStart, funcIdKodi::kodi_unregister));
    msgpack::pack(in, true);
    m_interface->SendMessage(in, out);
    m_interface->Destroy();
    delete m_interface;
    m_interface = nullptr;
  }

  if (m_socket)
  {
    if (m_socket->IsOpen())
      m_socket->Close();
  }
}

bool CAddon::readData(char* buffer, int totalBytes, int timeout)
{
  int bytesRead = m_socket->Read(buffer, totalBytes, timeout);
  if (bytesRead == totalBytes)
  {
    return true;
  }
  else if (m_socket->GetErrorNumber() == ETIMEDOUT && bytesRead > 0)
  {
    // we did read something. try to finish the read
    bytesRead += m_socket->Read(buffer+bytesRead, totalBytes-bytesRead, timeout);
    if (bytesRead == totalBytes)
      return true;
  }
  else if (m_socket->GetErrorNumber() == ETIMEDOUT)
  {
    return false;
  }

  Disconnect();
  return false;
}
