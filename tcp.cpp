#include "tcp.h"
using namespace std;

//TESTED WORKING
TCPClient::TCPClient(string ip, int port){
    this->ip = ip;
    this->port = port;
    this->connected = false;
}
TCPClient::~TCPClient(){
    close(sock);
}
bool TCPClient::sock_connect(){
    if(this->connected) return true;
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
    return true;
}
bool TCPClient::sock_send(string msg){
    if(!this->connected) return false;
    if(send(this->sock, msg.c_str(), msg.length(), 0) < 0){
        cout << "Error sending message" << endl;
        return false;
    }
    return true;
}
string TCPClient::sock_receive(){
    if(!this->connected) return "";
    if(recv(this->sock, this->buffer, 1024, 0) < 0){
        cout << "Error receiving message" << endl;
        return "";
    }
    return this->buffer;
}
bool TCPClient::disconnect(){
    if(!this->connected) return false;
    close(this->sock);
    this->connected = false;
    return true;
}

//UNTESTED
TCPServer::TCPServer(int port){
    this->port = port;
    this->connected = false;
}
TCPServer::~TCPServer(){
    close(sock);
}
bool TCPServer::sock_listen(){
    if(this->connected) return true;
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
    return true;
}
bool TCPServer::sock_accept(){
    if(!this->connected) return false;
    int new_sock = accept(this->sock, (struct sockaddr *)&this->server, (socklen_t*)&this->server);
    if(new_sock < 0){
        cout << "Error accepting connection" << endl;
        return false;
    }
    this->sock = new_sock;
    return true;
}
bool TCPServer::sock_send(string msg){
    if(!this->connected) return false;
    if(send(this->sock, msg.c_str(), msg.length(), 0) < 0){
        cout << "Error sending message" << endl;
        return false;
    }
    return true;
}
string TCPServer::sock_receive(){
    if(!this->connected) return "";
    if(recv(this->sock, this->buffer, 1024, 0) < 0){
        cout << "Error receiving message" << endl;
        return "";
    }
    return this->buffer;
}
bool TCPServer::disconnect(){
    if(!this->connected) return false;
    close(this->sock);
    this->connected = false;
    return true;
}
