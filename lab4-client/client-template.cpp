// ///////////////////////////////////
// File: client.cpp 
// Student Name: Mario Leonardo
// Student ID: 101598209
// //////////////////////////////////
//#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
//#include <winsock2.h>
//#include <iostream>
#include <cstring>
using namespace std;

// Need to link with ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#define PORT	 8888
#define MAXLINE 1024 // the upper limit for the sizes of messages sent or received

int main() {
//    WSADATA wsa;
//    SOCKET s;
    struct sockaddr_in server;  // to store server sockqaddr info
    char buffer[MAXLINE];  // buffer will have the received message from server
    char msg_client[MAXLINE];  // for sending message from client to server
    int len_s; //size of  server sockaddr_in
    int n; // number of bytes received from the server

    // 1. Initialize Winsock
//    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//        printf("Failed. Error Code: %d\n", WSAGetLastError());
//        return 1;
//    }

    // 2. Create socket s using socket() function
    // The domain is IP family (AF_INET), the socket is a datagram socket.
    // Check if the socket was successfully created
    // Your code here ..

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
      cout << "Socket creation failed.\n";
      return -1;
    }
   cout << "Socket successfully created.\n";

    // 3. Fill in the server sock_addr_in structure with the IP address and port of the server to be connected to. 
    // The client will connect to this server running at the same computer
    // The server IP address is localhost (i.e., 127.0.0.1) 
    // The server address family is IPv4 (i.e., AF_INET); use inet_addr() to fill sin_addr.s_addr field
    // Port number for this socket is 8888; use htons() to fill sin_port field
    // Your code here..

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);
    len_s = sizeof(server);
   
    while (1)  // infinite loop; keep on reading messages from client until client types "Exit".
    {
        cout << "Client says:  ";
   
    //4. Read a line of message (of max size MAXLINE) from the client using cin.getline() and store it into msg_client
    // Your code here..
        cin.getline(msg_client, MAXLINE);

    //5. send msg_client to the server using sendto()
    // connect the socket s to the sockaddr_in address specified for the server
    // Your code here..
       sendto(s, (const char*)msg_client, strlen(msg_client), 0, (const struct sockaddr*)&server, len_s);
        
    //6. check if msg_client was "Exit". If yes, then break out of while() loop. Use strcmp() for the check
    // Your code here..
        if(strcmp(msg_client, "Exit") == 0)
          break;
        
        

    //7. wait for a message from the server using blocking recvfrom(). Store the incoming message into buffer.
    //  The r/home/ririio/Repositories/seneca/semester-6/btn415/lab4eturn value from recvfrom() is the actual number of bytes received from the server.
    //  Make suer that the last char in the buffer array is a null char ('\0')
    // Your code here..
        n = recvfrom(s, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&server, (socklen_t*)&len_s);
        buffer[n] = '\0';
        

        cout << "Server says : ";
    //8. Print the message received from the server. 
    // Your code here..
        cout << buffer << endl;


    }  // end of while loop

    // 9. Close socket and cleanup
    close(s);
//    closesocket(s);
//    WSACleanup();

    return 0;
}
