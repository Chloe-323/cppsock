#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;


class TCPClient {
    private:
        int sock;
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
        int sock;
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
