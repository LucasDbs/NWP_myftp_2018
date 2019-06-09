/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** auth_command.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

int user_command(client_s *client, char *str)
{
    if (strcmp(str, "Anonymous\r\n") == 0) {
        client->username = true;
        write(client->port, "331\n", 4);
    } else
        write(client->port, "500\n", 4);
    return (0);
}

int passw_command(client_s *client, char *str)
{
    if (strcmp(str, "\r\n") == 0) {
        client->passw = true;
        write(client->port, "230\n", 4);
    } else
        write(client->port, "500\n", 4);
    return (0);
}

char *arg_command(char *src)
{
    char *dest = malloc(sizeof(char) * (strlen(src) + 1));
    int i = 0;
    int a = 0;

    while (src[i] != ' ' && src[i])
        i++;
    if (src[i] == ' ')
        i++;
    while (src[i])
        dest[a++] = src[i++];
    dest[i] = '\0';
    return (dest);
}

char *get_command(char *src)
{
    char *dest = malloc(sizeof(char) * (strlen(src) + 1));
    int i = 0;

    if (!src || !dest)
        return (NULL);
    while (src[i] != ' ' && src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int check_command(char *str, client_s *client)
{
    char *res = get_command(str);

    if (!res) {
        write(client->port, "530\n", 4);
        return (0);
    }
    if (strcmp(res, "USER") == 0)
        user_command(client, arg_command(str));
    else if (strcmp(res, "PASS") == 0)
        passw_command(client, arg_command(str));
    else
        other_command(res, client);
    free(res);
    return (0);
}