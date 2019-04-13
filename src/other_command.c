/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** other_command.c
*/

#include <unistd.h>
#include "list.h"

int clean_str(char *str)
{
        int i = 0;

        while (str[i]) {
                if (str[i] == '\n') {
                        str[i] = '\0';
                        return (0);
                }
                i++;
        }
        return (0);
}

int other_command(char *command, client_s *client)
{
        (void)command;

        if (client->username == true && client->passw == true)
                return (0);
        else {
                write(client->port, "500 Client not logged", 22);
                return (84);
        }
}