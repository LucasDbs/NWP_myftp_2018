/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** management.c
*/

#if !defined(FTP_H_)
#define FTP_H_

#include <sys/select.h>
#include "list.h"

int manage_select(fd_set *, int, /*int **/ client_s *);
client_s *manage_client(client_s *,/*int **/client_s *, struct sockaddr_in *);
client_s *check_client(fd_set *, struct sockaddr_in *, /*int **/ client_s *);
client_s *incoming_connection(int, struct sockaddr_in *, /*int **/ client_s *);
int print_usage(void);
int parsing(int, char **);

#endif // FTP_H_
