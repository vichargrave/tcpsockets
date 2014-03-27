/*
   client_timeout.cpp

   Test client for the tcpsockets classes. Use this program to test connect
   and receive time out capabilties.  Start the server_pause on one port and
   the server_timeout on the other.  Then run client_timeout specifying the
   server_pause and server_timeout ports.  The client will time out trying
   to connect to server_pause, which never accepts connections.  The client
   will then time out waiting for a reply from server_timeout which never 
   replies to clients.

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
#include <stdlib.h>
#include <string>
#include "tcpconnector.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 5) {
        printf("usage: %s <pause port> <time out port> <ip> <time out>\n", argv[0]);
        exit(1);
    }

    int result, timeout = atoi(argv[4]);
    string message;
    char line[256];

    printf("Connecting to the paused server...\n");
    TCPConnector* connector = new TCPConnector();
    TCPStream* stream = connector->connect(argv[3], atoi(argv[1]), timeout);
    if (stream == NULL) {
        printf("Timed out connecting to the server\n");
    }

    printf("Connecting to the time out server...\n");
    stream = connector->connect(argv[3], atoi(argv[2]), timeout);
    if (stream) {
        message = "Is there life on Mars?";
        stream->send(message.c_str(), message.size());
        printf("sent - %s\n", message.c_str());
        result = stream->receive(line, sizeof(line), timeout);
        if (result == TCPStream::connectionTimedOut) {
            printf("Timed out waiting for a server response\n");
        }
        delete stream;
    }

    exit(0);
}
