/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 07:06:37 by het-tale          #+#    #+#             */
/*   Updated: 2023/03/05 07:12:15 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP
#include <iostream>
#include <fstream>
#include <map>
#include <sys/stat.h>

/**
 * !The client always initiates The communicati00on with the server;
 * !The client send a request and expects response from the server;
 * !HTTP methods are meant to detect actions performed on the server;
 * *POST: CREATE resources in the server;
 * *GET: READ data from the server;
 * *PUT: UPDATE existing resources on the server;
 * *DELETE: DELETE resources on the server;
 * 
 * !check file existence return status code
 * !if the file exists then select content-type
 * !read data from file count how many bytes (content-size)
 * !append read data to the string
 * !My job here is to build a response; create the header and body
 * 
 * *A typical response Header Looks like:
 * ?HTTP_version code status_msg
 * ?content-type: value
 * ?content-length: value
 * ?
 * ?Data
 */

//*Status Codes

#define	NOT_IMPLEMENTED "501 Not Implemented"
#define BAD_REQUEST	"400 Bad Request"
#define LONG_REQUEST "414 Request-URI Too Long"
#define OK "200 OK"

//*
#define NPOS std::string::npos
#define ON	"on"
#define OFF "off"

class HttpResponse
{
	private:
		std::map<std::string, std::string> _request;
		int			_code;
		int			_fileFd;
		std::string _msg;
		std::string	_buffer;
		std::string	_contentType;
		std::string _autoIndex;
		std::string	_allow;
		bool		_isAutoIndexed;
		bool		_isDir;
		size_t		_contentLength;
		//*METHODS
		void		initRequest();
		bool		isUriAllowed();
		bool		is_file_or_directory(std::string fileName);
		bool		get_matched_location_for_request_uri();
		bool		is_method_allowed();
		bool		is_loc_has_redir();
		bool		is_uri_has_slash();
		std::string check_requested_method();
		
	public:
		HttpResponse();
		HttpResponse(const HttpResponse& res);
		HttpResponse& operator=(const HttpResponse& res);
		~HttpResponse();
		void	setHttpVersion();
		void	buildResponseHeader();
		bool	NotFound();
		void	setCodeMsg(int code, std::string msg);
		void	GetMethod();
		void	PostMethod();
		void	DeleteMethod();
};

#endif