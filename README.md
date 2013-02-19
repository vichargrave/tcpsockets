tcpsockets
==========

Example source code for the article 'TCP/IP Network Programming Design Patterns in C++'

Build
=====

1. Build the test client by running 'make -f Makefile.client'.
2. Build the test server by running 'make -f Makefile.server'.
3. Alternatively build both by just running 'make'.

Run
===

1. Type 'server <port> [<ip>]' where <ip> is the IP address of
   the network interface where you want to listen for and accept
   connections. If you don't specify an IP address the server
   will listen on all network interfaces.
2. Type 'client <port> <ip>' where <ip> is the IP address of the
   server you started in step 1. 

NOTE: If you are running client and server on the same system you
      can just use 'localhost' for <ip>.
