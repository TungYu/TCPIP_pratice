#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for bzero()
#include <unistd.h>  //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define Server_PortNumber 5555
#define Server_Address "140.120.14.241"

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr;
    int sock, byte_sent, server_addr_length = sizeof(server_addr);
    char buffer[6]="hello\0";

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)    printf("Error creating socket!\n");

    bzero(&server_addr, server_addr_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(Server_PortNumber);
    server_addr.sin_addr.s_addr = inet_addr(Server_Address);

    if (connect(sock, (struct sockaddr *)&server_addr,server_addr_length)==-1) {
        printf("connect failed!");
        close(sock);}

    byte_sent = send(sock, buffer, sizeof(buffer),0);
    if (byte_sent < 0)    printf("Error sending packet!\n");   
    close(sock);
    return 0;

}
