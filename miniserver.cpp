/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserver.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:28 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/07 01:42:18 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <strings.h>
#include <sys/_types/_fd_def.h>
#include <sys/_types/_socklen_t.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <vector>
#include <arpa/inet.h>
#include <map>
#include "mySocket.hpp"

#define	BUFF_SIZE 1024
#define SOCKTERROR -1

int check(int exp, const char *msg)
{
	if (exp == SOCKTERROR)
	{
		perror (msg);
		exit(EXIT_FAILURE);
	}
	return (exp);
}

void	*handle_connection(int client_socket)
{
	char	buffer[BUFF_SIZE];
	size_t	bytes_read;
	int		msgsize = 0;
	char	actual_path[PATH_MAX + 1];

	//* read the client's msg -- the name of the file read
	while ((bytes_read = read(client_socket, buffer + msgsize, sizeof (buffer) - msgsize)))
	{
		msgsize += bytes_read;
		if (msgsize > BUFF_SIZE - 1)
			break ;
	}
	check(bytes_read, "recv error");
	buffer[msgsize - 1] = '\0'; // null terminate the msg and remove the \n
	std::cout << "REQUEST: " << buffer << std::endl;
	
	//* validity check
	if (realpath(buffer, actual_path) == NULL) 
	{
		std::cout << "ERROR(bad path): " << buffer << std::endl;
		close(client_socket);
		return NULL;
	}

	//* read the file and send its contents to client
	FILE *fp = fopen(actual_path, "r");
	if (fp == NULL)
	{
		std::cout << "ERROR(open): " << buffer << std::endl;
		close(client_socket);
		return NULL;
	}
	while ((bytes_read = fread(buffer, 1, BUFF_SIZE, fp)) > 0)
		write (client_socket, buffer, bytes_read);
	close(client_socket);
	fclose(fp);
	std::cout << "closing connection" << std::endl;
	return NULL;
}

int accept_new_connection(int server_fd)
{
	int		addr_size = sizeof(sockaddr_in);
	int		client_socket;
	struct sockaddr_in	client_addr;
	check(client_socket = accept(server_fd, (sockaddr *)&client_addr, (socklen_t *)&addr_size), "accept failed");
	return client_socket;
}

int	max_server_fd(std::map<int, int> server_fd, int max_fd)
{
	for (int i = 0; i < server_fd.size(); i++)
	{
		if (server_fd[i] > max_fd)
			max_fd = server_fd[i];
	}
	return max_fd;
}

int	check_server_fd(std::map<int, int> *server_fd, int fd)
{
	for (std::map<int, int>::iterator itr = server_fd->begin(); itr != server_fd->end(); itr++)
	{
		if (itr->first == fd)
		{
			itr->second = false;
			return fd;
		}
	}
	return -1;
}

