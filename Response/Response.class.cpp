/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:18:48 by het-tale          #+#    #+#             */
/*   Updated: 2023/03/16 18:31:09 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.class.hpp"

/**------------------------------------------------COPLIEN FORM-----------------------------------------*/

Response::Response()
{
	this->_ResponseBuffer = "";
	this->_contentType = "";
	this->_contentLength = 0;
	this->_allow = "";
	this->_loc = "";
	this->_code = 0;
	this->_msg = "";
	this->_serv = "webserv/1.1";
	init_http_codes();
	init_mime_types();
}

Response::Response(Request req, ft::server server)
{
	this->_server = server;
	this->_request = req;
	this->_ResponseBuffer = "";
	this->_contentType = "";
	this->_contentLength = 0;
	this->_allow = "";
	this->_loc = "";
	this->_code = 0;
	this->_msg = "";
	this->_serv = "webserv/1.1";
	this->_location = _request.getLoc();
	init_http_codes();
	init_mime_types();
	HandleMultipleCases();
	buildHttpResponse();
}

Response::Response(const Response& res)
{
	*this = res;
}

Response& Response::operator=(const Response& res)
{
	if (this != &res)
	{
		this->_server = res._server;
		this->_request = res._request;
		this->_ResponseBuffer = res._ResponseBuffer;
		this->_contentType = res._contentType;
		this->_contentLength = res._contentLength;
		this->_allow = res._allow;
		this->_loc = res._loc;
	}
	return (*this);
}

Response::~Response() {}


/**------------------------------------------------Getters-----------------------------------------*/
int	Response::getCode() const
{
	return _code;
}

std::string	Response::getMessage() const
{
	return _msg;
}
Request	Response::getRequest() const
{
	return _request;
}

std::map<int, std::string>			Response::get_http_codes() const
{
	return http_codes;
}
std::map<std::string, std::string>	Response::get_mimeTypes() const
{
	return mimeTypes;
}

std::string	Response::getBody() const
{
	return _body;
}
/**------------------------------------------------Setters-----------------------------------------*/
void	Response::setCode(int code)
{
	_code = code;
}

void	Response::setMessage(std::string message)
{
	_msg = message;
}

void	Response::setBody(std::string body)
{
	_body = body;
}
/**------------------------------------------------Public Methods-----------------------------------------*/

void		Response::buildHttpResponse()
{
	setStatusLine();
	_ResponseBuffer.append("\r\n");
	setHeaders();
	_ResponseBuffer.append("\r\n");
	setMessageBody();
}

void		Response::setStatusLine()
{
	std::stringstream ss;
	ss << _code;
	_ResponseBuffer.append("HTTP/1.1 ");
	_ResponseBuffer.append(ss.str());
	_ResponseBuffer.append(" ");
	_ResponseBuffer.append(_msg);
}

void		Response::setHeaders()
{
	std::stringstream ss;
	_contentLength = _body.length();
	ss << _contentLength;
	if (_contentType != "")
	{
		_ResponseBuffer.append("Content-Type: ");
		_ResponseBuffer.append(_contentType);
		_ResponseBuffer.append("\r\n");
	}
	_ResponseBuffer.append("Content-length: ");
	_ResponseBuffer.append(ss.str());
	_ResponseBuffer.append("\r\n");
	if(_allow != "")
	{
		_ResponseBuffer.append("Allow: ");
		_ResponseBuffer.append(_allow);
		_ResponseBuffer.append("\r\n");
	}
	if(_loc != "")
	{
		_ResponseBuffer.append("Location: ");
		_ResponseBuffer.append(_loc);
		_ResponseBuffer.append("\r\n");
	}
	_ResponseBuffer.append("Server: ");
	_ResponseBuffer.append(_serv);
	_ResponseBuffer.append("\r\n");
	time_t now = time(0);
    struct tm* timeinfo = gmtime(&now);
    char buffer[80];

    strftime(buffer, 80, "Date: %a, %d %b %Y %H:%M:%S GMT", timeinfo);
	_ResponseBuffer.append(buffer);
	_ResponseBuffer.append("\r\n");
}

void		Response::setMessageBody()
{
	_ResponseBuffer.append(_body);
}

void	Response::setCodeMsg(int code, std::string msg)
{
	this->_code = code;
	this->_msg = msg;
}

