/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:32:27 by het-tale          #+#    #+#             */
/*   Updated: 2023/02/28 11:02:15 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response()
{
	this->is_req_well_formed = true;
	this->char_not_allowed = false;
}

Response::Response(const Response& res)
{
	*this = res;
}

Response& Response::operator=(const Response& res)
{
	if (this != &res)
	{
		//copy some data
	}
	return (*this);
}

Response::~Response() {}

void Response::initRequest()
{
	this->request.insert(std::make_pair("method", "GET"));
	this->request.insert(std::make_pair("version", "HTTP/1.1"));
	this->request.insert(std::make_pair("body", "Hello Zen!"));
	this->request.insert(std::make_pair("content-type", "text/plain"));
	this->request.insert(std::make_pair("content-length", "10"));
	this->request.insert(std::make_pair("transfer-encoding", "chunked"));
	this->request.insert(std::make_pair("uri", "/"));
}

std::string Response::get_matched_location_for_request_uri()
{
	//Look for location in config file that matches the uri from the request
	//and return it
	return "";
}

std::string Response::check_which_method()
{
	return this->request["method"];
}

void Response::cgi_handler()
{
	if (!location_has_cgi())
	{
		this->status_code = 200;
		this->status_msg = "OK";
		//!To think about
		//return requested file (body)
	}
	else
	{
		//!To think about
		//run cgi on requested file with get method
		//code depend on cgi
	}
}

int Response::getStatusCode()
{
	if (!is_req_well_formed) //?Rania do this Baliz check if the request hwa hadak
	{
		if (this->request.find("transfer-encoding") != this->request.end()
			&& this->request["transfer-encoding"] != "chunked")
		{
			this->status_code = 501;
			this->status_msg = "Not Implemented";
		}
		else if (this->request.find("transfer-encoding") == this->request.end()
			&& this->request.find("content-length") == this->request.end()
			&& this->request["method"] == "POST")
		{
			this->status_code = 400;
			this->status_msg = "Bad Request";
		}
		else if (char_not_allowed)
		{
			this->status_code = 400;
			this->status_msg = "Bad Request";
		}
		else if (this->request["uri"].length() > 2048)
		{
			this->status_code = 414;
			this->status_msg = "Request-URI Too Long";
		}
		// else if (this->request["body"].length() > client_max_body)
		// {
		// 	this->status_code = 413;
		// 	this->status_msg = "Request Entity Too Large";
		// }
	}
	else
	{
		if (get_matched_location_for_request_uri().empty())
		{
			this->status_code = 404;
			this->status_msg = "Not Found";
		}
		else
		{
			if (is_location_have_redirection())
			{
				this->status_code = 301;
				this->status_msg = "Moved Permanently";
			}
			else
			{
				if (!is_method_allowed_in_location())
				{
					this->status_code = 405;
					this->status_msg = "Method Not Allowed";
				}
				else
				{
					if (check_which_method() == "GET")
					{
						if (get_requested_resource().empty())
						{
							this->status_code = 404;
							this->status_msg = "Not Found";
						}
						else
						{
							struct stat file_stat;
							if (stat(get_requested_resource().c_str(), &file_stat) == 0)
							{
        						if (S_ISDIR(file_stat.st_mode))
								{
        						    if (!is_uri_has_slash_in_end())
									{
										//!To think about
										this->status_code = 301;
										this->status_msg = "Moved Permanently";
									}
									else
									{
										if (!is_diretory_has_index_files())
										{
											if (get_auto_index() == "off")
											{
												this->status_code = 403;
												this->status_msg = "Forbidden";
											}
											else if (get_auto_index() == "on")
											{
												//!To think about
												this->status_code = 200;
												this->status_msg = "OK";
											}
										}
										else
											cgi_handler();
									}
        						}
								else if (S_ISREG(file_stat.st_mode))
									cgi_handler();
							}
						}
					}
					else if (check_which_method() == "POST")
					{
						
					}
					else if (check_which_method() == "DELETE")
					{
						
					}
				}
			}
		}
	}
}