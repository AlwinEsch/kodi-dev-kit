#pragma once

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (~0)
#endif
#define SOCKET_ERROR (-1)

#define closesocket(s)  close(s)