void	Response::HandleMultipleCases()
{
	if (is_loc_has_redir())
	{
		setCodeMsg(301, "Moved Permanently");
		std::string tmp = "http://localhost:";
		tmp.append(_server.get_listen_directive());
		this->_loc = tmp.append("/");
		this->_loc = tmp.append(_location.get_return().at(1));
		return ;
	}
	else
	{
		if (!is_method_allowed())
		{
			setCodeMsg(405, "Method Not Allowed");
			std::vector<std::string> allowed = _location.get_limitexcept();
			std::vector<std::string>::size_type	i = 0;
			for (std::vector<std::string>::iterator it = allowed.begin(); it != allowed.end(); it++)
			{
				_allow.append(*it);
				if (i != allowed.size() - 1)
					_allow.append(", ");
				i++;
			}
			_body = generateErrorPages(_code);
			return ;
		}
		else
		{
			if (_request.getMethod() == "GET")
			{
				GetMethod();
				return ;
			}
			// else if (_request.getMethod() == "POST")
			// {
			// 	PostMethod();
			// 	return ;
			// }
			else if (_request.getMethod() == "DELETE")
			{
				DeleteMethod();
				return ;
			}
		}
	}
}

void	Response::GetMethod()
{
	Get_Post("GET");
}

void	Response::Get_Post(std::string method)
{
	if (!isResourceExist())
	{
		setCodeMsg(404, "Not Found");
		_body = generateErrorPages(_code);
		return ;
	}
	else
	{
		if (is_directory(getRequestedResource()))
		{
			if (!is_uri_has_slash(getRequestedResource()))
			{
					setCodeMsg(301, "Moved Permanently");
					std::string tmp = "http://localhost:";
					tmp.append(_server.get_listen_directive());
					this->_loc = tmp.append(this->_request.getTarget().append("/"));
					std::cout << "tmp: " << tmp << std::endl;
					return ;
			}
			else
			{
				if (!is_dir_has_index())
				{
					if (_code) //this for the 500 error 
						return ;
					if (_location.get_autoindex() == "off" || _location.get_autoindex() == "")
					{
						setCodeMsg(403, "Forbidden");
						_body = generateErrorPages(_code);
						return ;
					}
					else if (_location.get_autoindex() == "on")
					{
						setCodeMsg(200, "OK");
						_body = listDirContent(); //check which directory is it always root or  the requested dir?
						_contentType = this->mimeTypes["Default"];
						return ;
					}
				}
				else
					file_handler(_index_file, method);
			}
		}
		else
		{
			setCodeMsg(200, "OK");
			std::string str =  _request.getTarget().substr(1);
			_body = readFileContent(str);
			std::cout << "CGI test/file\n";
			std::cout << "-----target: " << str << std::endl;
			
		}
			//file_handler(getRequestedResource(), method);
	}
}


void		Response::file_handler(std::string file, std::string method)
{
	(void)method;
	// if (!is_loc_has_cgi())
	// {
		if (method == "GET")
		{
			setCodeMsg(200, "OK");
			_body = readFileContent(file);
			_contentType = this->mimeTypes[getFileExtension(file)];
			return ;
		}
	// else
	// 	cgi_handler(method);
}

void Response::deleteFolderContent(const char *path)
{
	DIR *dir = opendir(path);
    if (dir)
	{
    	dirent *entry;
    	while ((entry = readdir(dir)) != NULL)
		{
    	    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
			{
    	        std::string subPath = std::string(path) + "/" + std::string(entry->d_name);
    	        if (entry->d_type == DT_DIR)
				{
    	            deleteFolderContent(subPath.c_str());
    	            rmdir(subPath.c_str());
    	        }
				else
				{
    	            if (remove(subPath.c_str()) == -1)
					{
						if (!access(path, W_OK))
							setCodeMsg(500, "Internal Server Error");
						else
							setCodeMsg(403, "Forbidden");
					}
					else
						setCodeMsg(204, "No Content");
    	        }
    	    }
    	}
    	closedir(dir);
    }
}

std::string Response::getResponseBuffer() const
{
	return (_ResponseBuffer);
}

 bool		Response::get_matched_location_for_request_uri()
{
	// Match location with the requested uri
	// if found this->location = matched location
		return (true);
}
bool		Response::is_loc_has_redir()
{
	//check if the this->location has redirection
	if (_location.get_return().size() > 0)
		return true;
	return false;
	
}

