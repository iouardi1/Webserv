/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:45:23 by het-tale          #+#    #+#             */
/*   Updated: 2023/04/02 03:11:52 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.class.hpp"
#include "Response.hpp"

CGI::CGI(): _path() {}
CGI::CGI(const CGI& cgi)
{
	*this = cgi;
}

CGI::CGI(Request request, ft::server server, Response &response)
{
	this->_request = request;
	this->_server = server;
	this->_response = response;
	this->_location = _request.getLoc();
	_isStatus = false;
	this->_path = _location.get_cgi();
	init_args();
	init_envp();
	const char* path = "./var";
   	mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	executeCgi();
	if (_response.getCode() == 200)
	{
		ExtractResponseData();
		this->_response.setStatusLine();
		this->_response.appendHeaders("\r\n");
		this->_response.appendHeaders(_headers);
		this->_response.appendHeaders("Server: ");
		this->_response.appendHeaders(this->_response.getServ());
		this->_response.appendHeaders("\r\n");
		time_t now = time(0);
		struct tm* timeinfo = gmtime(&now);
		char buffer[80];
		strftime(buffer, 80, "Date: %a, %d %b %Y %H:%M:%S GMT", timeinfo);
		this->_response.appendHeaders(buffer);
		this->_response.appendHeaders("\r\n");
		this->_response.appendHeaders("\r\n");
	}
	else
	{
		this->_response.setStatusLine();
		this->_response.ResponseError(this->_response.getCode());
		struct stat fileInfo;
		std::stringstream ss;
		if (stat(this->_response.getHttpResponsePath().c_str(), &fileInfo) == 0)
		{
			ss << fileInfo.st_size;
		}
		this->_response.appendHeaders("\r\n");
		_headers = "Content-type: text/html; charset=UTF-8\r\nContent-Length: ";
		_headers.append(ss.str()).append("\r\n");
		this->_response.appendHeaders(_headers);
		this->_response.appendHeaders("Server: ");
		this->_response.appendHeaders(this->_response.getServ());
		this->_response.appendHeaders("\r\n");
		time_t now = time(0);
		struct tm* timeinfo = gmtime(&now);
		char buffer[80];
		strftime(buffer, 80, "Date: %a, %d %b %Y %H:%M:%S GMT", timeinfo);
		this->_response.appendHeaders(buffer);
		this->_response.appendHeaders("\r\n");
		this->_response.appendHeaders("\r\n");
	}
	response = this->_response;
	remove(_cgi_file.c_str());
}


CGI& CGI::operator=(const CGI& cgi)
{
	if (this != &cgi)
	{
		_path = cgi._path;
	}
	return *this;
}
CGI::~CGI() 
{
	if (this->env)
		delete this->env;
}

//*Getters

std::string CGI::getPath() const
{
	return _path;
}

//*Setters

void CGI::setPath(std::string path)
{
	_path = path;
}

void	CGI::init_args()
{
	this->_args.insert(std::make_pair(0, this->_path));
	this->_args.insert(std::make_pair(1, _response.getIndexFile()));
	this->_args.insert(std::make_pair(2, "NULL"));
	argv[0] = (char *)this->_args[0].c_str();
	argv[1] = (char *)this->_args[1].c_str();
	argv[2] = NULL;
}

void	CGI::init_envp()
{
	if (!_request.getHeaderFields()["Content-Length:"].empty() && _request.getMethod() != "GET")
    {
        this->_envp.push_back("CONTENT_TYPE=" + _request.getHeaderFields()["Content-Type:"][0]);
        this->_envp.push_back("CONTENT_LENGTH=" + _request.getHeaderFields()["Content-Length:"][0]);
    }
	this->_envp.push_back("GATEWAY_INTERFACE=CGI/1.1");
	this->_envp.push_back("QUERY_STRING=" + _request.extractQuerieString());
	this->_envp.push_back("PATH_INFO=" + _request.getTarget());
	this->_envp.push_back("REMOTE_ADDR=" + _server.getPortAndIpAddress().first);
	if (_request.getHeaderFields().find("Host:") != _request.getHeaderFields().end())
		this->_envp.push_back("SERVER_NAME=" + _request.getHeaderFields()["Host:"].at(0));
	else
		this->_envp.push_back("SERVER_NAME=" + _server.getPortAndIpAddress().first);
	this->_envp.push_back("SERVER_PORT=" + _server.getPortAndIpAddress().second);
	this->_envp.push_back("REQUEST_METHOD=" + _request.getMethod());
	this->_envp.push_back("SCRIPT_NAME=" + _path);
	this->_envp.push_back("SCRIPT_FILENAME=" + _response.getIndexFile());
	this->_envp.push_back("SERVER_SOFTWARE=webserv/1.1");
	this->_envp.push_back("SERVER_PROTOCOL=" + _request.getHttpVersion());
	this->_envp.push_back("REDIRECT_STATUS=true");

	std::map<std::string, std::vector<std::string> > req_headers = _request.getHeaderFields();
	std::map<std::string, std::vector<std::string> >::iterator it = req_headers.find("Cookie:");
	//this->_envp.push_back("HTTP_COOKIE=user=hasnaa;name=hett");
	std::string cookie = "HTTP_COOKIE=";
	if (it != req_headers.end())
	{
		for (size_t i = 0; i < it->second.size(); i++)
		{
			cookie.append(it->second.at(i));
		}
	}
	this->_envp.push_back(cookie);

	this->env = new char*[_envp.size() + 1];
	size_t i = -1;
	while (++i < _envp.size())
		env[i] = strdup(_envp[i].c_str());
	env[i] = NULL;
}

void	CGI::executeCgi()
{
	_cgi_file = generate_file_name("./var/cgi_");
	//std::cout<< "THE CGI FILE: " << _cgi_file << std::endl;
	pid_t pid;
	int	req_bodyFD = 0;
	pid = fork();
	if (pid < 0)
	{
		//std::cout<< "FOOOORK\n";
		_response.ResponseError(502);
		return;
	}
	//std::cout << "CGI FILE: " << _cgi_file << std::endl;
	_fileFD = open(_cgi_file.c_str(), O_CREAT | O_RDWR, 0777);
	req_bodyFD = open(_request.get_bodyFile().c_str(), O_RDONLY, 0444);
	if (pid == 0)
	{
		if ((_fileFD < 0))
		{
			exit(BAD_GATE);
		}
		if (_request.getMethod() == "POST" && (req_bodyFD < 0))
			exit(BAD_GATE);
		// std::cout<< "THE FD: " << _fileFD << std::endl;
		if (_request.getMethod() == "POST" && dup2(req_bodyFD, 0) < 0)
			exit(BAD_GATE);
		if (dup2(_fileFD, 1) < 0)
		{
			exit(BAD_GATE);
		}
		if (dup2(_fileFD, 2) < 0)
		{
			exit(BAD_GATE);
		}
		if (execve(_path.c_str(), argv, env) < 0)
		{
			//std::cout<< _path << std::endl;
			for (size_t i = 0; i < _envp.size() ; i++)
			//std::cout<< env[i] << std::endl;
			exit(BAD_GATE);
			
		}
		exit(0);
	}
	else
	{
		int status;
        if (waitpid(pid, &status, 0) == -1)
		{
			_response.ResponseError(500);
			return;
		}
        if (WIFEXITED(status) && (WEXITSTATUS(status)) == BAD_GATE)
		{
			_response.ResponseError(502);
			return;
        }
		close(_fileFD);
		close(req_bodyFD);
	}
	_response.setCodeMsg(200, "OK");
}

void	CGI::ExtractResponseData()
{
	std::ifstream inFile(_cgi_file.c_str());
	std::string path = generate_file_name("./var/body_");
	std::ofstream outFile(path.c_str());
	std::string line;
	bool	start_body = false;
	int	code;
	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			if (line == "\r")
			{
				start_body = true;
				continue;
			}
			if (start_body == true)
			{
				_cgiBody += line + "\n";
			}
			else
				_headers += line + "\n";
		}
		if (start_body == false)
		{
			_cgiBody = _headers;
			outFile << _cgiBody;
			_response.setHttpResponsePath(path);
			_headers = "Content-type: text/html; charset=UTF-8\r\nContent-Length: ";
			std::stringstream ss;
    		ss << _cgiBody.length();
			_headers.append(ss.str()).append("\r\n");
			outFile.close();
			inFile.close();
			return ;
		}
		size_t s = _headers.find("Status: ", 0);
		if (s != std::string::npos)
		{
			_isStatus = true;
			std::stringstream ss(_headers.substr(8, 3));
			ss >> code;
			_response.setCodeMsg(code, _response.get_http_codes()[code]);
			_headers = _headers.substr(14 + _response.getMessage().length());
			_response.ResponseError(_response.getCode());
		}
		else
		{
			outFile << _cgiBody;
			_response.setHttpResponsePath(path);
		}
	}
	outFile.close();
	inFile.close();
	// remove(_cgi_file.c_str());
}


std::string		CGI::generate_file_name(std::string sara)
{
	std::stringstream	strStream;
	std::string			str;
	
	srand((int) time(0));
	int r = rand() % 7000;
	strStream << r;
	strStream >> str;
	str = sara + str;
	return (str);
}
