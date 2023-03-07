/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mySocket.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:22:59 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/06 23:58:35 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mySocket.hpp"

HDE::mySocket::mySocket(int domain, int service, int protocol, int port, u_long interface)
{
	//* define address structure
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);
	//* establish socket
	sock = socket(domain, service, protocol);
	test_connection(sock);
	//* establish connection
	// connection = connect_to_network(sock, address);
	test_connection(connection);
}

void	HDE::mySocket::test_connection(int item_to_test)
{
	if (item_to_test < 0)
	{
		perror("Failed to connect");
		exit (EXIT_FAILURE);
	}
}

struct sockaddr_in	HDE::mySocket::get_address() const
{
	return (address);
}

int	HDE::mySocket::get_sock() const
{
	return (sock);
}

int	HDE::mySocket::get_connection() const
{
	return (connection);
}

void	HDE::mySocket::set_connection(int conn)
{
	connection = conn;
}

int	HDE::mySocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface)
{
	set_connection(connect_to_network(get_sock(), get_address()));
	return (bind(sock, (struct sockaddr *)&address, sizeof(address)));
}

int	HDE::mySocket::listeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg)
{
    set_connection(connect_to_network(get_sock(), get_address()));
 	return (listen(get_connection(), bklg));
}