bool		Response::is_dir_has_index()
{
	//check if directory has index files
	std::vector<std::string>::size_type    i = 0;
	std::cout << "*****This is Location****" << _server.get_root_directive() << std::endl;
    if (_location.get_root() != "")
    {
        std::string path = _location.get_root();
        std::ifstream file;
        if (_location.get_index().size() > 0)
        {
            while (i < _location.get_index().size())
            {
                file.open(path.append(_location.get_index()[i]).c_str());
				_index_file = path;
                if (file.is_open())
                    return true;
                i++;
            }
        }
        else
        {
            file.open(path.append("index.html").c_str()); //edited this
			_index_file = path;
            if (file.is_open())
                return true;
        }
    }
    else if (_server.get_root_directive() != "")
    {
        std::string path = _server.get_root_directive();//.append(_location.get_dir());
		std::string newPath;
		if (is_uri_has_slash(path))
		{
			if (_location.get_dir().at(0) == '/')
			{
				newPath.insert(0, path.c_str(), path.size() - 1);
				newPath.append(_location.get_dir());
			}
			else
			{
				newPath.append(path);
				newPath.append(_location.get_dir());
			}
		}
		else
		{
			std::cout << "holaaaaaaa\n";
			std::cout << "lol" << _location.get_dir() << std::endl;
			if (_location.get_dir().at(0) == '/')
			{
				newPath.append(path);
				newPath.append(_location.get_dir());
			}
			else
			{
				newPath.append(path);
				newPath.append("/");
				newPath.append(_location.get_dir());
			}
		}
		if (!is_uri_has_slash(newPath))
			newPath.append("/");
        std::ifstream file;
        file.open(newPath.append("index.html").c_str()); //edited this
		_index_file = newPath;
        if (file.is_open())
		{
            return true;
		}
    }
	else
	{
		setCodeMsg(500, "Internal Server Error");
		_body = generateErrorPages(_code);
	}
    return false;

}

// void		Response::PostMethod()
// {
// 	if (loc_support_upload())
// 	{
// 		setCodeMsg(201, "Created");
// 		std::string file_name = this->_request.getBody();
// 		std::ofstream file;
// 		file.open(file_name);
// 		//_loc = URI of the newly created resource
// 		this->_loc = 
// 	}
// 	else
// 		Get_Post("POST");
// }

void		Response::DeleteMethod()
{
	if (!isResourceExist())
	{
		setCodeMsg(404, "Not Found");
		_body = generateErrorPages(_code);
		return ;
	}
	else
	{
		if (is_directory(getRequestedResource()))
		{
			setCodeMsg(403, "Forbidden");
			_body = generateErrorPages(_code);
			return ;
		}
		else
		{
			// if(!is_loc_has_cgi())
			// {
				if (remove(getRequestedResource().c_str()) == -1)
				{
					char* dir = dirname((char *) getRequestedResource().c_str());
					if (access(dir, W_OK) == -1)
					{
						setCodeMsg(403, "Forbidden");
						_body = generateErrorPages(_code);
						return ;
					}
					else
					{
						setCodeMsg(500, "Internal Server Error");
						_body = generateErrorPages(_code);
						return ;
					}
				}
				else
				{
					setCodeMsg(204, "No Content");
					return ;
				}
			// }
			// else
			// 	cgi_handler("DELETE");
		}
	}
}

std::string	Response::generateErrorPages(int code)
{
	std::string buffer;
	std::stringstream ss;
	ss << code;

	buffer = "<!DOCTYPE html><html lang='en'><head><title>";
	buffer.append(ss.str());
	buffer.append(" ");
	buffer.append(http_codes[code]);
	buffer.append("</title></head><body><center><h1>");
	buffer.append(ss.str());
	buffer.append(" ");
	buffer.append(http_codes[code]);
	buffer.append("</h1></center><hr><center>webserv/1.1</center></body></html>");
	return buffer;
}

/**------------------------------------------------Private Methods-----------------------------------------*/

// bool		Response::isUriAllowed()
// {
// 	std::string		uri = this->_request.getTarget();
// 	const std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
//   	for (std::string::const_iterator it = uri.begin(); it != uri.end(); ++it)
//   	{
//   	  if (allowedChars.find(*it) == std::string::npos)
//   	    return false;
//   	}
//   	return true;
// }

