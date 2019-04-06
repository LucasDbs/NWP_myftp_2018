/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** server.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "ftp.h"

int create_socket(struct sockaddr_in *addr, int backlog)
{
        int sock = socket(PF_INET, SOCK_STREAM, 0);

        if (sock == -1) {
                perror("socket failed");
                return (-1);
        }
        if (bind(sock, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
                perror("bind failed");
                return (-1);
        }
        if (listen(sock, backlog) < 0) {
                perror("listen failed");
                return (-1);
        }
        return sock;
}

// int manage_select(fd_set *rfds, int sock, int *clients)
// {
//         int max = sock;

//         FD_ZERO(rfds);
//         FD_SET(sock, rfds);
//         for (int i = 0; i < 30; i++) {
//                 if (clients[i] > 0)
//                         FD_SET(clients[i], rfds);
//                 if (clients[i] > max)
//                         max = clients[i];
//         }
//         if (select(max + 1, rfds, NULL, NULL, NULL) < 0) {
//                 perror("select failed");
//                 return (-1);
//         }
//         return (0);
// }

// int incoming_connection(int sock, struct sockaddr_in *addr, int *clients)
// {
//         int new_socket = 0;
//         int addrlen = sizeof(*addr);

//         if ((new_socket = accept(sock, (struct sockaddr *)addr, (socklen_t *)&addrlen)) < 0) {
//                 perror("accept failed");
//                 return (-1);
//         }
//         printf("New connection, socket fd is: %d, ip is: %s, port is: %d\n",
//                 new_socket, inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
//         if (send(new_socket, "Hello World!!!\n", 15, 0) != 15) {
//                 perror("send failed");
//                 return (-1);
//         }
//         for (int i = 0; i < 30; i++) {
//                 if (clients[i] == 0) {
//                         clients[i] = new_socket;
//                         printf("Adding socket %d to list\n", new_socket);
//                         break;
//                 }
//         }
//         return (0);
// }

// int manage_client(int *client, struct sockaddr_in *addr)
// {
//         int retval = 0;
//         char str[1024] = {0};
//         int addrlen = sizeof(*addr);

//         if ((retval = read(*client, str, 1024)) == 0) {
//                 getpeername(*client, (struct sockaddr *)addr, (socklen_t *)&addrlen);
//                 printf("Host disconnected, ip %s, port %d \n", inet_ntoa(addr->sin_addr) , ntohs(addr->sin_port));
//                 close(*client);
//                 *client = 0;
//         } else {
//                 str[retval] = '\0';
//                 if (strcmp(str, "PASV") == 0)
//                         send(*client, "PASV command get\n", 17, 0);
//         }
//         return (0);
// }

// int check_client(fd_set *rfds, struct sockaddr_in *addr, int *clients)
// {
//         for (int i = 0; i < 30; i++) {
//                 if (FD_ISSET(clients[i], rfds))
//                         manage_client(&clients[i], addr);
//         }
//         return (0);
// }

struct sockaddr_in create_address(int port)
{
        struct sockaddr_in addr = {0};

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
        return (addr);
}

int main(int ac, char **av)
{
        fd_set rfds;
        int clients[30] = {0};
        struct sockaddr_in addr = create_address(atoi(av[1]));
        int master_sock = create_socket(&addr, 5);

        if (master_sock == -1)
                return (84);
        while (1) {
                if (manage_select(&rfds, master_sock, clients) < 0)
                        return (84);
                if (FD_ISSET(master_sock, &rfds)) {
                        if (incoming_connection(master_sock, &addr, clients) < 0)
                                return (84);
                } else
                        check_client(&rfds, &addr, clients);
        }
        close(master_sock);
        return (0);
}