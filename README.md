# cppsock
A simple C++ socket and networking library

## Usage

import the desired files into your code:
* `tcp.h` for TCP sockets

## TCP functionality (tcp.h)
### Client
* Initialize a TCP client with `TCPClient(string IP, int port)`
* connect with `sock_connect()`

### Server
* Initialize a TCP server with `TCPServer(int port)`
* listen with `sock_listen()`
* when this returns, accept the connection with `sock_accept()`

### Misc/other
* send a string with `sock_send(string msg)`
* receive a reply with `sock_receive()`
* remember to `delete` or `disconnect()` to close the socket when you're done
