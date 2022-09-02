#ifndef TCP_H
#define TCP_H
#define BUF_SIZE 1024
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
    inline WSADATA wsaData;
    inline bool WSAStarted = false;
    inline int WSAnumInstances = 0;
    void WSAManage();
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
            char buffer[BUF_SIZE];
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
            SOCKET sock = INVALID_SOCKET;
            #endif
            struct sockaddr_in server;
            char buffer[BUF_SIZE];
            int port = 0;
            bool connected;
        public:
            TCPServer(int _port);
            ~TCPServer();
            bool sock_listen();
            bool sock_accept();
            bool sock_send(string msg);
            string sock_receive();
            bool disconnect();
    };
}
#endif // TCP_H