int main()
{
	mySocket	mysock(8000, "127.0.0.1");
	std::vector<std::pair<int, std::string> > obj;

	obj.insert(obj.begin(), std::make_pair(8000, "127.0.0.1"));
	obj.insert(obj.begin() + 1, std::make_pair(8001, "127.0.0.1"));
	obj.insert(obj.begin() + 2, std::make_pair(8002, "127.0.0.1"));


	for (std::vector<std::pair<int, std::string> >::iterator itr = obj.begin(); itr != obj.end(); itr++)
	{
		mysock.set_port_and_ip(itr->first, itr->second);
		mysock.createServer_socket();
	}
	
	mysock.accept_client_request();

	
	// // int server_fd[1024];
	// struct sockaddr_in	addr;
	// std::vector<std::pair<int, std::string> > obj;

	// obj.insert(obj.begin(), std::make_pair(8000, "127.0.0.1"));
	// obj.insert(obj.begin() + 1, std::make_pair(8001, "127.0.0.1"));
	// obj.insert(obj.begin() + 2, std::make_pair(8002, "127.0.0.1"));
	// std::vector<std::pair<int, int> > server_fd;
	// // std::map<int, int> server_fd;


	// memset((char  *)&addr, 0, sizeof(struct sockaddr));
	// int i = 0;
	// for (std::vector<std::pair<int, std::string> >::iterator itr = obj.begin(); itr != obj.end(); itr++)
	// {
	// 	addr.sin_family = AF_INET;
	// 	addr.sin_addr.s_addr = inet_addr(itr->second.c_str());
	// 	addr.sin_port = htons(itr->first);

	// 	server_fd[i].push_back(std::make_pair((int)socket(AF_INET, SOCK_STREAM, 0), 1));
	// 	if ((server_fd[i] = (int)(socket(AF_INET, SOCK_STREAM, 0))) < 0)
	// 	{
	// 		perror("failes to create the socket");
	// 		return -1;
	// 	}
		
	// 	if (bind(server_fd[i], (struct sockaddr *)&addr, sizeof(addr)) < 0)
	// 	{
	// 		perror("failes to bind");
	// 		return -2;
	// 	}
		
	// 	if (listen(server_fd[i], 10) < 0)
	// 	{
	// 		perror("failes to listen");
	// 		return -3;
	// 	}
	// 	i++;
	// }
	
	// fd_set	read_fds, write_fds, current_socket;
	// FD_ZERO(&current_socket);
	// FD_SET(server_fd[0], &current_socket);
	// // socklen_t	client_addr_len;
	// // FD_SET(server_fd, &read_fds);
	// int max_fd = max_server_fd(server_fd, max_fd);
	// // 				int flag = 0;
	// while (1)
	// {
	// 	read_fds = current_socket;
	// 	if (select(max_fd + 1, &read_fds, &write_fds, NULL, NULL) < 0)
	// 	{
	// 		perror("select error");
	// 		exit(EXIT_FAILURE);
	// 	}
		
	// 	for (int i = 0; i <= max_fd; ++i)
	// 	{
	// 		if (FD_ISSET(i,  &read_fds))
	// 		{
	// 			if (i == check_server_fd(&server_fd, i))
	// 			{
	// 				//* new connection
	// 				int client_socket = accept_new_connection(i);
	// 				FD_SET(client_socket, &current_socket);
	// 				FD_CLR(i, &current_socket);
	// 				max_fd = ((max_fd > client_socket) ? max_fd : client_socket);
	// 			}
	// 			else
	// 			{
	// 				handle_connection(i);
	// 				FD_CLR(i, &current_socket);
	// 			}
	// 		}
	// 	}
	// }
			//* wait for i/o events with a zero timeout;
			// int	num_ready = select(max_fd + 1, &read_fds, &write_fds, NULL, NULL);

			// if (num_ready == -1)
			// {
			// 	perror("select");
			// 	exit(EXIT_FAILURE);
			// }
			// else if (num_ready == 0)
			// {
			// 	std::cout << "no events to process" << std::endl;
			// 	continue;
			// }
			// else
			// {
				//* check which file descriptor have events
				// if (FD_ISSET(server_fd, &read_fds))
				// {
					/*  a new client connection has been made */
					// for (int i = 0; i <= max_fd; ++i)
					// {
					// 	if (flag == 0)
					// 	{
					// 		new_socket = accept(server_fd, NULL, NULL);
					// 		flag = 1;
					// 		FD_SET(new_socket, &read_fds);
					// 		max_fd = ((max_fd > new_socket) ? max_fd : new_socket);
					// 		// perror("accept");
					// 		// close (server_fd);
					// 		// exit(EXIT_FAILURE);
					// 	}
					// 	//* add the new client socket to the read list
		
					// //*  loop through the client sockets to check for incoming data
					// 	else
					// 	{
					// 		if (FD_ISSET(i, &read_fds))
					// 		{
					// 			//* incoming data from this socket
					// 			char	buffer[1024];
					// 			int num_bytes = recv(i, buffer, sizeof(buffer), 0);
					// 			if (num_bytes == -1)
					// 			{
					// 				perror("recv");
					// 				exit(EXIT_FAILURE);
					// 			}
					// 			else if (num_bytes == 0)
					// 			{
					// 				//* client deconnected, remove the socket from the read list
					// 				FD_CLR(i, &read_fds);
					// 				close(i);
					// 			}
					// 			else
					// 			{
					// 				//* process the incoming data
					// 				FD_ISSET(i, &write_fds);
					// 			}
					// 		}
					// 		else if (FD_ISSET(i, &write_fds))
					// 		{
					// 			const char	*hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
					// 			write(i, hello, strlen(hello));
					// 		}
					// 	}
				// int		addr_size = sizeof(sockaddr_in);
				// int		client_socket;
				// struct sockaddr_in	client_addr;
				// check(client_socket = accept(server_fd, (sockaddr *)&client_addr, (socklen_t *)&addr_size), "accept failed");
				// handle_connection(server_fd);
				// SO_REUSEADDR;
			std::cout << "\n next client" << std::endl;
			return 0;
		}
			

			//*send and receive messages
		// 	char	buffer[30000] = {0};
		// 	int		valread = read(new_socket, buffer, 30000);
		// 	//* that's the buffer should be parsed   <3   aka  rania*//
		// 	std::cout << buffer << std::endl;
		// 	if  (valread < 0)
		// 		perror("nothing to read");
		// 	//* hello should be filled by the response aka hasnaa *//
		// 	const char	*hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
		// 	write(new_socket, hello, strlen(hello));
		// 	close(new_socket);
		// }

	//* and here i created a miniserver that can take multiple requests at the same time *//

