/*
 * @Author: Lucas Duboisse 
 * @Date: 2019-04-01 13:36:47 
 * @Last Modified by: Lucas Duboisse
 * @Last Modified time: 2019-04-01 16:58:49
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>

int main(int ac, char **av)
{
        fd_set rfds;
        int retval = 0;
        int clients[30] = {0};
        int max = 0;

        int master_sock = socket(PF_INET, SOCK_STREAM, 0);
        struct sockaddr_in addr = {0};
        int new_socket = 0;
        char str[1000] = {0};
        int addrlen = sizeof(addr);

        if (master_sock == -1) {
                perror("socket failed");
                exit(errno);
        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(atoi(av[1]));
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(master_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("bind failed");
                exit(EXIT_FAILURE);
        }
        if (listen(master_sock, 5) < 0) {
                perror("listen failed");
                exit(EXIT_FAILURE);
        }
        // FD_ZERO(&rfds);
        // FD_SET(master_sock, &rfds);
        while (1) {
                FD_ZERO(&rfds);
                FD_SET(master_sock, &rfds);
                max = master_sock;

                for (int i = 0; i < 30; i++) {
                        if (clients[i] > 0)
                                FD_SET(clients[i], &rfds);
                        if (clients[i] > max)
                                max = clients[i];
                }
                if ((retval = select(max + 1, &rfds, NULL, NULL, NULL)) < 0) {
                        perror("select failed");
                        exit(EXIT_FAILURE);
                }
                if (FD_ISSET(master_sock, &rfds)) {
                        if ((new_socket = accept(master_sock, (struct sockaddr *)&addr, (socklen_t *)&addrlen)) < 0) {
                                perror("accept failed");
                                exit(EXIT_FAILURE);
                        }
                        printf("New connection, socket fd is: %d, ip is: %s, port is: %d\n",
                                new_socket, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
                        if (send(new_socket, "Hello World!!!\n", 15, 0) != 15) {
                                perror("send failed");
                                exit(EXIT_FAILURE);
                        }
                        for (int i = 0; i < 30; i++) {
                                if (clients[i] == 0) {
                                        clients[i] = new_socket;
                                        printf("Adding socket %d to list\n", new_socket);
                                        break;
                                }
                        }
                        // FD_SET(new_socket, &rfds);
                } else {
                        for (int i = 0; i < 30; i++) {
                                if (FD_ISSET(clients[i], &rfds)) {
                                        if ((retval = read(clients[i], str, 1000)) == 0) {
                                                getpeername(clients[i], (struct sockaddr *)&addr, (socklen_t *)&addrlen);
                                                printf("Host disconnected, ip %s, port %d \n", inet_ntoa(addr.sin_addr) , ntohs(addr.sin_port));
                                                close(clients[i]);
                                                clients[i] = 0;
                                        } else {
                                                str[retval] = '\0';
                                                send(clients[i], str, strlen(str), 0);
                                        }
                                }
                        }
                }
        }
        close(master_sock);
        return (0);
}