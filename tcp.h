#ifndef TCP_H
#define TCP_H
#include <iostream>
#include <string>
//if Linux
#ifdef __linux__
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
//if Windows
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif


using namespace std;

namespace cppsock{
#ifdef _WIN32
    WSADATA wsaData;
    bool WSAStarted = false;
    int WSAnumInstances = 0;
    void WSAManage(){
        if(WSAnumInstances == 0 && WSAStarted){
            WSACleanup();
            WSAStarted = false;
        }
        else if(WSAnumInstances > 0 && !WSAStarted){
            if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
                cout << "WSAStartup failed" << endl;
                exit(1);
            }
            WSAStarted = true;
        }
    }
#endif

    class TCPClient {
        private:
            #ifdef __linux__
            int sock;

            #endif
            #ifdef _WIN32
            SOCKET sock = INVALID_SOCKET;
            #endif
            struct sockaddr_in server;
            char buffer[1024];
            string ip;
            string hostname;
            int port;
            bool connected;
        public:
            TCPClient(string ip, int port);
            ~TCPClient();
            bool sock_connect();
            bool sock_send(string msg);
            string sock_receive();
            bool disconnect();
    };
    class TCPServer {
        private:
            #ifdef __linux__
            int sock;

            #endif
            #ifdef _WIN32
            WSADATA wsaData;
            SOCKET sock = INVALID_SOCKET;
            #endif
            struct sockaddr_in server;
            char buffer[1024];
            int port;
            bool connected;
        public:
            TCPServer(int port);
            ~TCPServer();
            bool sock_listen();
            bool sock_accept();
            bool sock_send(string msg);
            string sock_receive();
            bool disconnect();
    };
}
#endif // TCP_H
