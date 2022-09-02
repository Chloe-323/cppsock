#include "tcp.h"
using namespace std;
using namespace cppsock;

//TESTED WORKING
TCPClient::TCPClient(string ip, int port){
    #ifdef _WIN32
    WSAnumInstances++;
    WSAManage();
    //TODO: get raw address
    #endif
    this->ip = ip;
    this->port = port;
    this->connected = false;
}
TCPClient::~TCPClient(){
    #ifdef __linux__
    close(sock);
    #endif
    #ifdef _WIN32
    closesocket(sock);
    WSAnumInstances--;
    WSAManage();
    #endif
}
bool TCPClient::sock_connect(){
    if(this->connected) return true;

    #ifdef __linux__
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
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
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
    #endif
    return true;
}
bool TCPClient::sock_send(string msg){
    if(!this->connected) return false;
    #ifdef __linux__
    if(send(this->sock, msg.c_str(), msg.length(), 0) < 0){
        cout << "Error sending message" << endl;
        return false;
    }
    #endif
    #ifdef _WIN32
    if(send(sock, msg.c_str(), msg.length(), 0) == SOCKET_ERROR){
        cout << "Error sending message" << endl;
        return false;
    }
    #endif
    return true;
}
string TCPClient::sock_receive(){ //TODO: arbitrary length buffer
    if(!this->connected) return "";
    #ifdef __linux__
    if(recv(this->sock, this->buffer, 1024, 0) < 0){
        cout << "Error receiving message" << endl;
        return "";
    }
    #endif
    #ifdef _WIN32
    if(recv(sock, buffer, 1024, 0) == SOCKET_ERROR){
        cout << "Error receiving message" << endl;
        return "";
    }
    #endif
    return this->buffer;
}
bool TCPClient::disconnect(){
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


TCPServer::TCPServer(int port){
    #ifdef _WIN32
    WSAnumInstances++;
    WSAManage();
    #endif
    this->port = port;
    this->connected = false;
}
TCPServer::~TCPServer(){
    #ifdef __linux__
    close(sock);
    #endif
    #ifdef _WIN32
    closesocket(sock);
    WSAnumInstances--;
    WSAManage();
    #endif
}
bool TCPServer::sock_listen(){
    if(this->connected) return true;
    #ifdef __linux__
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if(this->sock < 0){
        cout << "Error creating socket" << endl;
        return false;
    }
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = INADDR_ANY;
    this->server.sin_port = htons(this->port);
    if(bind(this->sock, (struct sockaddr *)&this->server, sizeof(this->server)) < 0){
        cout << "Error binding socket" << endl;
        return false;
    }
    if(listen(this->sock, 1) < 0){
        cout << "Error listening" << endl;
        return false;
    }
    this->connected = true;
    #endif
    #ifdef _WIN32
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock == INVALID_SOCKET){
        cout << "Error creating socket" << endl;
        return false;
    }
    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(this->port);
    this->server.sin_addr.s_addr = INADDR_ANY; //Works on Windows?
    if(bind(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        cout << "Error binding socket" << endl;
        return false;
    }
    if(listen(sock, 1) == SOCKET_ERROR){ //Only one connection for now
        cout << "Error listening" << endl;
        return false;
    }
    this->connected = true;
    #endif
    return true;
}
bool TCPServer::sock_accept(){
    if(!this->connected) return false;
    #ifdef __linux__
    int new_sock = accept(this->sock, (struct sockaddr *)&this->server, (socklen_t*)&this->server);
    if(new_sock < 0){
        cout << "Error accepting connection" << endl;
        return false;
    }
    this->sock = new_sock;
    #endif
    #ifdef _WIN32
    SOCKET new_sock = accept(sock, (struct sockaddr *)&server, (socklen_t*)&server);
    if(new_sock == INVALID_SOCKET){
        cout << "Error accepting connection" << endl;
        return false;
    }
    #endif
    return true;
}
bool TCPServer::sock_send(string msg){
    if(!this->connected) return false;
    #ifdef __linux__
    if(send(this->sock, msg.c_str(), msg.length(), 0) < 0){
        cout << "Error sending message" << endl;
        return false;
    }
    #endif
    #ifdef _WIN32
    if(send(sock, msg.c_str(), msg.length(), 0) == SOCKET_ERROR){
        cout << "Error sending message" << endl;
        return false;
    }
    #endif
    return true;
}
string TCPServer::sock_receive(){
    if(!this->connected) return "";
    #ifdef __linux__
    if(recv(this->sock, this->buffer, 1024, 0) < 0){
        cout << "Error receiving message" << endl;
        return "";
    }
    #endif
    #ifdef _WIN32
    if(recv(sock, buffer, 1024, 0) == SOCKET_ERROR){
        cout << "Error receiving message" << endl;
        return "";
    }
    #endif
    return this->buffer;
}
bool TCPServer::disconnect(){
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
