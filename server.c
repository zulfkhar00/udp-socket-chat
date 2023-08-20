#include <stdio.h>      // header contaning functions such as printf
#include <stdlib.h>     // header contaning functions such as malloc, free, atoi
#include <unistd.h>     // for POSIX operating system API functions such as close
#include <string.h>     //  header contaning functions such as memset
#include <sys/socket.h> // header contaning socket functions
#include <arpa/inet.h>  // header contaning byte-odering standardization functions of htons
#include <netinet/in.h> // header containing structure for internet addresses and macros such as INADDR_ANY
#include <time.h>

int main()
{
    // socket()
    int serverfd = socket(AF_INET, SOCK_DGRAM, 0); // creates a socket for communication via IPv4 and UDP
    if (serverfd < 0)
    {
        perror("socket error");
        return -1;
    }

    if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) // Allows to reuse address, without it you might run into "Address already in use errors"
    {
        perror("setsockopt error");
        exit(-1);
    }

    // bind()
    struct sockaddr_in srvaddr;
    memset(&srvaddr, 0, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;   // IPv4 Family
    srvaddr.sin_port = htons(9000); // convert port number to network-byte order
    srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(serverfd, (const struct sockaddr *)&srvaddr, sizeof(srvaddr)) < 0) // binds the socket to all the available network addresses which also include loopback (127.0.0.1) address
    {
        perror("bind error");
        return -1;
    }

    printf("%s \n", inet_ntoa(srvaddr.sin_addr));
    printf("%d \n", ntohs(srvaddr.sin_port));

    printf("Server Started: \n");

    while (1)
    {
        char buffer[256];
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        ssize_t recv_len = recvfrom(serverfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_len);
        if (recv_len < 0)
        {
            perror("recvfrom() failed");
            continue;
        }
        // Get the IP address and port number of the client
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_addr.sin_port);

        // Get the current system time and date
        time_t current_time = time(NULL);
        char *time_str = ctime(&current_time);
        if (time_str == NULL)
        {
            perror("ctime() failed");
            continue;
        }

        // Send the system time and date back to the client
        ssize_t send_len = sendto(serverfd, time_str, strlen(time_str), 0, (struct sockaddr *)&client_addr, client_len);
        if (send_len < 0)
        {
            perror("sendto() failed");
            continue;
        }

        printf("%s from %s:%d\n", buffer, client_ip, client_port);
    }

    close(serverfd);

    return 0;
}
