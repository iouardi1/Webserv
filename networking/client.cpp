/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:13:54 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/19 15:32:41 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client(): socket_server(-1), flag(0)
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

client::client(int sock): socket_server(sock), flag(0)
{
    socket_responses.push_back(std::make_pair(std::make_pair(-1, false), Request()));
}

client::client(int sock_res, bool flag, Request req): flag(0)
{
    socket_responses.push_back(std::make_pair(std::make_pair(sock_res, flag), req));
}

client& client::operator=(const client& copy)
{
    socket_server = copy.socket_server;
    socket_responses = copy.socket_responses;
    flag = copy.flag;
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

bool	client::setRequestEnd_(bool x, int index)
{
    socket_responses[index].second.setRequestEnd(x);
    return (x);
}

bool    client::get_sock_flag(int index) const
{
    return socket_responses[index].first.second;
}

void	client::set_resp_message(std::string msg)
{
    resp_message = msg;
}

std::string client::get_resp_message() const
{
    return resp_message;
}

void	client::setFlag(int flag)
{
    this->flag = flag;
}

int	client::getFlag() const
{
    return flag;
}

void    client::remove_sock(int index)
{
    socket_responses.erase(socket_responses.begin() + index);
}