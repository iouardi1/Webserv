/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:18:48 by het-tale          #+#    #+#             */
/*   Updated: 2023/04/02 03:10:31 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "./CGI.class.hpp"


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
	this->_root = "";
	this->_serv = "webserv/1.1";
	this->_isCGI = false;
	init_http_codes();
	init_mime_types();
	mkdir("./default", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
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
	this->_root = "";
	this->_isOpen = true;
	this->_serv = "webserv/1.1";
	this->_location = _request.getLoc();
	this->_isCGI = false;
	mkdir("./default", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	init_http_codes();
	init_mime_types();
	this->_httpResponsePath = "";
	HandleMultipleCases();
	if (!this->_isCGI)
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
		_request = res._request;
		_server = res._server;
		_location = res._location;
		_code = res._code;
		_fileFd = res._fileFd;
		_msg = res._msg;
		_ResponseBuffer = res._ResponseBuffer;
		_contentType = res._contentType;
		_autoIndex = res._autoIndex;
		_allow = res._allow;
		_loc = res._loc;
		_body = res._body;
		_index_file = res._index_file;
		_serv = res._serv;
		_date = res._date;
		_root = res._root;
		_isAutoIndexed = res._isAutoIndexed;
		_isDir = res._isDir;
		_isCGI = res._isCGI;
		_contentLength = res._contentLength;
		http_codes = res.http_codes;
		_isOpen = res._isOpen;
		mimeTypes = res.mimeTypes;
		_httpResponsePath = res._httpResponsePath;
		_headers = res._headers;
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

std::string	Response::getHttpResponsePath() const
{
	return this->_httpResponsePath;
}

std::string Response::getResponseBuffer() const
{
	return (_ResponseBuffer);
}

std::string	Response::getIndexFile() const
{
	return _index_file;
}

std::string	Response::getServ() const
{
	return _serv;
}

std::fstream&	Response::getRespFile()
{
	return this->respFile;
}
std::fstream&	Response::getFullRespFile()
{
	return this->fullrespFile;
}

bool	Response::getIsOpen() const
{
	return this->_isOpen;
}

std::string Response::getHeaders() const
{
	return this->_headers;
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
	this->_body = body;
}

void Response::setResponseBuffer(std::string buffer)
{
	this->_ResponseBuffer = buffer;
}

void	Response::appendResponseBuffer(std::string buffer)
{
	this->_ResponseBuffer += buffer;
}

void	Response::set_Headers(std::string headers)
{
	this->_headers = headers;
}

void	Response::appendHeaders(std::string headers)
{
	this->_headers += headers;
}

void	Response::setHttpResponsePath(std::string path)
{
	this->_httpResponsePath = path;
}

void	Response::setContentType(std::string type)
{
	this->_contentType = type;
}
/**------------------------------------------------Public Methods-----------------------------------------*/

void		Response::buildHttpResponse()
{
	setStatusLine();
	_headers.append("\r\n");
	setHeaders();
	_headers.append("\r\n");
}

void		Response::setStatusLine()
{
	std::stringstream ss;
	ss << _code;
	_headers.append("HTTP/1.1 ");
	_headers.append(ss.str());
	_headers.append(" ");
	_headers.append(_msg);
}

void		Response::setHeaders()
{
	std::stringstream ss;
	struct stat fileInfo;
	if (stat(_httpResponsePath.c_str(), &fileInfo) == 0)
	{
		_contentLength =fileInfo.st_size;
	}
	ss << _contentLength;
	if (_contentType != "")
	{
		_headers.append("Content-Type: ");
		_headers.append(_contentType);
		_headers.append("\r\n");
	}
	_headers.append("Content-length: ");
	_headers.append(ss.str());
	_headers.append("\r\n");
	if(_allow != "")
	{
		_headers.append("Allow: ");
		_headers.append(_allow);
		_headers.append("\r\n");
	}
	if(_loc != "")
	{
		_headers.append("Location: ");
		_headers.append(_loc);
		_headers.append("\r\n");
	}
	_headers.append("Server: ");
	_headers.append(_serv);
	_headers.append("\r\n");
	time_t now = time(0);
    struct tm* timeinfo = gmtime(&now);
    char buffer[80];

    strftime(buffer, 80, "Date: %a, %d %b %Y %H:%M:%S GMT", timeinfo);
	_headers.append(buffer);
	_headers.append("\r\n");
}

