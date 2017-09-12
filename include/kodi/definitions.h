#pragma once

#if (defined TARGET_POSIX)
#include <semaphore.h>
#endif
#include <string>
#include <unordered_map>

#ifndef SWIG

#define DEFAULT_SHARED_MEM_SIZE 10*1024
#define DEFAULT_SHARED_MEM_ARRAY_SIZE DEFAULT_SHARED_MEM_SIZE-(sizeof(uint32_t)*10)

const int KODI_API_CONNECTION_TIMEOUT = 3;
const int KODI_API_CONNECTION_PORT    = 34687;

typedef struct apiShareData
{
#if (defined TARGET_WINDOWS)
  HANDLE shmSegmentToAddon;
  HANDLE shmSegmentToKodi;
#elif (defined TARGET_POSIX)
  sem_t shmSegmentToAddon;
  sem_t shmSegmentToKodi;
#endif
  bool bigger;
  int size;
  char data[DEFAULT_SHARED_MEM_ARRAY_SIZE];
} apiShareData;


typedef enum groupId
{
  grStart = 0,
  grKodi = 1,
  grKodiGUI = 2,
  grKodiNet = 3,
  grKodiVFS = 4,
} groupId;

typedef enum funcIdKodi
{
  kodi_register = 1, /*! stream_msg_kodi_register */
  kodi_unregister = 2, /*! stream_msg_kodi_unregister */
  kodi_log = 1000, /*! stream_msg_kodi_log */

} funcIdKodi;

typedef enum funcIdAddon
{
  addon_get_status = 10,

} funcIdAddon;

typedef std::tuple<std::string, int, int> stream_msg_ident;
typedef std::unordered_map<std::string, std::string> stream_msg_kodi_register;
typedef std::unordered_map<std::string, std::string> stream_msg_kodi_unregister;
typedef std::pair<int, std::string> stream_msg_kodi_log;

#endif

typedef struct addon_properties
{
  std::string id;
  std::string type;
  std::string version;
  std::string name;
  std::string license;
  std::string summary;
  std::string description;
  std::string path;
  std::string libname;
  std::string author;
  std::string source;
  std::string icon;
  std::string disclaimer;
  std::string changelog;
  std::string fanart;
  bool independent;
} addon_properties;