bool		Response::is_method_allowed()
{
	/**
	 * if request.getMethod() exist in allowed methods by the server
	 * 
	 */
	std::vector<std::string> allowed = _location.get_limitexcept();
	if (allowed.size() == 0)
		return true;
	for (std::vector<std::string>::iterator it = allowed.begin(); it != allowed.end(); it++)
	{
		if (_request.getMethod() == *it)
			return true;
	}
	return false;
}

std::string Response::getRequestedResource()
{
	//get the requested file from the uri
	std::string server_path = "/Users/het-tale/cursus/42_webserv";
	return server_path.append(this->_request.getTarget());
	
}

bool Response::isResourceExist()
{
	//check if the requested Resource exist in the root directory
    std::string filename = getRequestedResource();  // Name of the file to search for
    struct stat fileInfo;
	if (stat(filename.c_str(), &fileInfo) == 0)
		return true;
	return false;
}

bool		Response::is_directory(std::string fileName)
{
	struct stat fileInfo;
	if (stat(fileName.c_str(), &fileInfo) == 0)
	{
		if (S_ISDIR(fileInfo.st_mode))
			return true;
	}
	return false;
}

bool		Response::is_uri_has_slash(std::string uri)
{
	//std::string uri = getRequestedResource();
	std::string::reverse_iterator it = uri.rbegin();
	if (*it == '/')
		return true;
	return false;
}

std::string	Response::readFileContent(std::string file_name)
{
	std::ifstream file(file_name.c_str());  // Open file for reading //edited this
	std::string buffer;
    std::string line;
    
    if (file.is_open())
	{
        while (getline(file, line))
		{
			buffer.append(line);
			buffer.append("\n");
        }
        file.close();  // Close file when done
    }
	return buffer;
}

std::string	Response::listDirContent()
{
	std::string htmlFile;

	DIR *dir;
    struct dirent *ent;
    struct stat st;
	std::stringstream ss;

	std::string d = "../";
	d.append(this->_location.get_dir());
	dir = opendir(d.c_str());
	htmlFile = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Index of ";
	htmlFile.append(this->_location.get_dir());
	htmlFile.append("</title></head><body><h1>Index of ");
	htmlFile.append(this->_location.get_dir());
	htmlFile.append("</h1><table><thead><tr><th style='padding: 10px;'>Name</th><th style='padding: 10px;'>Size</th><th style='padding: 10px;'>Last Modified</th></tr></thead><tbody>");
    if (dir != NULL)
	{
        while ((ent = readdir(dir)) != NULL)
		{
            stat(ent->d_name, &st);
			htmlFile.append("<tr><td style='padding-left: 10px;'>");
			htmlFile.append(ent->d_name);
			htmlFile.append("</td>");
			htmlFile.append("<td style='padding-left: 10px;'>");
			ss << st.st_size;
			htmlFile.append(ss.str());
			htmlFile.append("</td>");
			htmlFile.append("<td style='padding-left: 10px;'>");
			htmlFile.append(ctime(&st.st_ctime));
			htmlFile.append("</td></tr>");
        }
        closedir(dir);
    }
	htmlFile.append("</tbody></table></body></html>");
	return htmlFile;
}

// bool		Response::loc_support_upload()
// {
// 	// if (!this->_location.get_client_body_temp_path().empty())
// 	// 	return true;
// 	// return false;
// }

int			Response::getPositionOfLastDot(std::string file)
{
	std::string::iterator	it;
	int						position = -1;
	int						i = 0;
	
	for (it = file.begin(); it != file.end(); it++)
	{
		if (*it == '.')
			position = i;
		i++;
	}
	return position;
}

std::string	Response::getFileExtension(std::string file)
{
	int	position = getPositionOfLastDot(file);
	if (position != -1)
		return file.substr(position + 1);
	return "Default";
}

