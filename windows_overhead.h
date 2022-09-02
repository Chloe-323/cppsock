#ifndef WINDOWS_OVERHEAD
#define WINDOWS_OVERHEAD
#include <winsock2.h>
#include <ws2tcpip.h>
namespace cppsock{
    extern WSADATA wsaData;
    extern bool WSAStarted;
    extern int WSAnumInstances;
    void WSAManage();
}
#endif //WINDOWS_OVERHEAD