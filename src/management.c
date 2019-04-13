/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** management.c
*/

#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include "ftp.h"

int manage_select(fd_set *rfds, int sock, client_s *head)
{
	int max = sock;
	client_s *tmp = head;

	FD_ZERO(rfds);
	FD_SET(sock, rfds);
	while (tmp) {
		FD_SET(tmp->port, rfds);
		if (tmp->port > max)
			max = tmp->port;
		tmp = tmp->next;
	}
	if (select(max + 1, rfds, NULL, NULL, NULL) < 0) {
		perror("select failed");
		return (-1);
	}
	return (0);
}

client_s *manage_client(client_s *head, client_s *client, struct sockaddr_in *addr)
{
	int retval = 0;
	char str[1024] = { 0 };
	int addrlen = sizeof(*addr);

	if ((retval = read(client->port, str, 1024)) == 0) {
		getpeername(client->port, (struct sockaddr *)addr,
			(socklen_t *)&addrlen);
		printf("Host disconnected, ip %s, port %d \n",
		       	inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
		close(client->port);
		delete_node(&head, client);
	} else {
		str[retval] = '\0';
		if (strcmp(str, "PASV") == 0)
			write(client->port, "PASV command get\n", 17);
	}
	return (head);
}

client_s *check_client(fd_set *rfds, struct sockaddr_in *addr, client_s *head)
{
	client_s *tmp = head;

	while (tmp) {
		if (FD_ISSET(tmp->port, rfds)) {
			head = manage_client(head, tmp, addr);
			return (head);
		}
		tmp = tmp->next;
	}
	return (head);
}

client_s *incoming_connection(int sock, struct sockaddr_in *addr, client_s *head)
{
	int new_socket = 0;
	int addrlen = sizeof(*addr);

	if ((new_socket = accept(sock, (struct sockaddr *)addr, (socklen_t *) & addrlen)) < 0) {
		perror("accept failed");
		return (NULL);
	}
	write(new_socket, "220", 3);
	if (!head)
		head = create_node(new_socket);
	else
		add_node(head, new_socket);
	return (head);
}