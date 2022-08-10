#include "udp.h"

//UNTESTED
UDPClient::UDPClient(string ip, int port){
    this->ip = ip;
    this->port = port;
    this->connected = false;
}
UDPClient::~UDPClient(){
    close(sock);
}
bool UDPClient::sock_connect(){
    if(this->connected) return true;
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
    return true;
}
bool UDPClient::sock_send(string msg){
    if(!this->connected) return false;
    if(sendto(this->sock, msg.c_str(), msg.length(), 0, (struct sockaddr *)&this->server, sizeof(this->server)) < 0){
        cout << "Error sending message" << endl;
        return false;
    }
    return true;
}
string UDPClient::sock_receive(){
    if(!this->connected) return "";
    socklen_t server_len = sizeof(this->server);
    if(recvfrom(this->sock, this->buffer, 1024, 0, (struct sockaddr *)&this->server, &server_len) < 0){
        cout << "Error receiving message" << endl;
        return "";
    }
    return this->buffer;
}

bool UDPClient::disconnect(){
    if(!this->connected) return false;
    close(this->sock);
    this->connected = false;
    return true;
}

UDPServer::UDPServer(int port){
    this->port = port;
    this->connected = false;
}
UDPServer::~UDPServer(){
    close(sock);
}
bool UDPServer::sock_listen(){
    if(this->connected) return true;
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
    return true;
}

bool UDPServer::sock_accept(){
    if(!this->connected) return false;
    return true;
}

bool UDPServer::sock_send(string msg){
    if(!this->connected) return false;
    if(sendto(this->sock, msg.c_str(), msg.length(), 0, (struct sockaddr *)&this->server, sizeof(this->server)) < 0){
        cout << "Error sending message" << endl;
        return false;
    }
    return true;
}

string UDPServer::sock_receive(){
    if(!this->connected) return "";
    socklen_t server_len = sizeof(this->server);
    if(recvfrom(this->sock, this->buffer, 1024, 0, (struct sockaddr *)&this->server, &server_len) < 0){
        cout << "Error receiving message" << endl;
        return "";
    }
    return this->buffer;
}

bool UDPServer::disconnect(){
    if(!this->connected) return false;
    close(this->sock);
    this->connected = false;
    return true;
}
