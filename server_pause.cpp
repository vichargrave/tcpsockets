/*
   server_pause.cpp

   Test server for the time out capabilties of the TCPConnector class.  This 
   server will bind to a given IP address and TCP port but never start listening.  
   Use it to test connect time outs in client_timeout.  
  
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
   limitations under the License.
*/

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "tcpacceptor.h"

int main(int argc, char** argv)
{
    int lsd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(atoi(argv[1]));
    address.sin_addr.s_addr = INADDR_ANY;
    
    int optval = 1;
    setsockopt(lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval); 
    
    int result = bind(lsd, (struct sockaddr*)&address, sizeof(address));
    if (result != 0) {
        perror("bind() failed");
        return result;
    }
    pause();

    return 0;
}    