void		Response::init_http_codes()
{
	this->http_codes.insert(std::make_pair(100, "Continue"));
	this->http_codes.insert(std::make_pair(101, "Switching Protocols"));
	this->http_codes.insert(std::make_pair(102, "Processing"));
	
	this->http_codes.insert(std::make_pair(200, "OK"));
	this->http_codes.insert(std::make_pair(201, "Created"));
	this->http_codes.insert(std::make_pair(202, "Accepted"));
	this->http_codes.insert(std::make_pair(203, "Non-Authoritative Information"));
	this->http_codes.insert(std::make_pair(204, "No Content"));
	this->http_codes.insert(std::make_pair(205, "Reset Content"));
	this->http_codes.insert(std::make_pair(206, "Partial Content"));
	this->http_codes.insert(std::make_pair(207, "Multi-Status"));
	this->http_codes.insert(std::make_pair(208, "Already Reported"));
	this->http_codes.insert(std::make_pair(226, "IM Used"));
	
	this->http_codes.insert(std::make_pair(300, "Multiple Choices"));
	this->http_codes.insert(std::make_pair(301, "Moved Permanently"));
	this->http_codes.insert(std::make_pair(302, "Found"));
	this->http_codes.insert(std::make_pair(303, "See Other"));
	this->http_codes.insert(std::make_pair(304, "Not Modified"));
	this->http_codes.insert(std::make_pair(305, "Use Proxy"));
	this->http_codes.insert(std::make_pair(306, "Switch Proxy"));
	this->http_codes.insert(std::make_pair(307, "Temporary Redirect"));
	this->http_codes.insert(std::make_pair(308, "Permanent Redirect"));
	
	this->http_codes.insert(std::make_pair(400, "Bad Request"));
	this->http_codes.insert(std::make_pair(401, "Unauthorized"));
	this->http_codes.insert(std::make_pair(402, "Payment Required"));
	this->http_codes.insert(std::make_pair(403, "Forbidden"));
	this->http_codes.insert(std::make_pair(404, "Not Found"));
	this->http_codes.insert(std::make_pair(405, "Method Not Allowed"));
	this->http_codes.insert(std::make_pair(406, "Not Acceptable"));
	this->http_codes.insert(std::make_pair(407, "Proxy Authentication Required"));
	this->http_codes.insert(std::make_pair(408, "Request Timeout"));
	this->http_codes.insert(std::make_pair(409, "Conflict"));
	this->http_codes.insert(std::make_pair(410, "Gone"));
	this->http_codes.insert(std::make_pair(411, "Length Required"));
	this->http_codes.insert(std::make_pair(412, "Precondition Failed"));
	this->http_codes.insert(std::make_pair(413, "Payload Too Large"));
	this->http_codes.insert(std::make_pair(414, "URI Too Long"));
	this->http_codes.insert(std::make_pair(415, "Unsupported Media Type"));
	this->http_codes.insert(std::make_pair(416, "Range Not Satisfiable"));
	this->http_codes.insert(std::make_pair(417, "Expectation Failed"));
	this->http_codes.insert(std::make_pair(418, "I'm a teapot"));
	this->http_codes.insert(std::make_pair(421, "Misdirected Request"));
	this->http_codes.insert(std::make_pair(422, "Unprocessable Entity"));
	this->http_codes.insert(std::make_pair(423, "Locked"));
	this->http_codes.insert(std::make_pair(424, "Failed Dependency"));
	this->http_codes.insert(std::make_pair(426, "Upgrade Required"));
	this->http_codes.insert(std::make_pair(428, "Precondition Required"));
	this->http_codes.insert(std::make_pair(429, "Too Many Requests"));
	this->http_codes.insert(std::make_pair(431, "Request Header Fields Too Large"));
	this->http_codes.insert(std::make_pair(451, "Unavailable For Legal Reasons"));
	
	this->http_codes.insert(std::make_pair(500, "Internal Server Error"));
	this->http_codes.insert(std::make_pair(501, "Not Implemented"));
	this->http_codes.insert(std::make_pair(502, "Bad Gateway"));
	this->http_codes.insert(std::make_pair(503, "Service Unavailable"));
	this->http_codes.insert(std::make_pair(504, "Gateway Timeout"));
	this->http_codes.insert(std::make_pair(505, "HTTP Version Not Supported"));
	this->http_codes.insert(std::make_pair(506, "Variant Also Negotiates"));
	this->http_codes.insert(std::make_pair(507, "Insufficient Storage"));
	this->http_codes.insert(std::make_pair(508, "Loop Detected"));
	this->http_codes.insert(std::make_pair(510, "Not Extended"));
	this->http_codes.insert(std::make_pair(511, "Network Authentication Required"));
}

