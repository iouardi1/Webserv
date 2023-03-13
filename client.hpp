/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:32:24 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/13 22:55:23 by iouardi          ###   ########.fr       */
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
        client(): socket(-1), client_request()
        {}
        ~client()
        {}
        client(const client& copy)
        {
            *this = copy;
        }
        client(int sock): socket(sock), client_request()
        {}
        client& operator=(const client& copy)
        {
            socket = copy.socket;
            client_request = copy.client_request;
            return *this;
        }
        //* setters
        void set_socket(int socket_)
        {
            socket = socket_;
        }
        
        void set_client_request(const Request client)
        {
            client_request = client;
        }

        //* getters
        int get_socket() const
        {
            return socket;
        }
        
        Request get_client_request() const
        {
            return client_request;
        }
};


#endif /* AED5C75D_038B_4348_9995_2FD3969B7DA0 */
