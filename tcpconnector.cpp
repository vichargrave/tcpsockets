/*
   TCPConnector.h

   TCPConnector class definition. TCPConnector provides methods to actively
   establish TCP/IP connections with a server.

   ------------------------------------------

   Copyright © 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License
*/

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include "tcpconnector.h"

TCPStream* TCPConnector::connect(const char* server, int port)
{
    struct sockaddr_in address;

    memset (&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (resolveHostName(server, &(address.sin_addr)) != 0 ) {
        inet_pton(PF_INET, server, &(address.sin_addr));        
    } 
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (::connect(sd, (struct sockaddr*)&address, sizeof(address)) != 0) {
        perror("connect() failed");
        return NULL;
    }
    return new TCPStream(sd, &address);
}

TCPStream* TCPConnector::connect(const char* server, int port, int timeout)
{
    if (timeout == 0) return connect(server, port);
    
    struct sockaddr_in address;

    memset (&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (resolveHostName(server, &(address.sin_addr)) != 0 ) {
        inet_pton(PF_INET, server, &(address.sin_addr));        
    }     

    long arg;
    fd_set sdset;
    struct timeval tv;
    socklen_t len;
    int result = -1, valopt, sd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set socket to non-blocking
    arg = fcntl(sd, F_GETFL, NULL);
    arg |= O_NONBLOCK;
    fcntl(sd, F_SETFL, arg);
    
    // Connect with time limit
    string message;
    if ((result = ::connect(sd, (struct sockaddr *)&address, sizeof(address))) < 0) 
    {
        if (errno == EINPROGRESS)
        {
            tv.tv_sec = timeout;
            tv.tv_usec = 0;
            FD_ZERO(&sdset);
            FD_SET(sd, &sdset);
            if (select(sd+1, NULL, &sdset, NULL, &tv) > 0)
            {
                len = sizeof(int);
                getsockopt(sd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &len);
                if (valopt) {
                    fprintf(stderr, "connect() error %d - %s\n", valopt, strerror(valopt));
                }
                // connection established
                else result = 0;
            }
            else fprintf(stderr, "connect() timed out\n");
        }
        else fprintf(stderr, "connect() error %d - %s\n", errno, strerror(errno));
    }

    // Return socket to blocking mode 
    arg = fcntl(sd, F_GETFL, NULL);
    arg &= (~O_NONBLOCK);
    fcntl(sd, F_SETFL, arg);

    // Create stream object if connected
    if (result == -1) return NULL;
    return new TCPStream(sd, &address);
}

int TCPConnector::resolveHostName(const char* hostname, struct in_addr* addr) 
{
    struct addrinfo *res;
  
    int result = getaddrinfo (hostname, NULL, NULL, &res);
    if (result == 0) {
        memcpy(addr, &((struct sockaddr_in *) res->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(res);
    }
    return result;
}
