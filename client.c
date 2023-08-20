#include <stdio.h>      // header contaning functions such as printf
#include <stdlib.h>     // header contaning functions such as malloc, free, atoi
#include <unistd.h>     // for POSIX operating system API functions such as close
#include <string.h>     //  header contaning functions such as memset
#include <sys/socket.h> // header contaning socket functions
#include <arpa/inet.h>  // header contaning byte-odering standardization functions of htons
#include <netinet/in.h> // header containing structure for internet addresses and macros such as INADDR_ANY

int main()
{
    // socket()
    int serverfd = socket(AF_INET, SOCK_DGRAM, 0); // creates a socket for communication via IPv4 and UDP
    int recv_len;
    char buffer[256];
    if (serverfd < 0) // if we couldn't create a socket
    {
        perror("socket error");
        return -1;
    }
    if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) // Allows to reuse address, without it you might run into "Address already in use errors"
    {
        perror("setsockopt error");
        exit(-1);
    }

    struct sockaddr_in srvaddr; // defines server address
    memset(&srvaddr, 0, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;   // IPv4 Family
    srvaddr.sin_port = htons(9000); // convert 5000 port number to network-byte order
    srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send message to server
    if (sendto(serverfd, "Time request", strlen("Time request"), 0, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) == -1)
    {
        perror("sendto error");
        exit(1);
    }

    // Receive system time and date from server
    if ((recv_len = recvfrom(serverfd, buffer, sizeof(buffer), 0, NULL, NULL)) == -1)
    {
        perror("recvfrom error");
        exit(1);
    }

    buffer[recv_len] = '\0'; // Add null terminator to received message
    printf("Server time: %s\n", buffer);

    close(serverfd);
    return 0;
}