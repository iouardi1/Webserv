/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:15:56 by het-tale          #+#    #+#             */
/*   Updated: 2023/03/19 00:11:46 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef RESPONSE_HPP
#define RESPONSE_HPP
#include <iostream>
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

#include "../Parsing/server.hpp"
#include "../Parsing/location.hpp"
#include "../Parsing/http.hpp"
#include "../Parsing/Request.hpp"

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


#define	NOT_IMPLEMENTED "501 Not Implemented"
#define BAD_REQUEST	"400 Bad Request"
#define LONG_REQUEST "414 Request-URI Too Long"
#define OK "200 OK"
#define NOT_FOUND "404 Not Found"
#define FORBIDDEN "403 Forbidden"

class Response
{
	private:
		Request		_request;
		ft::server		_server;
		ft::location	_location;
		int			_code;
		int			_fileFd;
		std::string _msg;
		std::string	_ResponseBuffer; //The reponse string
		std::string	_contentType;
		std::string _autoIndex;
		std::string	_allow;
		std::string	_loc;
		std::string	_body;
		std::string	_index_file;
		std::string	_serv;
		std::string _date;
		std::string	_root;
		bool		_isAutoIndexed;
		bool		_isDir;
		size_t		_contentLength;
		std::map<int, std::string> http_codes;
		std::map<std::string, std::string> mimeTypes;
		//*METHODS
		
	public:
		Response();
		Response(const Response& res);
		Response(Request req, ft::server server);
		Response& operator=(const Response& res);
		~Response();
		void		setHttpVersion();
		void		buildHttpResponse();
		void		setStatusLine();
		void		setHeaders();
		void		setMessageBody();
		bool		NotFound();
		void		setCodeMsg(int code, std::string msg);
		void		GetMethod();
		void		PostMethod();
		void		DeleteMethod();
		bool		ErrorGenerator();
		void		HandleMultipleCases();
		bool		get_matched_location_for_request_uri();
		bool		is_loc_has_redir();
		std::string getRequestedResource();
		bool		is_dir_has_index();
		void		file_handler(std::string file, std::string method);
		void		cgi_handler(std::string method);
		std::string	generateErrorPages(int code, std::string name);
		void		Get_Post(std::string method);
		
		void		initRequest();
		bool		isUriAllowed();
		bool		is_directory(std::string fileName);
		bool		is_method_allowed();
		bool		is_uri_has_slash(std::string uri);
		bool		isResourceExist();
		std::string	readFileContent(std::string file);
		std::string	listDirContent();
		void		init_http_codes();
		void		init_mime_types();
		bool		loc_support_upload();
		std::string	getFileExtension(std::string file);
		std::string	generatRandomFileName(std::string file);
		int			getPositionOfLastDot(std::string file);
		std::string getResponseBuffer() const;

		ft::location match_location();
		void deleteFolderContent(const char *path);
		bool	is_loc_has_cgi();

		//Getters
		int									getCode() const;
		std::string							getMessage() const;
		std::string							getBody() const;
		Request								getRequest() const;
		std::map<int, std::string>			get_http_codes() const;
		std::map<std::string, std::string>	get_mimeTypes() const;

		//Setters
		void	setCode(int code);
		void	setMessage(std::string message);
		void	setBody(std::string body);
		// void	set_http_codes() const;
		// void	set_mimeTypes() const;
};

#endif


