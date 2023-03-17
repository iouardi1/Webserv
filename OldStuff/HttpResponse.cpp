/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 07:07:44 by het-tale          #+#    #+#             */
/*   Updated: 2023/03/05 07:15:11 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

HttpResponse::HttpResponse()
{
	this->initRequest();
	this->_code = 0;
	this->_fileFd = -1;
	this->_buffer = "";
	this->_contentType = "";
	this->_contentLength = 0;
	this->_isDir = this->is_file_or_directory(this->_request["resource"]);
}

HttpResponse::HttpResponse(const HttpResponse& res)
{
	*this = res;
}

HttpResponse& HttpResponse::operator=(const HttpResponse& res)
{
	if (this != &res)
	{
		//copy some data
	}
	return (*this);
}

HttpResponse::~HttpResponse() {}

void	HttpResponse::setHttpVersion()
{
	this->_buffer = "HTTP/1.1 ";
}



void	HttpResponse::setCodeMsg(int code, std::string msg)
{
	this->_code = code;
	this->_msg = msg;
}

bool	HttpResponse::NotFound()
{
	
}

// void	HttpResponse::cgi_handler(std::string method)
// {
// 	if (is_cgi())
// 	{
// 		//run CGI with method
// 		//return code depend on CGI
// 	}
// 	else
// 	{
// 		_code = 200;
// 		_msg = "OK";
// 	}
// }

// void	HttpResponse::GetMethod()
// {
// 	if (requested resource exist)
// 	{
// 		if (_isDir)
// 		{
// 			if (!is_uri_has_slash())
// 			{
// 				_code = 301;
// 				_msg = "Moved Permanantly";
// 			}
// 			else
// 			{
// 				if (!is_dir_has_index_file())
// 				{
// 					if (_autoIndex == OFF)
// 					{
// 						_code = 403;
// 						_msg = "Forbidden";
// 					}
// 					else
// 					{
// 						_code = 200;
// 						_msg = "OK";
// 						//return autoindex
// 					}
// 				}
// 				else
// 				{
// 					cgi_handler("GET");
// 				}
// 			}
// 		}
// 		else
// 			cgi_handler();
// 	}
// 	else
// 	{
// 		_code = 403;
// 		_msg = "Forbidden";
// 	}
// }

void	HttpResponse::buildResponseHeader()
{
	setHttpVersion();
	//call all The function that set status code and status msg
	//setContentType();
	//setContentLength();
	//buildResponseBody();
	
}

/**-------------------------------*!Private Methods-----------------0*/
void HttpResponse::initRequest()
{
	this->_request.insert(std::make_pair("method", "GET"));
	this->_request.insert(std::make_pair("version", "HTTP/1.1"));
	this->_request.insert(std::make_pair("body", "Hello Zen!"));
	this->_request.insert(std::make_pair("content-type", "text/plain"));
	this->_request.insert(std::make_pair("content-length", "10"));
	this->_request.insert(std::make_pair("transfer-encoding", "chunked"));
	this->_request.insert(std::make_pair("uri", "/index.html"));
	this->_request.insert(std::make_pair("resource", "index.html"));
}

bool		HttpResponse::isUriAllowed()
{
	std::string		uri = this->_request["uri"];
	const std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
  	for (std::string::const_iterator it = uri.begin(); it != uri.end(); ++it)
  	{
  	  if (allowedChars.find(*it) == NPOS)
  	    return false;
  	}
  	return true;
}

bool	HttpResponse::is_file_or_directory(std::string fileName)
{
	struct stat fileInfo;
	if (stat(fileName.c_str(), &fileInfo) == 0)
	{
		if (S_ISDIR(fileInfo.st_mode))
			return true;
	}
	return false;
}

bool HttpResponse::get_matched_location_for_request_uri()
{
	//check if this->_request["uri"] match any location in server
	return true;
}

bool		HttpResponse::is_loc_has_redir()
{
	//check if location has redirection
}

bool		HttpResponse::is_method_allowed()
{
	//check if this->_request["method"] supported by specific location
}

std::string HttpResponse::check_requested_method()
{
	return this->_request["method"];
}

bool		HttpResponse::is_uri_has_slash()
{
	std::string uri = this->_request["uri"];
	std::string::reverse_iterator it = uri.rbegin();
	if (*it == '/')
		return true;
	return false;
}