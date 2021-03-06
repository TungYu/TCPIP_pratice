#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for bzero()
#include <unistd.h>  //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_ntoa
#include <netinet/in.h>
#include <sys/time.h> // gettimeofday func

#define Server_PortNumber 1235
#define Server_Address "127.0.0.1"
#define DATAGRAM_NUM 30

int main(int argc, char *argv[]) {
    struct sockaddr_in address;
    struct timeval start_t,end_t;
    long double start_sec, end_sec, t_interval;
    int sock, byte_sent;
    char buffer[6]="hello\0";
    int i = 0, bytes = 0;


    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0)    printf("Error creating socket\n");

    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));
    address.sin_addr.s_addr = inet_addr(argv[1]);
    int address_length = sizeof(address);
         
    /* clock start */
    gettimeofday(&start_t,NULL);
    start_sec = (double)start_t.tv_sec + (double)start_t.tv_usec / 1000000;

    for(i = 0; i < DATAGRAM_NUM; i++){
	
	byte_sent = sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&address, address_length);
	if (byte_sent < 0)    printf("Error sending packet\n");
	bytes = bytes + sizeof(buffer);
    }

    /* clock end */
    gettimeofday(&end_t,NULL);
    end_sec = (double)end_t.tv_sec + (double)end_t.tv_usec / 1000000;
    
    t_interval = end_sec - start_sec;
    printf("Server port: %d\nServer IP: %s\nDatagran number: %d\nTime interval1: %llf\nThroughput: %llf Mbps\n", ntohs(address.sin_port), inet_ntoa(address.sin_addr), DATAGRAM_NUM, t_interval, (double)bytes / (t_interval * 1000000));



    close(sock);
    return 0;

}

