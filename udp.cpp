#include "udp.h"
using namespace std;
using namespace cppsock;

//UNTESTED
UDPClient::UDPClient(string ip, int port){
    #ifdef _WIN32
    WSAnumInstances++;
    WSAManage();
    //TODO: get raw address
    #endif
    this->ip = ip;
    this->port = port;
    this->connected = false;
}
UDPClient::~UDPClient(){
    #ifdef __linux__
    close(sock);
    #endif
    #ifdef _WIN32
    closesocket(sock);
    WSAnumInstances--;
    WSAManage();
    #endif
}
bool UDPClient::sock_connect(){
    if(this->connected) return true;
    #ifdef __linux__
    this->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(this->sock < 0){
        cout << "Error creating socket" << endl;
        return false;
    }
    this->server.sin_addr.s_addr = inet_addr(this->ip.c_str());
    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(this->port);
    if(connect(this->sock, (struct sockaddr *)&this->server, sizeof(this->server)) < 0){
        cout << "Error connecting to server" << endl;
        return false;
    }
    this->connected = true;
    #endif
    #ifdef _WIN32
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == INVALID_SOCKET){
        cout << "Error creating socket" << endl;
        return false;
    }
    //Connect via IP
    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(this->port);
    this->server.sin_addr.s_addr = inet_addr(this->ip.c_str());
    if(connect(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        cout << "Error connecting to server" << endl;
        return false;
    }
    this->connected = true;
    #endif
    return true;
}
bool UDPClient::sock_send(string msg){
    if(!this->connected) return false;
    #ifdef __linux__
    if(sendto(this->sock, msg.c_str(), msg.length(), 0, (struct sockaddr *)&this->server, sizeof(this->server)) < 0){
        cout << "Error sending message" << endl;
        return false;
    }
    #endif
    #ifdef _WIN32
    if(sendto(sock, msg.c_str(), msg.length(), 0, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        cout << "Error sending message" << endl;
        return false;
    }
    #endif
    return true;
}
string UDPClient::sock_receive(){
    if(!this->connected) return "";
    //zero out buffer
    memset(this->buffer, 0, sizeof(this->buffer));
    #ifdef __linux__
    socklen_t server_len = sizeof(this->server);
    if(recvfrom(this->sock, this->buffer, 1024, 0, (struct sockaddr *)&this->server, &server_len) < 0){
        cout << "Error receiving message" << endl;
        return "";
    }
    #endif
    #ifdef _WIN32
    int server_len = sizeof(this->server);
    if(recvfrom(sock, this->buffer, 1024, 0, (struct sockaddr *)&this->server, &server_len) == SOCKET_ERROR){
        cout << "Error receiving message" << endl;
        return "";
    }
    #endif
    return this->buffer;
}

bool UDPClient::disconnect(){
    if(!this->connected) return false;
    #ifdef __linux__
    close(this->sock);
    this->connected = false;
    #endif
    #ifdef _WIN32
    closesocket(this->sock);
    this->connected = false;
    #endif
    return true;
}

UDPServer::UDPServer(int port){
    #ifdef _WIN32
    WSAnumInstances++;
    WSAManage();
    #endif
    this->port = port;
    this->connected = false;
}
UDPServer::~UDPServer(){
    #ifdef __linux__
    close(sock);
    #endif
    #ifdef _WIN32
    closesocket(sock);
    WSAnumInstances--;
    WSAManage();
    #endif
}
bool UDPServer::sock_listen(){
    if(this->connected) return true;
    #ifdef __linux__
    this->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(this->sock < 0){
        cout << "Error creating socket" << endl;
        return false;
    }
    this->server.sin_addr.s_addr = INADDR_ANY;
    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(this->port);
    if(bind(this->sock, (struct sockaddr *)&this->server, sizeof(this->server)) < 0){
        cout << "Error binding socket" << endl;
        return false;
    }
    this->connected = true;
    #endif
    #ifdef _WIN32
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == INVALID_SOCKET){
        cout << "Error creating socket" << endl;
        return false;
    }
    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(this->port);
    this->server.sin_addr.s_addr = INADDR_ANY;
    if(bind(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        cout << "Error binding socket" << endl;
        return false;
    }
    this->connected = true;
    #endif
    return true;
}

bool UDPServer::sock_accept(){
    if(!this->connected) return false;
    return true;
}

bool UDPServer::sock_send(string msg){
    if(!this->connected) return false;
    #ifdef __linux__
    if(sendto(this->sock, msg.c_str(), msg.length(), 0, (struct sockaddr *)&this->server, sizeof(this->server)) < 0){
        cout << "Error sending message" << endl;
        return false;
    }
    #endif
    #ifdef _WIN32
    if(sendto(sock, msg.c_str(), msg.length(), 0, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        cout << "Error sending message" << endl;
        return false;
    }
    #endif
    return true;
}

string UDPServer::sock_receive(){
    if(!this->connected) return "";
    //zero out buffer
    memset(this->buffer, 0, sizeof(this->buffer));
    #ifdef __linux__
    socklen_t server_len = sizeof(this->server);
    if(recvfrom(this->sock, this->buffer, 1024, 0, (struct sockaddr *)&this->server, &server_len) < 0){
        cout << "Error receiving message" << endl;
        return "";
    }
    #endif
    #ifdef _WIN32
    int server_len = sizeof(this->server);
    if(recvfrom(sock, this->buffer, 1024, 0, (struct sockaddr *)&this->server, &server_len) == SOCKET_ERROR){
        cout << "Error receiving message" << endl;
        return "";
    }
    #endif
    return this->buffer;
}

bool UDPServer::disconnect(){
    if(!this->connected) return false;
    #ifdef __linux__
    close(this->sock);
    this->connected = false;
    #endif
    #ifdef _WIN32
    closesocket(sock);
    this->connected = false;
    #endif
    return true;
}