void		Response::setMessageBody()
{
	_ResponseBuffer.append(_body);
	if (fullrespFile.is_open())
		fullrespFile.close();
	std::ofstream output(this->_httpResponsePath.c_str(), std::ios::app);
	//fullrespFile.open(this->_httpResponsePath.c_str(), std::ios::app);
	if (respFile.is_open())
		respFile.close();
	std::ifstream rd("./temp/respFile");
	//respFile.open("./temp/respFile", std::ios::in);
	char b[1024];
	std::string st;
	if (rd.is_open())
	{
	// while (!rd.eof())
	// {
		memset(b, 0, sizeof(b));
		// rd.read(b, sizeof(b));
		// if (output.is_open())
		// {
		// 	st = std::string(b, strlen(b));
		// 	std::cout << "ana mftoh" << std::endl;
		// 	output << st;
			
		// }

		char c;
		while (rd.get(c))
		{
			output << c;
		// std::cout << "HOLA\n";
		}
	}
	// }
	// char c;
	// while (respFile.get(c))
	// {
	// 	fullrespFile.put(c);
	// // std::cout << "HOLA\n";
	// }
	// remove("./temp/respFile");
	output.close();
}

void	Response::setCodeMsg(int code, std::string msg)
{
	this->setCode(code);
	this->setMessage(msg);
}

void	Response::HandleReturnDirective()
{
	if (_location.get_return().at(0) == "301")
	{
		setCodeMsg(301, "Moved Permanently");
		std::string tmp = "http://";
		tmp.append(_request.getHeaderFields()["Host:"][0]);
		tmp.append("/");
		std::string target = _location.get_return().at(1);
		tmp.append(target.append("/"));
		tmp = removeConsecutiveChars(tmp, '/', true);
		this->_loc = tmp;
	}
	else
	{
		ResponseError(std::atoi(_location.get_return().at(0).c_str()));
		_contentType = mimeTypes["html"];
	}
}

void	Response::HandleMethodNotAllowed()
{
	ResponseError(405);
	std::vector<std::string> allowed = _location.get_limitexcept();
	std::vector<std::string>::size_type	i = 0;
	for (std::vector<std::string>::iterator it = allowed.begin(); it != allowed.end(); it++)
	{
		_allow.append(*it);
		if (i != allowed.size() - 1)
			_allow.append(", ");
		i++;
	}
}

void	Response::HandleMultipleCases()
{
	if (_location.get_return().size() > 0)
		HandleReturnDirective();
    else
    {
        if (!is_method_allowed())
			HandleMethodNotAllowed();
        else
        {
            if (!_request.getMethod().compare("GET"))
            	Get_Post("GET");
			else if (!_request.getMethod().compare("DELETE"))
				DeleteMethod();
			else if (!_request.getMethod().compare("POST"))
				PostMethod();
			else
				HandleMethodNotAllowed();
        }
    }
}

void		Response::DeleteMethod()
{
	if (!isResourceExist())
	{
		ResponseError(404);
		_contentType = mimeTypes["html"];
		return ;
	}
	else
	{
		if (is_directory(getRequestedResource()))
		{
			ResponseError(403);
			_contentType = mimeTypes["html"];
			return ;
		}
		else
		{
				if (remove(getRequestedResource().c_str()) == -1)
				{
					char* dir = dirname((char *) getRequestedResource().c_str());
					if (access(dir, W_OK) == -1)
					{
						ResponseError(403);
						_contentType = mimeTypes["html"];
						return ;
					}
					else
					{
						ResponseError(500);
						_contentType = mimeTypes["html"];
						return ;
					}
				}
				else
					setCodeMsg(204, "No Content");
		}
	}
}

