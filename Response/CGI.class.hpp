/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:38:31 by het-tale          #+#    #+#             */
/*   Updated: 2023/04/01 02:57:59 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <sys/stat.h>
#include <dirent.h>
#include <sstream>
#include <string>
#include<cstring>
#include <unistd.h>
#include <libgen.h>
#include <ctime>
#include <stdlib.h>
#include <time.h> 
#include <fcntl.h>
#include <cstdlib>
 #include <sys/types.h>
#include <sys/wait.h>

#include "../Parsing/server.hpp"
#include "../Parsing/location.hpp"
#include "../Parsing/http.hpp"
#include "../Parsing/Request.hpp"
#include "Response.hpp"


#define BAD_GATE 52
// class Response;
class CGI
{
private:
	std::string	_path;
	std::string	_cgi_file;
	std::string	_headers;
	std::string	_cgiBody;
	bool	_isStatus;
	std::string	_file_content;
	int			_fileFD;
	char *argv[3];
	char **env;
	std::vector<std::string> _envp;
	std::map<int, std::string> _args;
	Request _request;
	ft::server _server;
	Response _response;
	ft::location	_location;
public:
	CGI();
	CGI(const CGI& cgi);
	CGI(Request request, ft::server server, Response &response);
	CGI& operator=(const CGI& cgi);
	~CGI();

	/**Public Methods**/
	void	init_args();
	void	init_envp();
	void	executeCgi();
	void	parseFile();
	void	ExtractResponseData();
	std::string	generatRandomFileName(std::string file);
	std::string	generate_file_name(std::string sara);
	
	/**Getters*/
	std::string getPath() const;
	/**Setters*/
	void	setPath(std::string path);
};
