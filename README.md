# cppsock
A simple C++ socket and networking library

## Usage

import the desired files into your code:
* `tcp.h` for TCP sockets
* `udp.h` for UDP sockets (**UNTESTED**)
Make sure to either add `using namespace cppsock` OR `cppsock::<class/method name>`

## Notes
* When creating a server on Windows, make sure to create it on the heap. For some reason creating it on the stack causes a segfault when trying to write to a variable. You can do this with `TCPServer *server = new TCPServer(port)`, and then accessing the methods with `server->method()` instead of `server.method()`. As far as I can tell this does not happen on Linux.

## TCP functionality (`tcp.h`)
### Client
* Initialize a TCP client with `TCPClient(string IP, int port)`
* connect with `sock_connect()`

### Server
* Initialize a TCP server with `TCPServer(int port)`
* listen with `sock_listen()`
* when this returns, accept the connection with `sock_accept()`

### Both
* send a string with `sock_send(string msg)`
* receive a reply with `sock_receive()`
* remember to `delete` or `disconnect()` to close the socket when you're done

## UDP functionality (`udp.h`) **UNTESTED**
### Client
* Initialize a UDP client with `UDPClient(string IP, int port)`
* connect with `sock_connect()`

### Server
* Initialize a TCP server with `UDPServer(int port)`
* listen with `sock_listen()`
* when this returns, accept the connection with `sock_accept()`

### Both
* send a string with `sock_send(string msg)`
* receive a reply with `sock_receive()`
* remember to `delete` or `disconnect()` to close the socket when you're done


## TODO
* Test UDP functionality
* Add SSL support
* Add wrappers to these classes to make common networking related tasks less tedious
