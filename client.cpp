/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:13:54 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/15 00:21:00 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client(): socket(-1), client_request()
{
    
}

client::~client()
{
    
}

client::client(const client& copy)
{
    *this = copy;
}

client::client(int sock): socket(sock), client_request()
{
    
}

client& client::operator=(const client& copy)
{
    socket = copy.socket;
    client_request = copy.client_request;
    return *this;
}


//* setters
void    client::set_socket(int socket_)
{
    socket = socket_;
}

void    client::set_client_request(const Request client)
{
    client_request = client;
}


//* getters
int client::get_socket() const
{
    return socket;
}

Request client::get_client_request() const
{
    return client_request;
}