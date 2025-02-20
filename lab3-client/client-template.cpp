/* ********************************************
File: client.cpp 
Student Name:  Mario Leonardo
Student ID: 101598209
**********************************************/
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
// #include <winsock2.h>
#include <iostream>
using namespace std;

// Need to link with ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


int main() {
//    WSADATA wsa;
//    SOCKET s;
    struct sockaddr_in server;
    int num; // number to be read from the user and to be sent to server
    int  result; // result sent by the server

// Not required for linux
    // 1. Initialize Winsock
//    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//        printf("Failed. Error Code: %d\n", WSAGetLastError());
//        return 1;
//    }

    // 2. Create socket s using socket() function
    // The domain is IP family (AF_INET), the socket is stream socket.
    // Check if the socket was successfully created
    // Your code here ..
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if(s == -1) {
      cout << "Error in opening socket" << endl;
      return -1;
    }
    cout << "Socket opened" << endl;


    // 3. Fill in the server sock_addr_in structure with the IP address and port of the server to be connected to.
    // The client will connect to this server running at the same computer
    // The server IP address is localhost (i.e., 127.0.0.1)
    // The server address family is IPv4 (i.e., AF_INET); use inet_addr() to fill sin_addr.s_addr field
    // Port number for this socket is 8888; use htons() to fill sin_port field
    // Your code here..

   server.sin_addr.s_addr = inet_addr("127.0.0.1");
   server.sin_family = AF_INET;
   server.sin_port = htons(8888);


    // 4. Connect to server using connect() function
    // connect the socket with fildescriptor s to the sockaddr_in address specified for the server
    // connect to IP address and port of the server to be connected to.
    // Check whether the connect() was successful
    // Your code here..

   int con = connect(s, (struct sockaddr *)&server, sizeof(server));
   if(con == -1) {
     cout << "Connect failed, errno = " << errno << endl;
     return -1;
    }
    cout << "Connected" << endl;

   // 5. Read an integer number from the user through keyboard
   // Your code here..

   int x;
   cin >> x;

   // 6. Send the number read from the user to the server application over the socket s
   // Use send() function
   // Your code here..

   send(s, &x, sizeof(&x), 0);

   // 7. Receive the results from the server on socket s using recv()
   // Your code here..

    int r = recv(s, &x, sizeof(&x), 0);
    if(r == -1) {
      cout << "recv failed, errno = " << errno << endl;
      return -1;
    }

   // 8. Print the result got from server
   // Your code here..

   cout << "Received: " << x << endl;

  // 9. Close socket and cleanup
    close(s);

    return 0;
}
