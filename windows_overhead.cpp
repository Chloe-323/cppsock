#include "windows_overhead.h"
#ifdef _WIN32

WSADATA wsaData;
bool WSAStarted = false;
int WSAnumInstances = 0;
void cppsock::WSAManage(){
    if(WSAnumInstances == 0 && WSAStarted){
        WSACleanup();
        WSAStarted = false;
    }
    else if(WSAnumInstances > 0 && !WSAStarted){
        if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
            exit(1);
        }
        WSAStarted = true;
    }
}
#endif
