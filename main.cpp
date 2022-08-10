#include <iostream>
#include <string>
#include "tcp.h"
using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }
    int port = atoi(argv[1]);
    TCPServer server(port);
    server.sock_listen();
    server.sock_accept();
    server.sock_send("Hello World");
    string msg = server.sock_receive();
    cout << msg << endl;
    server.disconnect();
    return 0;
}
