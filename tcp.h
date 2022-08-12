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


class TCPClient {
    private:
        #ifdef __linux__
        int sock;
        struct sockaddr_in server;
        #endif
        #ifdef _WIN32
        WSADATA wsaData; //TODO: a way to make sure we don't initialize twice with multiple instances?'
        struct addrinfo *result = NULL;
        struct addrinfo *ptr = NULL;
        struct addrinfo hints; //TODO: do we need this?
        SOCKET sock = INVALID_SOCKET;
        #endif
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
        struct sockaddr_in server;
        #endif
        #ifdef _WIN32

        #endif
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

#endif // TCP_H
