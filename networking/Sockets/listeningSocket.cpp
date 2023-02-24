/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeningSocket.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:54:14 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/24 23:03:12 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listeningSocket.hpp"

HDE::listeningSocket::listeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg): BindingSocket(domain, service, protocol, port, interface)
{
    set_connection(connect_to_network(get_sock(), get_address()));
    backlog = bklg;
    start_listening();
    std::cout << "3\n";
    test_connection(listening);
}

void    HDE::listeningSocket::start_listening()
{
    std::cout << "1\n";
    listening = listen(get_connection(), backlog);
    std::cout << "2\n";
}