void		Response::init_mime_types()
{
	mimeTypes.insert(std::make_pair("Default", "application/octet-stream"));
	
	mimeTypes.insert(std::make_pair("html", "text/html"));
    mimeTypes.insert(std::make_pair("htm", "text/html"));
    mimeTypes.insert(std::make_pair("shtml", "text/html"));
    mimeTypes.insert(std::make_pair("css", "text/css"));
    mimeTypes.insert(std::make_pair("xml", "text/xml"));
    mimeTypes.insert(std::make_pair("rss", "text/xml"));
    mimeTypes.insert(std::make_pair("gif", "image/gif"));
    mimeTypes.insert(std::make_pair("jpeg", "image/jpeg"));
    mimeTypes.insert(std::make_pair("jpg", "image/jpeg"));
    mimeTypes.insert(std::make_pair("js", "application/x-javascript"));
    mimeTypes.insert(std::make_pair("txt", "text/plain"));
    mimeTypes.insert(std::make_pair("htc", "text/x-component"));
    mimeTypes.insert(std::make_pair("mml", "text/mathml"));
    mimeTypes.insert(std::make_pair("png", "image/png"));
    mimeTypes.insert(std::make_pair("ico", "image/x-icon"));
    mimeTypes.insert(std::make_pair("jng", "image/x-jng"));
    mimeTypes.insert(std::make_pair("wbmp", "image/vnd.wap.wbmp"));
    mimeTypes.insert(std::make_pair("jar", "application/java-archive"));
    mimeTypes.insert(std::make_pair("war", "application/java-archive"));
    mimeTypes.insert(std::make_pair("ear", "application/java-archive"));
    mimeTypes.insert(std::make_pair("hqx", "application/mac-binhex40"));
    mimeTypes.insert(std::make_pair("pdf", "application/pdf"));
    mimeTypes.insert(std::make_pair("cco", "application/x-cocoa"));
    mimeTypes.insert(std::make_pair("jardiff", "application/x-java-archive-diff"));
    mimeTypes.insert(std::make_pair("jnlp", "application/x-java-jnlp-file"));
    mimeTypes.insert(std::make_pair("run", "application/x-makeself"));
    mimeTypes.insert(std::make_pair("pl", "application/x-perl"));
    mimeTypes.insert(std::make_pair("pm", "application/x-perl"));
    mimeTypes.insert(std::make_pair("prc", "application/x-pilot"));
    mimeTypes.insert(std::make_pair("pdb", "application/x-pilot"));
    mimeTypes.insert(std::make_pair("rar", "application/x-rar-compressed"));
    mimeTypes.insert(std::make_pair("rpm", "application/x-redhat-package-manager"));
    mimeTypes.insert(std::make_pair("sea", "application/x-sea"));
    mimeTypes.insert(std::make_pair("swf", "application/x-shockwave-flash"));
    mimeTypes.insert(std::make_pair("sit", "application/x-stuffit"));
    mimeTypes.insert(std::make_pair("tcl", "application/x-tcl"));
    mimeTypes.insert(std::make_pair("tk", "application/x-tcl"));
    mimeTypes.insert(std::make_pair("der", "application/x-x509-ca-cert"));
    mimeTypes.insert(std::make_pair("pem", "application/x-x509-ca-cert"));
    mimeTypes.insert(std::make_pair("crt", "application/x-x509-ca-cert"));
    mimeTypes.insert(std::make_pair("xpi", "application/x-xpinstall"));
    mimeTypes.insert(std::make_pair("zip", "application/zip"));
    mimeTypes.insert(std::make_pair("deb", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("bin", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("exe", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("dll", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("dmg", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("eot", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("iso", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("img", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("msi", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("msp", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("msm", "application/octet-stream"));
    mimeTypes.insert(std::make_pair("mp3", "audio/mpeg"));
    mimeTypes.insert(std::make_pair("ra", "audio/x-realaudio"));
    mimeTypes.insert(std::make_pair("mpeg", "video/mpeg"));
    mimeTypes.insert(std::make_pair("mpg", "video/mpeg"));
    mimeTypes.insert(std::make_pair("mov", "video/quicktime"));
    mimeTypes.insert(std::make_pair("flv", "video/x-flv"));
    mimeTypes.insert(std::make_pair("avi", "video/x-msvideo"));
    mimeTypes.insert(std::make_pair("wmv", "video/x-ms-wmv"));
    mimeTypes.insert(std::make_pair("asx", "video/x-ms-asf"));
    mimeTypes.insert(std::make_pair("asf", "video/x-ms-asf"));
    mimeTypes.insert(std::make_pair("mng", "video/x-mng"));
}