#include <iostream>
#include <string>
#include "tcp.h"
using namespace std;
using namespace cppsock;


//Server


int main(int argc, char *argv[]){
    TCPServer *server = new TCPServer(8889);
    server->sock_listen();
    server->sock_accept();
    string msg = server->sock_receive();
    cout << "Received: " << msg << endl;
    server->sock_send(msg);
    server->disconnect();
    delete server;
    return 0;
}
/*
*/


//Client
/*
int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "Usage: " << argv[0] << " <ip> <port>" << endl;
        return 1;
    }
    string ip = argv[1];
    int port = atoi(argv[2]);
    TCPClient client(ip, port);
    TCPClient client2("127.0.0.1", 1234);
    client.sock_connect();
    client.sock_send("Hello World\n");
    string msg = client.sock_receive();
    cout << msg << endl;
    client.disconnect();
    return 0;
}

*/

