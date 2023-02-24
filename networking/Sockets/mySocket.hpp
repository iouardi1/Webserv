/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mySocket.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:22:49 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/24 20:35:05 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSOCKET_HPP
#define MYSOCKET_HPP
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

namespace  HDE
{
	class mySocket
	{
		private:
			struct  sockaddr_in		address;
			int						sock;
			int						connection;
		public:
			mySocket(int domain, int service, int protocol, int port, u_long interface);
			//* virtual function to coonnect to a network interface
			virtual	int connect_to_network(int sock, struct sockaddr_in address) = 0;
			void	test_connection(int);
			//* getter functions
			struct	sockaddr_in get_address() const;
			int	get_sock() const;
			int get_connection() const;
			//* setter functions
			void set_connection(int);
	};
}

#endif /* MYSOCKET_HPP */