bool		Response::is_method_allowed()
{
	std::vector<std::string> allowed = _location.get_limitexcept();
	if (allowed.size() == 0 || find(allowed.begin(), allowed.end(), _request.getMethod()) != allowed.end())
		return true;
	return false;
}

void	Response::ResponseError(int code)
{
	std::stringstream ss;
	int	exist = 0;
    ss << code;
	setCodeMsg(code, http_codes[code]);
	std::vector<std::vector<std::string> > vect = _server.get_error_pages_directive();
	for (std::vector<std::vector<std::string> >::iterator it = vect.begin(); it != vect.end(); it++)
	{
		if ((*it).size() > 0 && (*it)[0] == ss.str() && isResourceExist1((*it)[1]))
		{
			//_body = readFileContent((*it)[1]);
			_httpResponsePath = (*it)[1];
			_contentType = "text/html";
			exist = 1;
			//this->respFile << _body;
			break;
		}
	}
	if (!exist)
	{
		_httpResponsePath = generateErrorPages(_code, "Hasnaa");
		_contentType = "text/html";
	}
}

void	Response::Get_Post(std::string method)
{
	if (!isResourceExist())
	{
		ResponseError(404);
		return ;
	}
	else
	{
        if (is_directory(getRequestedResource()))
		{
			if (!is_uri_has_slash(getRequestedResource()))
			{
					setCodeMsg(301, "Moved Permanently");
					std::string tmp = "http://";
					tmp.append(_request.getHeaderFields()["Host:"][0]);
					tmp.append("/");
					std::string target;
					if (!_request.extractQuerieString().empty())
						target = _request.getTarget().substr(0, _request.getTarget().size() - _request.extractQuerieString().size() - 1);
					else
						target = _request.getTarget();
					tmp.append(target.append("/"));
					tmp = removeConsecutiveChars(tmp, '/', true);
					this->_loc = tmp;
					return ;
			}
			else
			{
				if (!is_dir_has_index())
				{
					if (_code) 
						return ;
					if (_location.get_autoindex() == "off" || _location.get_autoindex() == "")
					{
						ResponseError(403);
						_contentType = this->mimeTypes["html"];
						return ;
					}
					else if (_location.get_autoindex() == "on")
					{
						setCodeMsg(200, "OK");
						_httpResponsePath = listDirContent();
						_contentType = this->mimeTypes["html"];
						return ;
					}
				}
				else
				{
                   file_handler(_index_file, method);
                }
			}
		}
		else
		{
			_index_file = getRequestedResource();
			file_handler(getRequestedResource(), method);
		}
    }
}


std::string		Response::generate_file_name()
{
	std::stringstream	strStream;
	std::string			str;

	while (true)
	{
		
		srand((int) time(0));
		int r = rand() % 7000;


		strStream << r;
		strStream >> str;
		str = "/file" + str;
		if (!isResourceExist1(str))
			break;
	}

	return (str);

}

bool Response::isResourceExist1(std::string s)
{
    std::string filename = s;
    struct stat fileInfo;

    if (stat(filename.c_str(), &fileInfo) == 0)
        return true;
    return false;
}

void		Response::PostMethod()
{
	if (loc_support_upload())
	{
		splitUpload(_location.get_alias());
		std::string file_name = this->_request.get_bodyFile();
		std::string upload_path = _location.get_alias().append("/");
		upload_path.append(generate_file_name());
		upload_path.append(".").append(getFileExtension(getLastDir(file_name, false)));
		upload_path = removeConsecutiveChars(upload_path, '/', false);
		struct stat fileInfo;
		if (stat(upload_path.c_str(), &fileInfo) == 0 || rename(file_name.c_str(), upload_path.c_str()) != 0)
		{
			remove(file_name.c_str());
			this->ResponseError(500);
			return ;
		}
		setCodeMsg(201, "Created");
		this->_loc = "http://";
		this->_loc.append(_request.getHeaderFields()["Host:"][0]);
		this->_loc.append("/").append(this->_location.get_dir()).append("/");
		std::string app = getLastDir(upload_path, true).append("/").append( getLastDir(upload_path, false));
		std::string cp = this->_loc.append(app);
		cp = removeConsecutiveChars(cp, '/', true);
		this->_loc = cp;
	}
	else
		Get_Post("POST");
}


