#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Client side implementation of UDP Server/Client model @divancevic
// Receive "Pong!" and send "Ping!" to server

#define PORT 3000
#define CLIENT_PORT 3001
#define MAX_MESSAGE_SIZE 8

int main(){
    int socket_fd;
    char buffer[MAX_MESSAGE_SIZE];
    char server_address_string[INET_ADDRSTRLEN];

    struct sockaddr_in server_address, client_address;

    memset(&server_address,0,sizeof(struct sockaddr_in));
    memset(&client_address,0,sizeof(struct sockaddr_in));
    memset(buffer,0,MAX_MESSAGE_SIZE);
    memset(server_address_string,0,INET_ADDRSTRLEN);

    if((socket_fd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
        perror("Can't create socket");
        exit(0);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT); // Port of server
    inet_aton("192.168.0.150",&server_address.sin_addr); // Address of server

    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(CLIENT_PORT); // Don't use ephemeral port, instead explicitly assing/chose one for client
    inet_aton("192.168.0.112",&client_address.sin_addr); // Address of client

    if(bind(socket_fd,(const struct sockaddr*)&client_address,sizeof(client_address)) < 0){ // Bind client address and port (source) with previously created socket file descriptor - optional on client side
        perror("Can't bind socket with client address");
        exit(0);
    }

    if(connect(socket_fd,(const struct sockaddr*)&server_address,sizeof(server_address)) < 0){ // Use server address as default (destination) for/when sending data - optional on client side
        perror("connect() failed");
        exit(0);
    }

    while(1){
        memset(buffer,0,MAX_MESSAGE_SIZE);
        sprintf(buffer,"Ping!");

        sleep(2);

        send(socket_fd,buffer,strlen(buffer),0); // Data sent to server with ip address 192.168.0.150 - as we used sys call connect() - so there is no need to explicitly write ip address of server
        memset(buffer,0,MAX_MESSAGE_SIZE);

        recv(socket_fd,(void* )&buffer,MAX_MESSAGE_SIZE,0); // Data received from server with ip address 192.168.0.150 - as we used sys call connect()
        printf("Client received: %s\n", buffer);
    }

    close(socket_fd);
    return 0;
}
