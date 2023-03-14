/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserver.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:28 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/14 22:49:49 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>
#include <strings.h>
#include <sys/_types/_fd_def.h>
#include <sys/_types/_socklen_t.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <vector>
#include <arpa/inet.h>
#include <map>
#include "mySocket.hpp"
#include "client.hpp"


std::vector<std::string>    get_tokens(std::string line, std::string delimiter)
{
  size_t                      _start = 0;
  size_t                      _end = 0;
  std::string                 token;
  std::vector<std::string>    tokens;

  if (delimiter == " ")
    line.push_back(delimiter[0]);
  while ((_end = line.find(delimiter, _start))!= std::string::npos)
  {
    token = line.substr(_start, _end - _start);
      _start = _end + delimiter.size();
    if (!token.empty())
      tokens.push_back(token);
  }

  return (tokens);
}

std::pair<int, std::string>	getPortAndIpAddress_(std::string key)
{
	std::vector<std::string> tokens;

	tokens = get_tokens(key + ":", ":");
	if (tokens.size() == 1)
		return (std::make_pair(std::atoi(tokens[0].c_str()), "127.0.0.1"));
	else
		return (std::make_pair(std::atoi(tokens[1].c_str()), tokens[0]));
}

int main()
{	
	http														serv;
	mySocket													mysock(80, "127.0.0.1");
	std::vector<mySocket>										myServers;
	int															i = 0;
	fd_set														read_fds, write_fds;
	std::vector<client> 										clients;
	fd_set														m_read_fds, m_write_fds;
	int															max_fd = 0;
	std::map<int, int>											arr;
	int 														fd_a = 0;
	int 														j = 0;
	char 														buffer[1024] = {0};
	int 														flag = 0;
	std::map<int, std::vector<ft::server> >						mapy_;
	std::vector<std::pair<int, std::string> > 					obj;

	serv.parser("CURRENT/f.config");
	serv.check_servers_conflict();
	
	std::map<std::string, std::vector<ft::server> >				mapy(serv.get_ipPort_matched_servers());
	std::map<std::string, std::vector<ft::server> >::iterator	itrr(mapy.begin());
	
	for (std::map<std::string, std::vector<ft::server> >::iterator itr = mapy.begin(); itr != mapy.end(); itr++)
	{
		obj.push_back(getPortAndIpAddress_(itr->first));
	}

	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	for (std::vector<std::pair<int, std::string> >::iterator itr = obj.begin(); itr != obj.end(); itr++)
	{
		mysock.set_port_and_ip(itr->first, itr->second);
		myServers.push_back(mysock);
		myServers[i].createServer_socket();
		clients.push_back(myServers[i].get_server_fd());
		mapy_.insert(std::make_pair(myServers[i].get_server_fd(), itrr->second));
		fd_a = myServers[i].get_server_fd();
		FD_SET(fd_a, &read_fds);
		arr[fd_a] = 0;
		if (myServers[i].get_server_fd() > max_fd)
			max_fd = myServers[i].get_server_fd();
		i++;
		itrr++;
	}
	serv.setSocketServers(mapy_);
	while (true)
	{
		m_read_fds = read_fds;
		m_write_fds = write_fds;
		int	activity = select(max_fd + 1, &m_read_fds, &m_write_fds, NULL, NULL);
		if (activity < 0)
		{
			perror("select");
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < max_fd + 1; i++)
		{
			if (FD_ISSET(i, &m_read_fds))
			{
				if (arr[i] == 0)
				{
					int new_sock = (accept(i, NULL, NULL));
					if (new_sock < 0)
					{
						perror("accept");
						FD_CLR(new_sock, &read_fds);
						continue ;
						// exit(EXIT_FAILURE);
					}
					fcntl(new_sock, F_SETFL, O_NONBLOCK);
					arr[new_sock] = 1;
					FD_SET(new_sock, &read_fds);
					// FD_CLR(new_sock, &read_fds);
					max_fd = ((max_fd > new_sock) ? max_fd : new_sock);
				}
				else
				{
					int valread = read(i, buffer, 1024);
					if (valread < 0)
					{
						perror("read");
						FD_CLR(i, &read_fds);
						continue ;
						// exit(EXIT_FAILURE);//
					}
					for (std::vector<client>::size_type j = 0; j < clients.size(); j++)
					{
						if (clients[j].get_socket() == i)
							clients[j].get_client_request().parse2(buffer);
					}
					
					std::cout << buffer << std::endl;
					FD_SET(i, &write_fds);
					FD_CLR(i, &read_fds);
				}

			}
			else if (FD_ISSET(i, &m_write_fds))
			{
				const char *message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
				write(i, message, strlen(message));
				FD_CLR(i, &write_fds);
			}
		}
	}
	std::cout << "\n next client" << std::endl;
	return 0;
}
