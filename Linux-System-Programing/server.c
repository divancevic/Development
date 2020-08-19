#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Server side implementation of UDP Server/Client model - @divancevic
// Receive "Ping!" and send "Pong!" to client

#define PORT 3000
#define MAX_MESSAGE_SIZE 8

int main()
{
    int socket_fd;
    socklen_t client_len;
    char buffer[MAX_MESSAGE_SIZE];
    char client_address_string[INET_ADDRSTRLEN];

    struct sockaddr_in server_address, client_address;

    memset(&server_address,0,sizeof(struct sockaddr_in));
    memset(&client_address,0,sizeof(struct sockaddr_in));
    memset(buffer,0,MAX_MESSAGE_SIZE);
    memset(client_address_string,0,INET_ADDRSTRLEN);

    client_len = sizeof(client_address); // Will be used for printing client address purpose

    if((socket_fd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
        perror("Can't create socket");
        exit(0);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_aton("192.168.0.150",&server_address.sin_addr); // Convert string (server) ip address and store it in struct member sin_addr
    							   // Must be ip address of one of interfaces or loopback address

    if(bind(socket_fd,(const struct sockaddr*)&server_address,sizeof(server_address)) < 0){ // Bind server address with previously created socket file descriptor
        perror("Can't bind socket with server address");
        exit(0);
    }

    char* message_to_send = "Pong!"; // Send this message to client machine


    while(1){ // recevfrom() and sendto() used because connect() sys call not made on server side application
        recvfrom(socket_fd,(void *)buffer,MAX_MESSAGE_SIZE,MSG_WAITALL,(struct sockaddr*)&client_address,&client_len);
        printf("Received message: %s -- from client with address: %s and port: %u\n",buffer,inet_ntop(AF_INET,(void *)&(client_address.sin_addr),client_address_string,INET_ADDRSTRLEN),ntohs(client_address.sin_port));

        sendto(socket_fd,(void *)message_to_send,strlen(message_to_send),MSG_CONFIRM,(struct sockaddr*)&client_address,client_len);

        memset(&buffer,0,MAX_MESSAGE_SIZE);
        memset(&client_address_string,0,INET_ADDRSTRLEN);
        memset(&client_address,0,sizeof(struct sockaddr_in));
    }

    close(socket_fd);
    return 0;
}