bool		Response::loc_support_upload()
{
	if (_location.get_alias().empty())
		return false;
	return true;
}

bool	Response::is_loc_has_cgi()
{
	if (!_location.get_cgi().empty())
		return true;
	return false;
}

void		Response::file_handler(std::string file, std::string method)
{
	(void)method;
	if (!is_loc_has_cgi())
	{
		if (method == "GET")
		{
			setCodeMsg(200, "OK");
			_httpResponsePath = file;
			_contentType = this->mimeTypes[getFileExtension(file)];
			return ;
		}
		else if (method == "POST")
		{
			ResponseError(403);
			_contentType = this->mimeTypes[getFileExtension(file)];
			return ;
		}
	}
	else
	{
		this->_isCGI = true;
		CGI cgi(_request, _server, *this);
	}
}

std::string	Response::theFullOne(std::string s1, std::string s2)
{
	if (s1.empty())
		return s2;
	return s1;
}

std::string Response::getRequestedResource()
{
	std::string path;
	std::string target;
	std::string res;
    path = _request.getTarget().substr(_location.get_dir().length());
	target = theFullOne(_location.get_root(), _server.get_root_directive());
	res = target.append("/").append(path);
	res = removeConsecutiveChars(res, '/', false);
	if (!_request.extractQuerieString().empty())
		res = res.substr(0, res.size() - _request.extractQuerieString().size() - 1);
	// std::cout << "THE PATH: " << res << std::endl;
	return res;
}

bool Response::isResourceExist()
{
    std::string filename = getRequestedResource();
	//std::cout << "FILENAME: " << filename << std::endl;
    struct stat fileInfo;
	if (stat(filename.c_str(), &fileInfo) == 0)
		return true;
	return false;
}

std::string Response::removeConsecutiveChars(std::string src, char c, bool flag)
{
    std::string result;
	size_t	j = 0;
	if (flag)
	{
		result = src.substr(0, 7);
		j = 7;
	}
	for (size_t i = j; i < src.length(); i++)
	{
		if (i == 0)
			result += src[i];
		else if (src[i] != c || (i > 0 && src[i-1] != c))
			result += src[i];
			
	}
	return result;
}

std::string	Response::generateErrorPages(int code, std::string name)
{
	std::string buffer;
	std::stringstream ss;
	std::ofstream out;
	ss << code;
	std::string path = "./default/";
	path.append(ss.str()).append(".html");
	out.open(path.c_str(), std::ios::out);

	buffer = "<!DOCTYPE html><html lang='en'><head><title>";
	buffer.append(name);
	buffer.append("</title></head><body><center><h1>");
	buffer.append(ss.str());
	buffer.append(" ");
	buffer.append(http_codes[code]);
	buffer.append("</h1></center><hr><center>webserv/1.1</center></body></html>");
	if (out.is_open())
		out << buffer;
	return path;
}

bool		Response::is_uri_has_slash(std::string uri)
{
	std::string::reverse_iterator it = uri.rbegin();
	if (*it == '/')
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


bool		Response::is_dir_has_index()
{
	if (_location.get_root() == "" && _server.get_root_directive() == "")
	{
		ResponseError(404);
		return false;
	}
	std::string path;
	size_t			counter = 0;
	if (_location.get_root() != "" || _server.get_root_directive() != "")
	{
		if (_location.get_index().size() == 0)
		{
			path = getRequestedResource().append("index.html");
			path = removeConsecutiveChars(path, '/', false);
			if (!access(path.c_str(), F_OK))
			{
				_index_file = path;
				_httpResponsePath = path;
				_contentType = this->mimeTypes[getFileExtension(_index_file)];
				return true;
			}
		}
		for (size_t it = 0; it < _location.get_index().size(); it++)
		{
			path = getRequestedResource().append(_location.get_index().at(it));
			path = removeConsecutiveChars(path, '/', false);
			if (!access(path.c_str(), F_OK))
			{
				_index_file = path;
				_httpResponsePath = path;
				_contentType = this->mimeTypes[getFileExtension(_index_file)];
				return true;
			}
			counter++;
		}
		if (counter == _location.get_index().size())
		{
			path = getRequestedResource().append("index.html");
			path = removeConsecutiveChars(path, '/', false);
			if (!access(path.c_str(), F_OK))
			{
				_index_file = path;
				_httpResponsePath = path;
				_contentType = this->mimeTypes[getFileExtension(_index_file)];
				return true;
			}
			return false;
		}
	}
	return false;
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
                    remove(subPath.c_str());
                }
            }
        }
        closedir(dir);
    }
}

