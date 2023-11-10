/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mySocket.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:52:35 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/18 18:52:37 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mySocket.hpp"

mySocket::mySocket(): m_port(0), flag(0), ip(NULL), m_server_fd(0), m_new_socket(0), flags(0), m_server_address()
{
    
}
mySocket::mySocket(const mySocket& copy)
{
    *this = copy;
}
mySocket& mySocket::operator=(const mySocket& copy)
{
    m_port           = copy.m_port;
    flag             = copy.flag;
    ip               = copy.ip;
    m_server_fd      = copy.m_server_fd;
    m_new_socket     = copy.m_new_socket;
    flags            = copy.flags;
    m_server_address = copy.m_server_address;
    return *this;
}
mySocket::~mySocket()
{
    
}


//* constructor
mySocket::mySocket(int port, std::string ip) : m_port(port), flag(0), ip(ip), m_server_fd(0), m_new_socket(0), flags(0), m_server_address()
{
    
}


//* setters
void	mySocket::set_port_and_ip(int port, std::string _ip)
{
    m_port = port;
    ip = _ip;
}

void	mySocket::set_new_socket(int new_socket)
{
    m_new_socket = new_socket;
}

void	mySocket::set_server_fd(int i)
{
    flag = i;
}


//* getters
int	mySocket::get_new_socket() const
{
    return m_new_socket;
}

int mySocket::get_server_fd() const
{
    return m_server_fd;
}

struct sockaddr_in mySocket::get_server_address() const
{
    return m_server_address;
}

int	mySocket::get_flag() const
{
    return flag;
}

int	mySocket::get_port() const
{
    return m_port;
}


//* useful member functions
void mySocket::createServer_socket()
{
    // create server socket
    m_server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_fd == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // set socket options
    int opt = 1;
    if (setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // bind server socket to port
    m_server_address.sin_family = AF_INET;
    m_server_address.sin_addr.s_addr = inet_addr(ip.c_str());
    m_server_address.sin_port = htons(m_port);
    if (bind(m_server_fd, (struct sockaddr *) &m_server_address, sizeof(m_server_address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // listen for client connections
    if (listen(m_server_fd, 1000) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    // set server socket to non-blocking mode
    flags = fcntl(m_server_fd, F_GETFL, 0);
    fcntl(m_server_fd, F_SETFL, flags | O_NONBLOCK);
}
