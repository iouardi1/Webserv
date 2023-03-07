/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mySocket.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:22:49 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/07 01:36:24 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSOCKET_HPP
#define MYSOCKET_HPP
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

class mySocket
{
	private:
		int m_port;
		std::string	ip;
		int m_server_fd;
		int m_new_socket;
		struct sockaddr_in m_server_address;//need to set some setters for these two depends on the ips i wanna listen to
		struct sockaddr_in m_client_address;//need to set some setters for these two depends on the ips i wanna listen to
		socklen_t m_addrlen;

	public:
    	explicit mySocket(int port, std::string ip) : m_port(port), ip(ip), m_server_fd(0), m_new_socket(0), m_server_address(), m_client_address(), m_addrlen(sizeof(m_client_address)) {}


		void set_port_and_ip(int port, std::string _ip)
		{
			m_port = port;
			ip = _ip;
		}
	
		void createServer_socket()
		{
			// create server socket
			m_server_fd = socket(AF_INET, SOCK_STREAM, 0);
			if (m_server_fd == 0)
			{
				perror("Socket creation failed");
				exit(EXIT_FAILURE);
			}

			// set socket options
			int opt = 1;
			if (setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
				perror("Setsockopt failed");
				exit(EXIT_FAILURE);
			}

			// bind server socket to port
			m_server_address.sin_family = AF_INET;
			m_server_address.sin_addr.s_addr = inet_addr(ip.c_str());
			m_server_address.sin_port = htons(m_port);
			if (bind(m_server_fd, (struct sockaddr *) &m_server_address, sizeof(m_server_address)) < 0)
			{
				perror("Bind failed");
				exit(EXIT_FAILURE);
			}

			// listen for client connections
			if (listen(m_server_fd, 100) < 0)
			{
				perror("Listen failed");
				exit(EXIT_FAILURE);
			}
		}
		void	accept_client_request()
		{

			std::cout << "Server listening on port " << m_port << std::endl;

			// accept client connections
			while (true) 
			{
				m_new_socket = accept(m_server_fd, (struct sockaddr *) &m_client_address, &m_addrlen);
				if (m_new_socket < 0) 
				{
					perror("Accept failed");
					exit(EXIT_FAILURE);
				}

				char buffer[1024] = {0};
				int valread = read(m_new_socket, buffer, 1024);
				std::cout << "Received: " << buffer << std::endl;
				const char *message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
				write(m_new_socket, message, strlen(message));
				// std::cout << "Sent: " << message << std::endl;

				close(m_new_socket);
			}
		}
};

#endif /* MYSOCKET_HPP */