std::string    Response::listDirContent()
{
    std::string htmlFile;

    DIR *dir;
    struct dirent *ent;
    struct stat st;
    std::stringstream ss;
    std::ofstream out;
    std::string path = "./default/listing.html";
    out.open(path.c_str(), std::ios::out);

    std::string d = getRequestedResource();
    dir = opendir(d.c_str());
    htmlFile = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Index of ";
    htmlFile.append(d);
    htmlFile.append("</title></head><body><h1>Index of ");
    htmlFile.append(d);
    htmlFile.append("</h1><table><thead><tr><th style='padding: 10px;'>Name</th><th style='padding: 10px;'>Size</th><th style='padding: 10px;'>Last Modified</th></tr></thead><tbody>");
    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            stat(ent->d_name, &st);
            htmlFile.append("<tr><td style='padding-left: 10px;'><a href='");
            htmlFile.append(ent->d_name);
            htmlFile.append("'>");
            htmlFile.append(ent->d_name);
            htmlFile.append("</a></td>");
            htmlFile.append("<td style='padding-left: 10px;'>");
            ss << (st.st_size);
            htmlFile.append(ss.str());
            htmlFile.append("</td>");
            htmlFile.append("<td style='padding-left: 10px;'>");
            htmlFile.append(ctime(&st.st_ctime));
            htmlFile.append("</td></tr>");
        }
        closedir(dir);
    }
    htmlFile.append("</tbody></table></body></html>");
    if (out.is_open())
        out << htmlFile;
    return path;
}

void	Response::splitUpload(std::string path)
{
	char* token = std::strtok((char *)path.c_str(), "/");
	struct stat info;
	std::string l = "";
    while (token != NULL)
	{
        l.append("/");
		l += token;
        // std::cout << "This is L: " << l << std::endl;
		if (stat(l.c_str(), &info) != 0)
		{
			mkdir(l.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}
        token = std::strtok(NULL, "/");
    }
}

std::string	Response::getLastDir(std::string path, bool isDir)
{
	char* token = std::strtok((char *)path.c_str(), "/");
    char* lastToken = token;
	std::string l;
    while (token != NULL)
	{
		l = token;
		if (isDir)
		{
			if (l.find(".") == std::string::npos)
				lastToken = token;
		}
		else
		{
			lastToken = token;
		}
        token = std::strtok(NULL, "/");
    }
	 std::string t = lastToken;
	return t;
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
    mimeTypes.insert(std::make_pair("mp4", "video/mp4"));
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
    mimeTypes.insert(std::make_pair(" ", "application/zip"));
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

std::string	Response:: getFileExtension(std::string file)
{
	int	position = getPositionOfLastDot(file);
	if (position != -1)
		return file.substr(position + 1);
	return "txt";
}

std::string	Response::readFileContent(std::string file_name)
{
	std::ifstream file(file_name.c_str());
	std::string buffer;
    std::string line;
	std::cout << "COUCOU\n";
	if (respFile.is_open())
		respFile.close();
	this->respFile.open("./temp/respFile", std::ios::out | std::ios::app);
    if (file.is_open())
	{
        while (getline(file, line))
		{
			buffer.append(line);
			buffer.append("\n");
			// std::cout << line << std::endl;
			
			if (respFile.is_open())
			{
				//std::cout << line << std::endl;
				this->respFile << line << std::endl;
			}
        }
        file.close();
    }
	this->respFile.close();
	return buffer;
}
