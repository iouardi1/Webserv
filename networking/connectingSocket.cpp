/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectingSocket.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:44:20 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/24 20:47:30 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connectingSocket.hpp"

HDE::connectingSocket::connectingSocket(int domain, int service, int protocol, int port, u_long interface): mySocket(domain, service, protocol, port, interface)
{
	set_connection(connect_to_network(get_sock(), get_address()));
	test_connection(get_connection());
}

int HDE::connectingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	return (bind(sock, (struct sockaddr *)&address, sizeof(address)));
}