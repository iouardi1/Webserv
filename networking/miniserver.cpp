/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniserver.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:28 by iouardi           #+#    #+#             */
/*   Updated: 2023/04/02 03:02:23 by iouardi          ###   ########.fr       */
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
#include <signal.h>
#include <fstream>
#include "mySocket.hpp"
#include "client.hpp"
#include "../Response/Response.hpp"



//*curl localhost:8087 to send request from terminal
//* curl localhost:8086/Dir -X POST -H "Content-Length: 8"  -H "Content-Type: plain/text" --data "123456789"  */

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
long long ress;
std::pair<int, std::string>	getPortAndIpAddress_(std::string key)
{
	std::vector<std::string> tokens;

	tokens = get_tokens(key + ":", ":");
	if (tokens.size() == 1)
		return (std::make_pair(std::atoi(tokens[0].c_str()), "127.0.0.1"));
	else
		return (std::make_pair(std::atoi(tokens[1].c_str()), tokens[0]));
}

int main(int argc, char *argv[])
{	
	ress = 0;
	http														serv;
	mySocket													mysock(80, "127.0.0.1");
	std::vector<mySocket>										myServers;
	int															i = 0;
	fd_set														read_fds, write_fds;
	fd_set														m_read_fds, m_write_fds;
	int															max_fd = 0;
	std::map<int, int>											arr;
	int 														fd_a = 0;
	char 														buffer[100000] = {0};
	int 														flag = 0;
	std::map<int, std::vector<ft::server> >						mapy_;
	std::vector<std::pair<int, std::string> > 					obj;

	std::string													file_to_parse;
	
	if (argc > 2)
	{
	
		std::cerr << "WRONG number of arguments\n";
		exit(EXIT_FAILURE); 
	}
	else if (argc <= 2)
	{
		if (argc == 1)
			file_to_parse = "./ConfigFiles/return.config";
		else
			file_to_parse = std::string(argv[1]);
	}
	try
	{
	serv.parser(file_to_parse);
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
		
		struct  timeval	tv = {5, 500};
		std::map<int, size_t>		itr_map;
		
		while (true)
		{
			signal(SIGPIPE, SIG_IGN);
			m_read_fds = read_fds;
			m_write_fds = write_fds;
			int	activity = select(max_fd + 1, &m_read_fds, &m_write_fds, NULL, &tv);
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
								continue ;
							}
							std::vector<client>::size_type k;
							std::vector<std::pair<int, Request> >::size_type	l = 0;
							flag = 0;
							for (k = 0; k < clients.size(); k++)
							{
								itr_map = clients[k].get_itr_map();
								std::map<int, size_t>::iterator itr;
								if((itr = itr_map.find(i)) != (itr_map.end()))
								{
									l = itr->second;
									if (clients[k].get_socket_responses()[l].first.first == i)
									{
										bool ret = clients[k].parse_request(std::string(buffer, valread), mapy_, l);
										clients[k].set_sock_flag(ret, l);
										if (clients[k].get_sock_flag(l))
										{
											memset(buffer, 0, sizeof(buffer));
											FD_SET(i, &write_fds);
											FD_CLR(i, &read_fds);
										}
										break ;
									}
								}
							}

						}
					}
					else if (FD_ISSET(i, &m_write_fds))
					{
						std::string message;
						std::string path;
						int bytes_sent;
					
						flag = 0;
						int flag1 = 0;
						for (std::vector<client>::size_type j = 0; j < clients.size(); j++)
						{
							std::vector<std::pair<int, Request> >::size_type	l = 0;
							for (l = 0; l < clients[j].get_socket_responses().size(); l++)
							{
								if (clients[j].get_socket_responses()[l].first.first == i && clients[j].get_socket_responses()[l].first.second == true)
								{
									if (clients[j].get_socket_responses()[l].second.getErrorCode() != 0)
									{
										Response resp;
										resp.setCode(clients[j].get_socket_responses()[l].second.getErrorCode());
										resp.setMessage(resp.get_http_codes()[resp.getCode()]);
										std::string path = resp.generateErrorPages(resp.getCode(), "Rania");
										resp.setContentType("text/html");
										resp.setHttpResponsePath(path);
										resp.buildHttpResponse();
										send(i, resp.getHeaders().c_str(), resp.getHeaders().size(), 0);
										std::ifstream in;
										in.open(path.c_str());
										char b[100000] = {0};
										if (in.is_open())
										{
											in.read(b, 100000);
											send(i,b, sizeof(b), 0);
										}
									}
									else
									{
										Response resp(clients[j].get_socket_responses()[l].second, clients[j].get_socket_responses()[l].second.getServer());
										std::string path = resp.getHttpResponsePath();
										std::string headers = resp.getHeaders();
										send(i, headers.c_str(), headers.size(), 0);
										std::ifstream in;
										in.open(path.c_str());
										std::vector<char> b(1024);
										if (in.is_open())
										{
											while (!in.eof())
											{
												in.read(&b[0], 1024);
												bytes_sent = send(i, std::string(b.begin(), b.begin() + in.gcount()).c_str(), in.gcount(), 0);
												if ( bytes_sent < 0)
												{
													FD_CLR(i, &write_fds);
													in.close();
													close(i);
													clients[j].remove_sock(l, i);
													flag1 = 1;
													break ;
												}
											}
											in.close();
											flag = 1;
											if (flag1)
												break ;
											}
										}
										FD_CLR(i, &write_fds);
										close(i);
										clients[j].remove_sock(l, i);
										if (flag)
											break ;
								}
							}
						}
					}
				}
			}

		}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}