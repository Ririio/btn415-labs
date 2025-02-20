// /////////////////////
// File: server.cpp 
// Student Name: Mario Leonardo
// Student ID: 101598209
// ///////////////////////

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define PORT	 8888 
#define MAXLINE 1024 // the upper limit for the sizes of messages sent or received

int main() {
//    WSADATA wsa;
//    SOCKET s;
    struct sockaddr_in server, client;  // for server and client
    char buffer[MAXLINE];
    char msg_server[MAXLINE];  // message to be sent by server
    int len_c; // will have sizeof(struct sockaddr_in client);
    int n; // number of bytes received from client

    // 1. Initialize Winsock
//    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//        printf("Failed. Error Code: %d\n", WSAGetLastError());
//        return 1;
//    }

    // 2. Create socket s with IP family (AF_INET), and SOC_DGRAM
    // Check for the successful socket creation
    // Your code here

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
      cout << "Socket creation failed."  << endl;
      return -1;
    }
    cout << "Socket successfully created." << endl;

    // 3. Fill in the server sockaddr_in structure infoation
    // .sin_family is AF_INET; .sin_addr.s_addr is INADDR_ANY (Any IP address assigned to the server host)
    // .sin_port should be 8888; use htons(8888); to initialize this field
    // Your code here..

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);


    // 4. Bind the socket s to this server's sockaddr. Check for errors
    // Your code here..

    if(bind(s, (struct sockaddr*)&server, sizeof(server)) == -1){
      cout << "Bind failed." << endl;
      return -1;
     }

     cout << "Bind successful." << endl;
    
    // Just send out the message declaring that server is ready..

    cout << "Server Ready.. " << endl;
    len_c = sizeof(client); //len_c is value/result
    while (1)
        // infinite loop; first receive message from client, and then send a response message
        // If "Exit" message is received from the client, then break the loop
    {
    // 5. Receive message from client using recvfrom(). 
    // Store the received message into buffer (of max size MAXLINE), and extract client sockaddr info
    // The actual number of bytes received is n (returned from recvfrom().
    // Make sure that that the last char in the buffer is null ('\0').
    // Your code here..

        n = recvfrom(s, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&client, (socklen_t*)&len_c);
        buffer[n] = '\0';

        cout << "Client says : ";
    // 6.  Print the message received from the client
    // Your code here..

        cout << buffer << endl;

    // 7. If the message received from client is "Exit", break out of while loop and termainte
    // use strcmp() function
    // Your code here..
        if(strcmp(buffer, "Exit") == 0){
            break;
        }

       
        cout << "Server says: ";
    //8. Read the response from the server user. use cin.getline()
    // Your code here..
        cin.getline(msg_server, MAXLINE);
        cout << msg_server << endl;

        
    //9. send the server response to the client using sendto()
    //  Use the destination's (client's) sockaddr info.
    // Your code here..
        sendto(s, (const char*)msg_server, strlen(msg_server), 0, (const struct sockaddr*)&client, len_c);

    } // end of while loop



    // 10. Close sockets

//    closesocket(s);
    close(s);

    //11. cleanup

//    WSACleanup();

    return 0;
}