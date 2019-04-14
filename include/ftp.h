/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** management.c
*/

#if !defined(FTP_H_)
#define FTP_H_

#include "list.h"

int manage_select(fd_set *, int, client_s *);
client_s *manage_client(client_s *, client_s *, struct sockaddr_in *);
client_s *check_client(fd_set *, struct sockaddr_in *, client_s *);
client_s *incoming_connection(int, struct sockaddr_in *, client_s *);
int print_usage(void);
int parsing(int, char **);
int check_command(char *, client_s *);

#endif
