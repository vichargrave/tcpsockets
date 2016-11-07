# tcpsockets

Example source code from my TCP/IP Network Programming Design Patterns in C++ and TCP/IP Sockets with Time Out Capabilities blogs.

## Build

1. cd to the `tcpsockets` directory.
2. Type `make` to build all the clients and servers

## Run client and server

1. Type `server <port> [<ip>]` where <ip> is the IP address of
   the network interface where you want to listen for and accept
   connections. If you don't specify an IP address the server
   will listen on all network interfaces.
2. Type `client <port> <ip>` where <ip> is the IP address of the
   server you started in step 1. 

NOTE: If you are running client and server on the same system you
      can just use `localhost` for `<ip>`.

## Run client and server with time out

1. Type `server_pause <pause port>` to start a server that binds
   to any IP address and the pasue port you specify, but never
   listens for connection requests.
2. Type `server_timeout <time out port> [<ip>]` to start a server that 
   listens for connections and receives requests bu never replies.
3. To test connect and receive time outs, run client_timeout by typing
   `connect_timeout <pause port> <time out port> <ip> <time out>` where
   <pause port> is the port from step 1, <time out port> is the port
   from step 2, <ip> is the IP address from step 2 and <time out> is
   the number of seconds to wait on a connect or receive operation 
   before timing out.
