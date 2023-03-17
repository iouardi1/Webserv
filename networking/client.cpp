/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:13:54 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/17 17:17:35 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client(): socket_server(-1)
{
    socket_responses.push_back(std::make_pair(std::make_pair(-1, false), Request()));
}

client::~client()
{
    
}

client::client(const client& copy)
{
    *this = copy;
}

client::client(int sock): socket_server(sock)
{
    socket_responses.push_back(std::make_pair(std::make_pair(-1, false), Request()));
}

client::client(int sock_res, bool flag, Request req)
{
    socket_responses.push_back(std::make_pair(std::make_pair(sock_res, flag), req));
}

client& client::operator=(const client& copy)
{
    socket_server = copy.socket_server;
    socket_responses = copy.socket_responses;
    return *this;
}


//* setters
void    client::set_socket_server(int socket_)
{
    socket_server = socket_;
}

void    client::set_socket_responses(int socket_, bool flag, Request client_request)
{
    socket_responses.push_back(std::make_pair(std::make_pair(socket_, flag), client_request));
}

void	client::set_sock_flag(bool flag, int index)
{
    socket_responses[index].first.second = flag;
}


//* getters
int client::get_socket_server() const
{
    return socket_server;
}

std::vector<std::pair<std::pair<int, bool>, Request> >   client::get_socket_responses() const
{
    return socket_responses;
}


bool	client::parse_request(std::string s, std::map<int, std::vector<ft::server> > m, int index)
{

	return (socket_responses[index].second.parse(get_socket_server(), s, m));
}

bool    client::get_sock_flag(int index) const
{
    return socket_responses[index].first.second;
}