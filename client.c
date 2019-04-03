/*
 * @Author: Lucas Duboisse 
 * @Date: 2019-04-01 15:46:41 
 * @Last Modified by: Lucas Duboisse
 * @Last Modified time: 2019-04-01 16:27:11
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av)
{
        int sock = 0;
        struct sockaddr_in sockaddr = {0};
        int valread = 0;
        char buffer[1000] = {0};

        if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
                perror("Socket failed");
                exit(EXIT_FAILURE);
        }

        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(atoi(av[2]));

        if (inet_pton(AF_INET, av[1], &sockaddr.sin_addr) <= 0) {
                perror("inet_pton failed");
                exit(EXIT_FAILURE);
        }
        if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
                perror("Connect failed");
                exit(EXIT_FAILURE);
        }
        valread = read(sock, buffer, 1000);
        printf("Server said: %s", buffer);
        close(sock);
        return 0;
}