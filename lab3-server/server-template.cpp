/* ********************************************
File: server.cpp
Student Name:
Student ID:
**********************************************/

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

#pragma comment(lib, "ws2_32.lib")

int main() {
//    WSADATA wsa;
//    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int num; // the integer to be received from client
    int  result; // result computed by server 
    int c; // will have sizeof(struct sockaddr_in);

    // 1. Initialize Winsock
//    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//        printf("Failed. Error Code: %d\n", WSAGetLastError());
//        return 1;
//    }

    // 2. Create socket s with IP family (AF_INET), and SOC_STREAM
    // Use socket() function
    // Check for the successful socket creation
    // Your code here ..
    
    int s = socket(AF_INET, SOCK_STREAM, 0);

    // 3. Fill in the server sockaddr_in structure
    // .sin_family is AF_INET; .sin_addr.s_addr is INADDR_ANY (Any IP address assigned to the server host)
    // .sin_port should be 8888; use htons(8888); to initialize this field
    // Your code here ..
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // 4. Bind the socket s to this server's sockaddr. Check for errors
    // Use bind() function
    // Your code here ..
    
    int bnd = bind(s, (struct sockaddr *)&server, sizeof(server));
    if (bnd == -1) {
      perror("bind");
    }

    //5.  Listen to incoming connections on the sock s, and allow a max of 3 incoming connections
    // use listen() function
    // Your code here ..

    listen(s, 3);
   
    //6. Print a message saying "Waiting for incoming connections .."
    // Your code here ..

    cout << "Server listening on port 8888" << endl;

    // 7. initilize int variable c to sizeof(struct sockaddr_in);
    // Your code here ..

    c = sizeof(struct sockaddr_in);
     
    //8. accept() the pending connection request for socket s and return a new socket descriptor (new_socket) for this connection.
    // Check on the return value from accept() for error
    // Your code here ..

    int acpt = accept(s, (struct sockaddr *)&client, (socklen_t *)&c);
    if (acpt == -1) {
      perror("accept");
    }
    cout << "Client connected" << endl;

    
     // 9. Using recv(), receive an integer from client on the socket created by accept()
    // Your code here ..
    recv(acpt, &num, sizeof(int), 0);

     // 10. Compute the square of the integer rxd
    // Your code here ..
    num = num * num;
        

     //11.  Send result back to client using send(); Print out the result sent
    // Your code here ..
    send(acpt, &num, sizeof(int), 0);
    cout << "Client received num: " << num << endl;
        

        
    
    // 12. Close sockets
    close(acpt);
    close(s);

    //13. cleanup

    // Not required for linux

    return 0;
}