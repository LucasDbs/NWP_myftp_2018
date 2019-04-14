/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** other_command.c
*/

#include <unistd.h>
#include "list.h"

int other_command(char *command, client_s *client)
{
    (void)command;

    if (client->username == true && client->passw == true)
        return (0);
    else {
        write(client->port, "500 Client not logged\n", 23);
        return (84);
    }
}