#ifndef UDP_H
#define UDP_H
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

class UDPClient{
    private:
        int sock;
        struct sockaddr_in server;
        char buffer[1024];
        string ip;
        string hostname;
        int port;
        bool connected;
    public:
        UDPClient(string ip, int port);
        ~UDPClient();
        bool sock_connect();
        bool sock_send(string msg);
        string sock_receive();
        bool disconnect();
};

class UDPServer{
    private:
        int sock;
        struct sockaddr_in server;
        char buffer[1024];
        int port;
        bool connected;
    public:
        UDPServer(int port);
        ~UDPServer();
        bool sock_listen();
        bool sock_accept();
        bool sock_send(string msg);
        string sock_receive();
        bool disconnect();
};

#endif // UDP_H
