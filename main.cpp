#include <iostream>
#include <string>
#include <arpa/inet.h>
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
        TCPClient(string ip, int port){
            this->ip = ip;
            this->port = port;
            this->connected = false;
        }
        ~TCPClient(){
            close(sock);
        }
        bool sock_connect(){
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
        bool sock_send(string msg){
            if(!this->connected) return false;
            if(send(this->sock, msg.c_str(), msg.length(), 0) < 0){
                cout << "Error sending message" << endl;
                return false;
            }
            return true;
        }
        string receive(){
            if(!this->connected) return "";
            if(recv(this->sock, this->buffer, 1024, 0) < 0){
                cout << "Error receiving message" << endl;
                return "";
            }
            return this->buffer;
        }
        bool disconnect(){
            if(!this->connected) return false;
            close(this->sock);
            this->connected = false;
            return true;
        }
};

int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "Usage: " << argv[0] << " <ip> <port>" << endl;
        return 1;
    }
    TCPClient client(argv[1], atoi(argv[2]));
    if(!client.sock_connect()){
        cout << "Error connecting to server" << endl;
        return 1;
    }
    string msg;
    while(true){
        cout << "Enter message: ";
        getline(cin, msg);
        if(msg == "exit") break;
        if(!client.sock_send(msg)){
            cout << "Error sending message" << endl;
            return 1;
        }
        msg = client.receive();
        if(msg == ""){
            cout << "Error receiving message" << endl;
            return 1;
        }
        cout << "Server: " << msg << endl;
    }
    if(!client.disconnect()){
        cout << "Error disconnecting from server" << endl;
        return 1;
    }
    return 0;
}
