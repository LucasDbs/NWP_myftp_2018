/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** management.c
*/

#if !defined(LIST_H_)
#define LIST_H_

#include <stdbool.h>
#include <sys/select.h>

typedef struct clients_t
{
        int port;
        int data;
        bool username;
        bool passw;
        struct clients_t *next;
} client_s;

int print_list(client_s *head);
client_s *create_node(int port);
int add_node(client_s *head, int port);
int delete_node(client_s **head, client_s *to_delete);
int destroy_list(client_s *head);

#endif
