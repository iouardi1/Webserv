/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:32:24 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/15 00:19:03 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AED5C75D_038B_4348_9995_2FD3969B7DA0
#define AED5C75D_038B_4348_9995_2FD3969B7DA0

#include "CURRENT/http.hpp"
#include "CURRENT/server.hpp"
#include "CURRENT/Request.hpp"
#include "CURRENT/location.hpp"

class   client
{
    private:
        int         socket;
        Request     client_request;

    public:
        client();
        ~client();
        client(const client& copy);
        client(int sock);
        client& operator=(const client& copy);


        //* setters
        void    set_socket(int socket_);
        void    set_client_request(const Request client);

    
        //* getters
        int     get_socket() const;
        Request get_client_request() const;
};


#endif /* AED5C75D_038B_4348_9995_2FD3969B7DA0 */
