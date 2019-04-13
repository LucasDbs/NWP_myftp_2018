/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** server.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "list.h"

int print_list(client_s *head)
{
        client_s *tmp = head;

        while (tmp) {
                printf("list->port = %d\n", tmp->port);
                tmp = tmp->next;
        }
        return (0);
}

client_s *create_node(int port)
{
        client_s *new = malloc(sizeof(client_s));

        new->port = port;
        new->data = 0;
        new->username = false;
        new->passw = false;
        new->next = NULL;
        return (new);
}

int add_node(client_s *head, int port)
{
        client_s *new = NULL;
        client_s *tmp = head;

        if (!head)
                return (0);
        else {
                new = create_node(port);
                while (tmp->next)
                        tmp = tmp->next;
                tmp->next = new;
        }
        return (0);
}

int delete_node(client_s **head, client_s *to_delete)
{
        client_s *tmp = *head;
        client_s *prev = NULL;

        if (tmp == to_delete) {
                *head = tmp->next;
                free(tmp);
                return (0);
        }
        while (tmp) {
                prev = tmp;
                tmp = tmp->next;
                if (tmp == to_delete) {
                        prev->next = tmp->next;
                        free(tmp);
                        return (0);
                }
        }
        return (0);
}

int destroy_list(client_s *head)
{
        client_s *tmp = head;
        client_s *prev = NULL;

        while (tmp) {
                prev = tmp;
                tmp = tmp->next;
                free(prev);
        }
        return (0);
}
