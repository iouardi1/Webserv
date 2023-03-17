/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:33:59 by het-tale          #+#    #+#             */
/*   Updated: 2023/02/28 11:00:17 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef RESPONSE_HPP
#define RESPONSE_HPP
#include <iostream>
#include <fstream>
#include <map>
#include <sys/stat.h>

/**
 * !The client always initiates The communication with the server;
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
 */


class Response
{
	private:
		int 		status_code;
		std::string content_type;
		int			content_size;
		std::string file_path;
		std::string status_msg;
		std::map<std::string, std::string> request;
		bool is_req_well_formed;
		bool char_not_allowed;
	public:
		Response();
		Response(const Response& res);
		Response& operator=(const Response& res);
		~Response();
		int	getStatusCode();
		std::string getContentType();
		int getContentSize();
		void initRequest();
		std::string get_matched_location_for_request_uri();
		bool is_location_have_redirection();
		bool is_method_allowed_in_location();
		std::string check_which_method();
		std::string get_requested_resource();
		void cgi_handler();
		bool location_has_cgi();
		bool is_uri_has_slash_in_end();
		bool is_diretory_has_index_files();
		std::string get_auto_index();
};

#endif