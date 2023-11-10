/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mySocket.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:22:49 by iouardi           #+#    #+#             */
/*   Updated: 2023/04/02 03:04:04 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSOCKET_HPP
#define MYSOCKET_HPP
#include <iostream>
#include <string>
#include <strings.h>
// #include <sys/_types/_fd_def.h>
// #include <sys/_types/_socklen_t.h> //edited this
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
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
