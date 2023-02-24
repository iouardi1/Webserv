/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindingSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:21:21 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/24 21:33:22 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGSOET_HPP
#define BINDINGSOET_HPP
#include <iostream>
#include "mySocket.hpp"

namespace HDE
{
	class BindingSocket: public mySocket
	{
		public:
			BindingSocket(int domain, int service, int protocol, int port, u_long interface);
			int connect_to_network(int sock, struct sockaddr_in address);
	};
}

#endif /* BINDINGSOET_HPP */
