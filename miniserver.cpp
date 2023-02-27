/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserver.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:28 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/28 00:19:25 by iouardi          ###   ########.fr       */
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


int main()
{
	int server_fd;
	struct sockaddr_in	addr;
	const int port =  8000;

	memset((char  *)&addr, 0, sizeof(struct sockaddr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("failes to create the socket");
		return -1;
	}
	
	if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("failes to bind");
		return -2;
	}
	
	if (listen(server_fd, 2) < 0)
	{
		perror("failes to listen");
		return -3;
	}
	
	int new_socket;
	struct sockaddr_in	client_addr;
	socklen_t	client_addr_len;
	while (1)
	{
		std::cout << "\n-----------waiting for new client---------------\n" << std::endl;
		if ((new_socket = accept(server_fd, (sockaddr *)&client_addr, &client_addr_len)) < 0)
		{
			perror("accept");
			close (server_fd);
			exit(EXIT_FAILURE);
		}
		

		//*send and receive messages
		char	buffer[30000] = {0};
		int		valread = read(new_socket, buffer, 30000);
		//* that's the buffer should be parsed   <3   aka  rania*//
		std::cout << buffer << std::endl;
		if  (valread < 0)
			perror("nothing to read");
		//* hello should be filled by the response aka hasnaa *//
		const char	*hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
		write(new_socket, hello, strlen(hello));
		close(new_socket);
	}

	//* and here i created a miniserver that can take multiple requests at the same time *//

	return 0;
}