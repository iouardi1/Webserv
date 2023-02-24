/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindingSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:20:40 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/24 20:40:50 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindingSocket.hpp"

HDE::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface): mySocket(domain, service, protocol, port, interface)
{
	set_connection(connect_to_network(get_sock(), get_address()));
	test_connection(get_connection());
}

int HDE::BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	return (bind(sock, (struct sockaddr *)&address, sizeof(address)));
}