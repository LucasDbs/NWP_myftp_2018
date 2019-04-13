/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** parsing.c
*/

#include <stdlib.h>
#include <stdio.h>

int print_usage(void)
{
	printf("USAGE: ./myftp port path\n");
	printf("\tport is the port number on which the server socket listens\n");
	printf("\tpath is the path to the home directory for the Anonymous user\n");
	return (0);
}

int parsing(int ac, char **av)
{
	if (ac != 3)
		return (84);
	if (atoi(av[1]) == 0)
		return (84);
	else
		return (0);
}
