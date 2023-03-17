/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserver.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:28 by iouardi           #+#    #+#             */
/*   Updated: 2023/03/17 17:34:13 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>
#include <strings.h>
// #include <sys/_types/_fd_def.h>
// #include <sys/_types/_socklen_t.h> //edited this
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <vector>
#include <arpa/inet.h>
#include <map>
#include "mySocket.hpp"
#include "client.hpp"
#include "../Response/Response.class.hpp"


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
	fd_set														m_read_fds, m_write_fds;
	int															max_fd = 0;
	std::map<int, int>											arr;
	int 														fd_a = 0;
	// int 														j = 0;
	char 														buffer[1024] = {0};
	// int 														flag = 0;
	std::map<int, std::vector<ft::server> >						mapy_;
	std::vector<std::pair<int, std::string> > 					obj;

	serv.parser("Parsing/f.config");
	serv.check_servers_conflict();
	
	std::map<std::string, std::vector<ft::server> >				mapy(serv.get_ipPort_matched_servers());
	std::map<std::string, std::vector<ft::server> >::iterator	itrr(mapy.begin());
	
	for (std::map<std::string, std::vector<ft::server> >::iterator itr = mapy.begin(); itr != mapy.end(); itr++)
	{
		obj.push_back(getPortAndIpAddress_(itr->first));
	}
	std::vector<client> 										clients;

	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	for (std::vector<std::pair<int, std::string> >::iterator itr = obj.begin(); itr != obj.end(); itr++)
	{
		mysock.set_port_and_ip(itr->first, itr->second);
		myServers.push_back(mysock);
		myServers[i].createServer_socket();
		clients.push_back(myServers[i].get_server_fd());
		clients[i].set_socket_server(myServers[i].get_server_fd());
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
	
	int			j;
	struct  timeval	tv = {0, 500};
	while (true)
	{
		m_read_fds = read_fds;
		m_write_fds = write_fds;
		try
		{
			int	activity = select(max_fd + 1, &m_read_fds, &m_write_fds, NULL, &tv);
			if (activity < 0)
			{
				perror("select");
				exit(EXIT_FAILURE);
			}
			bool s = false;
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
							for (std::vector<client>::size_type l = 0; l < clients.size(); l++)
							{
								if (clients[l].get_socket_server() == i)
								{
									clients[l].set_socket_responses(new_sock, false, Request());
									FD_SET(new_sock, &read_fds);
									max_fd = ((max_fd > new_sock) ? max_fd : new_sock);
									break ;
								}
							}
						}
						else
						{
							memset(buffer, 0, sizeof(buffer));
							int valread = recv(i, buffer, sizeof(buffer), 0);
							if (valread < 0)
							{
								perror("read");
								FD_CLR(i, &read_fds);
								
								close(i);
								// clients[l].get_socket_responses()
								continue ;
								// exit(EXIT_FAILURE);//
							}
							std::vector<client>::size_type k;
							std::vector<std::pair<int, Request> >::size_type	l = 0;
							int	flag = 0;
							for (k = 0; k < clients.size(); k++)
							{
								for (l = 0; l < clients[k].get_socket_responses().size(); l++)
								{	
									// std::cout << &s << std::endl;
									if (clients[k].get_socket_responses()[l].first.first == i)
									{
										clients[k].set_sock_flag(clients[k].parse_request(buffer, mapy_, l), l);
										// clients[k].get_socket_responses()[l].second.parse(clients[k].get_socket_server(),buffer, mapy_);
										// std::cout << "/n/nthe bool is : " << s << std::endl;
										if (clients[k].get_sock_flag(l))
										{
											std::cout << "WEEESH DKHLTI?  " << std::endl;
											std::cout << buffer << std::endl;
											FD_SET(i, &write_fds);
											FD_CLR(i, &read_fds);
										}
										flag = 1;
										break ;
									}
								}
								if (flag)
									break ;
							}
							// int	flag = 0;
							// for (k = 0; k < clients.size(); k++)
							// {
							// 	std::vector<std::pair<std::pair<int, bool>, Request> >::iterator it = find(clients[k].get_socket_responses().begin(), clients[k].get_socket_responses().end(), i);

							// 	if (it != clients[k].get_socket_responses().end())
							// 	{
							// 		s = clients[k].parse_request(buffer, mapy_, l);
							// 		std::cout << "\n\nthe bool is : " << s << std::endl;
							// 		if (s)
							// 		{
							// 			std::cout << "WEEESH DKHLTI?  " << std::endl;
							// 			std::cout << buffer << std::endl;
							// 			FD_SET(i, &write_fds);
							// 			FD_CLR(i, &read_fds);
							// 		}
							// 	}
							// 	else
							// 		continue ;
							// }
						}
					}
					else if (FD_ISSET(i, &m_write_fds))
					{
						std::string message;
						int			flag = 0;
						for (std::vector<client>::size_type j = 0; j < clients.size(); j++)
						{
							std::vector<std::pair<int, Request> >::size_type	l = 0;
							for (l = 0; l < clients[j].get_socket_responses().size(); l++)
							{
								if (clients[j].get_socket_responses()[l].first.first == i && clients[j].get_socket_responses()[l].first.second == true)
								{
									Response resp(clients[j].get_socket_responses()[l].second, clients[j].get_socket_responses()[l].second.getServer());
									message = resp.getResponseBuffer();
									// std::string message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
									std::cout << "The reponse message is: " << message << std::endl;
									
									// write(2, "RES: ***************************************************", strlen("RES: ***************************************************"));
									// write(2, message.c_str(), strlen(message.c_str()));
									// write(2, "********************************************************", strlen("********************************************************"));
									
									send(i, message.c_str(), message.length(), 0);
									FD_CLR(i, &write_fds);
									// close(i);
									clients[j].set_sock_flag(false, l);
									flag = 1;
									break ;
								}
								if (flag)
									break ;
							}
							}
					}
				}
		}
		catch(int &e)
		{
			Response resp;
			resp.setCode(e);
			resp.setMessage(resp.get_http_codes()[resp.getCode()]);
			resp.setBody(resp.generateErrorPages(resp.getCode()));
			resp.buildHttpResponse();
			std::string message = resp.getResponseBuffer();
			std::cout << "The reponse message is: " << message << std::endl;
			write(i, message.c_str(), strlen(message.c_str()));		
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return 0;
}
