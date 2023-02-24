/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectingSocket.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:44:52 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/24 20:50:29 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNCTINGSOCKET_HPP
#define CONNCTINGSOCKET_HPP
#include <iostream>
#include "mySocket.hpp"

namespace HDE
{
	class connectingSocket: public mySocket
	{
		public:
			connectingSocket(int domain, int service, int protocol, int port, u_long interface);
			int connect_to_network(int sock, struct sockaddr_in address);
	};
}

#endif /* CONNCTINGSOCKET_HPP */
