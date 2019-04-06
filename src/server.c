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
#include <string.h>
#include <errno.h>
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

struct sockaddr_in create_address(int port)
{
        struct sockaddr_in addr = {0};

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
        return (addr);
}

// int print_usage()
// {
//         printf("USAGE: ./myftp port path\n");
//         printf("\tport is the port number on which the server socket listens\n");
//         printf("\tpath is the path to the home directory for the Anonymous user\n");
//         return 0;
// }

// int parsing(int ac, char **av)
// {
//         if (ac != 3)
//                 return (84);
//         if (atoi(av[1]) == 0)
//                 return (84);
//         else
//                 return (0);
// }

int launch_server(int port)
{
        fd_set rfds;
        int clients[30] = {0};
        struct sockaddr_in addr = create_address(port);
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

int main(int ac, char **av)
{
        if (ac != 1 && strcmp(av[1], "-h") == 0) {
                print_usage();
                return (0);
        } else if (parsing(ac, av) == 84)
                return (84);
        else
                return (launch_server(atoi(av[1])));
}