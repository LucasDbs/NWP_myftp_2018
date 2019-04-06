/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** management.c
*/

#if !defined(FTP_H_)
#define FTP_H_

#include <sys/select.h>

int manage_select(fd_set *, int, int *);
int manage_client(int *, struct sockaddr_in *);
int check_client(fd_set *, struct sockaddr_in *, int *);
int incoming_connection(int, struct sockaddr_in *, int *);

#endif // FTP_H_
