/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mySocket.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:22:49 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/15 00:13:01 by iouardi          ###   ########.fr       */
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
#include <fcntl.h>
#include <map>

class mySocket
{
	private:
		int 					m_port;
		int						flag;
		std::string				ip;
		int 					m_server_fd;
		int 					m_new_socket;
		int 					flags;
		struct sockaddr_in 		m_server_address;//need to set some setters for these two depends on the ips i wanna listen to
	
	public:

		//* canonical form
		mySocket();
		mySocket(const mySocket& copy);
		mySocket& 			operator=(const mySocket& copy);
		~mySocket();


		//* constructor
    	explicit 			mySocket(int port, std::string ip);

		
		//* setters
		void				set_port_and_ip(int port, std::string _ip);
		void				set_new_socket(int new_socket);
		void				set_server_fd(int i);
		

		//* getters
		int					get_new_socket() const;
		int					get_server_fd() const;
		struct sockaddr_in	get_server_address() const;
		int					get_flag() const;
		struct sockaddr_in& get_client_address() const;
		socklen_t&			get_addrlen() const;
		int					get_port() const;


		//* useful member functions
		void				createServer_socket();
};

#endif /* MYSOCKET_HPP */

/// fcntl: The fcntl function can be used to set the file 
/// descriptor flags for a file or socket. By setting the
/// O_NONBLOCK flag, you can make the file descriptor 
/// non-blocking. This means that read and write operations
/// will return immediately, even if there is no data available
/// to read or the write buffer is full.





/*  fd_set read_fds;
    int max_sd;
    int sd, new_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);
    char buffer[1024];

    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(server_socket, &read_fds);
        max_sd = server_socket;

        for (int i = 0; i < client_sockets.size(); i++) {
            sd = client_sockets[i];
            if (sd > 0) {
                FD_SET(sd, &read_fds);
                if (sd > max_sd) {
                    max_sd = sd;
                }
            }
        }

        if (select(max_sd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("select failed");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(server_socket, &read_fds)) {
            if ((new_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length)) < 0) {
                perror("accept failed");
                exit(EXIT_FAILURE);
            }
            std::cout << "New connection from " << inet_ntoa(client_address.sin_addr) << ":" << ntohs(client_address.sin_port) << std::endl;
            client_sockets.push_back(new_socket);
        }

        for (int i = 0; i < client_sockets.size(); i++) {
            sd = client_sockets[i];
            if (FD_ISSET(sd, &read_fds)) {
                if (read(sd, buffer, 1024) == 0) {
                    std::cout << "Client " << sd << " disconnected" << std::endl;
                    close(sd);
                    client_sockets.erase(client_sockets.begin() + i);
                } else {
                    std::cout << "Client " << sd << " sent message: " << buffer << std::endl;
                    send(sd, "Message received", strlen("Message received"), 0);
                }
            }
        }
    }

    return 0;
}*/

/*fd_set read_fds;
FD_ZERO(&read_fds);
FD_SET(fd, &read_fds);

struct timeval timeout;
timeout.tv_sec = 0;
timeout.tv_usec = 0;

int ready_fds = select(fd + 1, &read_fds, NULL, NULL, &timeout);
if (ready_fds == -1) {
    perror("select");
} else if (ready_fds > 0) {
    char buffer[1024];
    ssize_t n = read(fd, buffer, sizeof(buffer));
    if (n == -1) {
        perror("read");
    } else {
        std::cout << "Read " << n << " bytes: " << buffer << std::endl;
    }
} else {
    std::cout << "No data available to read" << std::endl;
}*/


/*for (int i = 0; i < myServers.size(); i++)
        {
            if (FD_ISSET(myServers[i].get_server_fd(), &read_fds))
            {
                mySocket new_sock = myServers[i].accept_client_request();
                if (new_sock.get_new_socket() < 0)
                {
                    perror("Accept failed");
                    exit(EXIT_FAILURE);
                }

                char buffer[1024] = {0};
                int valread = read(new_sock.get_new_socket(), buffer, 1024);
                std::cout << "Received: " << buffer << std::endl;

                const char *message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
                write(new_sock.get_new_socket(), message, strlen(message));
                std::cout << "Sent: " << message << std::endl;

                new_sock.close_socket();
            }
        }*/