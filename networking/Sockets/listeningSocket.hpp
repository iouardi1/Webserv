/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeningSocket.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:54:26 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/24 22:56:20 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENINGSOCKET_HPP
#define LISTENINGSOCKET_HPP
#include "bindingSocket.hpp"


namespace HDE
{
	class   listeningSocket: public BindingSocket
	{
		private:
			int	backlog;
			int	listening;
		public:
			listeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg);
			void	start_listening();
	};
}


#endif /* LISTENINGSOCKET_HPP */
