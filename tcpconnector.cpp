/*
   TCPConnector.h

   TCPConnector class definition. TCPConnector provides methods to actively
   establish TCP/IP connections with a server.

   ------------------------------------------

   Copyright @ [Vic Hargrave - http://vichargrave.com]

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

#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "tcpconnector.h"

TCPStream* TCPConnector::connect(const char* server, int port)
{
    struct sockaddr_in address;

    memset (&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (resolveHost(server, &(address.sin_addr)) != 0 ) {
        inet_pton(PF_INET, server, &(address.sin_addr));        
    } 
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (::connect(sd, (struct sockaddr*)&address, sizeof(address)) != 0) {
        return NULL;
    }
    return new TCPStream(sd, &address);
}

int TCPConnector::resolveHost(const char* hostname, struct in_addr* addr) 
{
    struct addrinfo hints, *res;
  
    memset (&hints, 0, sizeof (hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;
    int result = getaddrinfo (hostname, NULL, &hints, &res);
    if (result == 0) {
        memcpy(addr, &((struct sockaddr_in *) res->ai_addr)->sin_addr, sizeof(struct in_addr));
    }
    return result;
}
