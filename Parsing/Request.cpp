#include "Request.hpp"
#include <fstream>

Request::Request() : chunk_size(1), current_length(0), request_data(std::string()), index(0), current_pos(0), start_line_section(true), headers_section(false),
					 body_section(false), serv(ft::server()), flag(0), fileData(std::pair<std::string, size_t>()), method(std::string()), target(std::string()),
					 http_version(std::string()), header_fields(std::map<std::string, std::vector<std::string> >()), chunk_size_line(true),
					 requestBody(std::string()), loc(ft::location()), matchedServ(false), request_end(false), 
					 body_length(0), errorCode(0), _bodyFile(std::string()), chunkedBody(false), unchunkedBody(false), FirstSection(true), i_index(0) {}

Request::Request(Request const &x)
{
	chunk_size = x.getChunkSize();
	current_length = x.getCurrentLength();
	request_data = x.getRequestData();
	index = x.getIndex();
	current_pos = x.getCurrentPos();
	start_line_section = x.getStartLineSection();
	headers_section = x.getHeadersSection();
	body_section = x.getBodySection();
	serv = x.getServer();
	flag = x.getflag();
	fileData = x.getFileData();
	method = x.getMethod();
	target = x.getTarget();
	http_version = x.getHttpVersion();
	header_fields = x.getHeaderFields();
	chunk_size_line = x.getChunkSizeLine();
	requestBody = x.getRequestBody();
	loc = x.getLoc();
	matchedServ = x.getMatchedServ();
	request_end = x.getRequestEnd();
	body_length = x.getBodyLength();
	errorCode = x.getErrorCode();
	_bodyFile = x.get_bodyFile();
	chunkedBody = x.getChunkedBody();
	unchunkedBody = x.getUnchunkedBody();
	FirstSection = x.getFirstSection();
	i_index = x.getI_index();
}

Request &Request::operator=(Request const &x)
{
	request_data = x.getRequestData();
	index = x.getIndex();
	current_pos = x.getCurrentPos();
	start_line_section = x.getStartLineSection();
	headers_section = x.getHeadersSection();
	body_section = x.getBodySection();
	serv = x.getServer();
	flag = x.getflag();
	fileData = x.getFileData();
	method = x.getMethod();
	target = x.getTarget();
	http_version = x.getHttpVersion();
	header_fields = x.getHeaderFields();
	chunk_size_line = x.getChunkSizeLine();
	requestBody = x.getRequestBody();
	loc = x.getLoc();
	matchedServ = x.getMatchedServ();
	request_end = x.getRequestEnd();
	body_length = x.getBodyLength();
	errorCode = x.getErrorCode();
	_bodyFile = x.get_bodyFile();
	chunkedBody = x.getChunkedBody();
	unchunkedBody = x.getUnchunkedBody();
	FirstSection = x.getFirstSection();
	i_index = x.getI_index();

	return (*this);
}

size_t	Request::getI_index() const
{
	return (i_index);
}

bool	Request::getFirstSection() const
{
	return (FirstSection);
}

void Request::setChunkedBody(bool x)
{
	chunkedBody = x;
}

void Request::setUnchunkedBody(bool x)
{
	unchunkedBody = x;
}

bool Request::getChunkedBody() const
{
	return (chunkedBody);
}

bool Request::getUnchunkedBody() const
{
	return (unchunkedBody);
}

std::string Request::get_bodyFile() const
{
	return (_bodyFile);
}

int Request::getErrorCode() const
{
	return (errorCode);
}

size_t Request::getBodyLength() const
{
	return (body_length);
}

bool Request::getRequestEnd() const
{
	return (request_end);
}

bool Request::getMatchedServ() const
{
	return (matchedServ);
}

void Request::setLoc(ft::location x)
{
	loc = x;
}

ft::location Request::getLoc() const
{
	return (loc);
}

size_t Request::getChunkSize() const
{
	return (chunk_size);
}

size_t Request::getCurrentLength() const
{
	return (current_length);
}

bool Request::getChunkSizeLine() const
{
	return (chunk_size_line);
}

size_t Request::getCurrentPos() const
{
	return (current_pos);
}

size_t Request::getIndex() const
{
	return (index);
}

std::string Request::getRequestData() const
{
	return (request_data);
}

bool Request::getStartLineSection() const
{
	return (start_line_section);
}

bool Request::getHeadersSection() const
{
	return (headers_section);
}

bool Request::getBodySection() const
{
	return (body_section);
}

int Request::getflag() const
{
	return (flag);
}

std::pair<std::string, size_t> Request::getFileData() const
{
	return (fileData);
}

std::map<std::string, std::vector<std::string> > Request::getHeaderFields() const
{
	return (header_fields);
}

std::string Request::getMethod() const
{
	return (method);
}

std::string Request::getTarget() const
{
	return (target);
}

std::string Request::getHttpVersion() const
{
	return (http_version);
}

void Request::setMethod(std::string x)
{

	method = x;
}

void Request::setTarget(std::string x)
{
	target = x;
}

void Request::setHttpVersion(std::string x)
{
	http_version = x;
}

std::string Request::getRequestBody() const
{
	return (requestBody);
}

void Request::setHeaderFields(std::pair<std::string, std::vector<std::string> > value)
{
	if (value.first == "Cookie:" && header_fields.find("Cookie:") != header_fields.end())
	{
		for (size_t i = 0; i < value.second.size(); i++)
			header_fields.find("Cookie:")->second.push_back(value.second[i]);
	}
	else
		header_fields.insert(value);
}

ft::server Request::getServer() const
{
	return (serv);
}

void Request::setServer(ft::server s)
{
	serv = s;
}

std::vector<std::string> Request::get_tokens(std::string line, std::string delimiter)
{
	size_t _start = 0;
	size_t _end = 0;
	std::string token;
	std::vector<std::string> tokens;

	if (delimiter == " ")
		line.push_back(delimiter[0]);
	while ((_end = line.find(delimiter, _start)) != std::string::npos)
	{
		token = line.substr(_start, _end - _start);
		_start = _end + delimiter.size();
		if (!token.empty())
			tokens.push_back(token);
	}

	return (tokens);
}

void Request::setRequestLine(std::string line)
{

	std::vector<std::string> tokens;
	std::string attributes[3] = {"method", "target", "http_version"};
	void (Request::*f1[3])(std::string) = {&Request::setMethod, &Request::setTarget, &Request::setHttpVersion};

	tokens = get_tokens(line, " ");
	if (tokens.size() != 3)
	{
		errorCode = 400;
		return;
	}

	for (std::vector<std::string>::size_type i = 0; i < tokens.size(); i++)
		(this->*f1[i])(tokens[i]);
}

void Request::setHeaderLine(std::string line)
{
	std::vector<std::string> tokens;
	std::vector<std::string> val;

	tokens = get_tokens(line, " ");

	// throw_Errors_here
	if (tokens.size() < 2)
	{
		errorCode = 400;
		return;
	}

	for (std::vector<std::string>::size_type i = 1; i < tokens.size(); i++)
		val.push_back(tokens[i]);

	setHeaderFields(std::make_pair(tokens[0], val));
}


void Request::serverMatching(int socket, std::map<int, std::vector<ft::server> > socket_servers)
{
	if (!matchedServ)
	{

		if (header_fields.find("Host:") == header_fields.end())
		{
			errorCode = 400;
			return;
		}

		std::string toMatch;
		std::string hostValue;
		bool matched = false;

		if (header_fields.find("Host:")->second.size())
			hostValue = header_fields.find("Host:")->second[0] + ":";
		std::vector<std::string> tokens = get_tokens(hostValue, ":");
		std::map<int, std::vector<ft::server> >::iterator It = socket_servers.find(socket);

		if (tokens.size())
			toMatch = tokens[0];

		if (It != socket_servers.end())
		{
			for (std::vector<ft::server>::size_type i = 0; i < (It->second).size(); i++)
			{
				for (std::vector<std::string>::size_type y = 0; y < (It->second)[i].get_server_name_directive().size(); y++)
				{
					if ((It->second)[i].get_server_name_directive()[y] == toMatch)
					{
						serv = (It->second)[i];
						matched = true;
						break;
					}
				}
				if (matched)
					break;
			}
			if (!matched && It->second.size())
				serv = It->second[0];
		}
		matchedServ = true;
	}
}

bool Request::find_line(std::string s, size_t current_pos, std::string &line)
{

	size_t i = 0;
	if ((i = s.find("\r\n", current_pos)) != std::string::npos)
	{
		
		index = i;
		
		line = s.substr(current_pos, i - current_pos);
				
		request_data = s.substr(i + 2, s.size() - (i + 2));
		
		return (true);
	}
	return (false);
}

void Request::checkRequestErrors()
{
	if (method == "POST" && header_fields.find("Content-Length:") == header_fields.end() && header_fields.find("Transfer-Encoding:") == header_fields.end())
	{
		errorCode = 400;
		return;
	}

	if ((header_fields.find("Transfer-Encoding:") != header_fields.end() && header_fields.find("Transfer-Encoding:")->second.size() > 1) ||
		(header_fields.find("Transfer-Encoding:") != header_fields.end() && header_fields.find("Transfer-Encoding:")->second.size() && header_fields.find("Transfer-Encoding:")->second[0] != "chunked"))
	{
		errorCode = 501;
		return;
	}
}

void Request::checkUriErrors()
{
	std::string uri = target;
	std::string allowedUriContent("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%");

	/*********[check uri len]**********/

	if (uri.size() > 2048)
	{
		errorCode = 414;
		return;
	}

	/*********[check uri characters]**********/

	for (std::string::size_type i = 0; i < uri.size(); i++)
	{
		if (allowedUriContent.find(uri[i], 0) == std::string::npos)
		{
			errorCode = 400;
			return;
		}
	}
}

bool Request::isHexStr(std::string s)
{
	for (std::string::size_type i = 0; i < s.size(); i++)
	{
		if (!isHexChar(s[i]))
			return (false);
	}
	return (true);
}

bool Request::isHexChar(char c)
{
	std::string str1("0123456789abcdef");
	std::string str2("0123456789ABCDEF");

	for (std::string::size_type i = 0; i < str1.size(); i++)
	{
		if (c == str1[i])
			return (true);
	}

	for (std::string::size_type i = 0; i < str2.size(); i++)
	{
		if (c == str2[i])
			return (true);
	}
	return (false);
}

int Request::hexToDecHelper(char c)
{
	std::string str1("0123456789abcdef");
	std::string str2("0123456789ABCDEF");

	for (std::string::size_type i = 0; i < str1.size(); i++)
	{
		if (c == str1[i])
			return (i);
	}

	for (std::string::size_type i = 0; i < str2.size(); i++)
	{
		if (c == str2[i])
			return (i);
	}
	return (0);
}

size_t Request::hexToDec(std::string s)
{
	// std::cerr  << "////•> " << "1 <=> "<< s <<" <•////" ;
	size_t len = 0;
	size_t j = 0;
	int i = s.size(); // edited this

	if (i)
		i--;
	while (i >= 0)
	{
		len += hexToDecHelper(s[i]) * pow(16.00, j);
		j++;
		i--;
	}
	// std::cerr  << "////•> " << "2 <=>"<< s <<" <•////" ;
	return (len);
}

void Request::CheckBodyMaxSize()
{
	if (!serv.get_max_body_size_directive().empty())
	{
		size_t maxSizeAllowed = std::atoi(serv.get_max_body_size_directive().c_str());
		if (body_length > maxSizeAllowed)
		{
			errorCode = 413;
			return;
		}
	}
}

void Request::CheckBodyMaxSizee(size_t ln)
{
	if (!serv.get_max_body_size_directive().empty())
	{
		size_t maxSizeAllowed = std::atoi(serv.get_max_body_size_directive().c_str());
		if (body_length + ln > maxSizeAllowed)
		{
			errorCode = 413;
			return;
		}
	}
}

void Request::transferEncodingChunked(std::string s1)
{

	if (chunk_size_line)
	{
		
		current_length = 0;
		std::string line = s1 + ";";
		std::vector<std::string> tokens = get_tokens(line, ";");
		if (tokens.size())
		{
			chunk_size = hexToDec(tokens[0]);
		}
		if (chunk_size == 0)
		{
			
			body_section = false;
			request_end = true;
			chunkedBody = false;
		}
		chunk_size_line = false;

	}
	else
	{
		std::ofstream writeObj;
		if (_bodyFile.empty())
			_bodyFile = generate_file_name();
		writeObj.open(_bodyFile.c_str(), std::ios::out | std::ios::app);
		if (!writeObj.is_open())
		{
			
			errorCode = 500;
			if (errorCase())
				return;
		}
		else
		{

			
			if (isHexStr(s1))
			{
				
				int check = hexToDec(s1);
				
				
				if (check == 0)
				{
					
					body_section = false;
					request_end = true;
					chunkedBody = false;
					chunk_size_line = false;
					return;
				}
				else
				{

					return;
				}
			}

			writeObj << s1;
			writeObj.close();
			
			current_length += s1.size();
			
			
			body_length += current_length;
			if (current_length == chunk_size)
			{
				chunk_size_line = true;
				CheckBodyMaxSize();
				if (errorCase())
					return;
			}
		}
	}
}

void	Request::extractContentLen(size_t &len)
{
	std::string s;

	if (header_fields.find("Content-Length:") != header_fields.end())
	{
		s = header_fields.find("Content-Length:")->second[0];

		for (size_t i = 0; i < s.size(); i++)
		{
			if ( !(s[i] >= '0' && s[i] <= '9') )
			{
				errorCode = 400;
				return;
			}
		}

		len = std::atoi(s.c_str());
	}
}

void Request::CheckBody()
{
	size_t ln = 0;
	
	FirstSection = false;
	if (header_fields.find("Content-Length:") == header_fields.end() && header_fields.find("Transfer-Encoding:") == header_fields.end())
	{
		
		request_end = true;
		body_section = false;
		
	}
	else if(method == "GET" && (header_fields.find("Content-Length:") != header_fields.end() || header_fields.find("Transfer-Encoding:") != header_fields.end()))
	{
		request_end = true;
		body_section = false;
	}
	else if(method == "DELETE" && (header_fields.find("Content-Length:") != header_fields.end() || header_fields.find("Transfer-Encoding:") != header_fields.end()))
	{
		request_end = true;
		body_section = false;
	}
	else if (header_fields.find("Transfer-Encoding:") != header_fields.end())
	{
		body_section = true;
		chunkedBody = true;
		request_data.insert(0, "\r\n");
		// std::cerr << "CHECKED" ;
	}
	else if (header_fields.find("Content-Length:") != header_fields.end())
	{
		
		unchunkedBody = true;
		chunkedBody = false;
		extractContentLen(ln);
		if (errorCase())
			return;
		if (!serv.get_max_body_size_directive().empty())
		{
			size_t maxSizeAllowed = std::atoi(serv.get_max_body_size_directive().c_str());
			if (ln  > maxSizeAllowed)
			{
				errorCode = 413;
				return;
			}
		}
	}

}

void Request::ContentLengthCase()
{
	std::ofstream writeObj;
	std::string s1;

	if (_bodyFile.empty())
		_bodyFile = generate_file_name();
	writeObj.open(_bodyFile.c_str(), std::ios::out | std::ios::app);
	if (!writeObj.is_open())
	{
		
		errorCode = 500;
		if (errorCase())
			return;
	}
	else
	{
		
		s1 = getStrToAdd();
		writeObj << s1;
		writeObj.close();
		
		body_length += s1.size();
		CheckBodyMaxSize();
		if (errorCase())
			return;
		
		if (header_fields.find("Content-Length:")->second.size() && body_length == (unsigned long)(std::atoi(header_fields.find("Content-Length:")->second[0].c_str())))
		{
			unchunkedBody = false;
			request_end = true;
		}

	}
}

bool Request::parse(int socket, std::string s, std::map<int, std::vector<ft::server> > m)
{
	 std::string _line;
	

	errorCode = 0;
	request_data.append(s);


	if (FirstSection  && !request_end)
	{
		while (FirstSection && !request_end && find_line(request_data, 0, _line))
		{

			if (start_line_section)
			{
				setRequestLine(_line);
				if (errorCase())
					return (true);
				start_line_section = false;
				headers_section = true;
				// current_pos = 0;
				checkUriErrors();
				if (errorCase())
					return (true);
			}
			else if (headers_section)
			{
				if (index == 0)
				{

					headers_section = false;
					checkRequestErrors();
					if (errorCase())
						return (true);
					serverMatching(socket, m);
					if (errorCase())
						return (true);
					locationMatching();
					if (errorCase())
						return (true);
					CheckBody();
				}
				else
				{
					setHeaderLine(_line);
					if (errorCase())
						return (true);
				}

				
			}

		}
	}
	if (unchunkedBody && !request_end)
	{
		

		ContentLengthCase();
		
				
		if (errorCase())
			return (true);
	}
	if (chunkedBody && !request_end)
	{
					
		size_t 			a = 0;
		size_t 			b = 0;
		std::string		 s;
		std::ofstream writeObj;
		bool condition = true;

		while (chunk_size > 0 && condition)
		{
			condition = false;
			if (chunk_size_line)
			{
				if ( ((a = request_data.find("\r\n", i_index )) != std::string::npos)   &&  ((b = request_data.find("\r\n", a + 2)) != std::string::npos)  && a != b  )
				{
					condition = true;
					s = request_data.substr(a + 2, b - (a + 2));
					i_index  = b + 2;
					chunk_size = hexToDec(s);
					chunk_size_line = false;
					current_length = 0;
					CheckBodyMaxSizee(chunk_size);
					if (errorCase())
						return (true);
					
					if (chunk_size == 0)
					{

						body_section = false;
						chunkedBody = false;
						request_end = true;				
					}
				}
			}
			
			else
			{
				
				
						
				if (_bodyFile.empty())
				{
					_bodyFile = generate_file_name();
				}
				writeObj.open(_bodyFile.c_str(), std::ios::out | std::ios::app);
				if (!writeObj.is_open())
				{
				
					errorCode = 500;
					if (errorCase())
						return (true);
				}
				else 
				{
					

					while (current_length < chunk_size && i_index  <  request_data.size() )
					{
						
						condition = true;
						writeObj << request_data[i_index++];	
						current_length++;
						body_length++;
						CheckBodyMaxSize();
						if (errorCase())
							return (true);
						if (current_length == chunk_size)
						{

							chunk_size_line = true;
						}
							
					}

					writeObj.close();


				}
			

			}
		}

	}

	return (request_end);
}

void	Request::transferEncodingChunked2()
{
	std::string line_;

	if (chunk_size_line)
	{
		
		find_line(request_data, 0, line_);
		current_length = 0;
		std::vector<std::string> tokens = get_tokens(line_ + ";", ";");
		if (tokens.size())
			chunk_size = hexToDec(tokens[0]);
		if (chunk_size == 0)
		{
			
			body_section = false;
			request_end = true;
			chunkedBody = false;
		}		
		chunk_size_line = false;
	}
	else
	{
		std::ofstream writeObj;

		if (_bodyFile.empty())
			_bodyFile = generate_file_name();
		writeObj.open(_bodyFile.c_str(), std::ios::out | std::ios::app);
		if (!writeObj.is_open())
		{
			
			errorCode = 500;
			if (errorCase())
				return;
		}		
		else
		{
			if (request_data.size() + current_length <= chunk_size)
			{
				writeObj << request_data;
				writeObj.close();
				current_length += request_data.size();
				body_length += current_length;
				if (current_length == chunk_size)
				{
					chunk_size_line = true;
					CheckBodyMaxSize();
					if (errorCase())
						return;				
				}
			}
			else
			{
				
				writeObj << request_data.substr(0, chunk_size - current_length);
				writeObj.close();
				current_length += chunk_size - current_length;
				body_length += current_length;
				request_data = request_data.substr((chunk_size - current_length) , request_data.size() - (chunk_size - current_length));
				if (current_length == chunk_size)
				{
					current_length = 0;
					chunk_size_line = true;
					CheckBodyMaxSize();
					if (errorCase())
						return;				
				}
			}
		}
	}
}


void Request::locationMatching()
{
	std::string uri = target;

	for (size_t i = 0; i < serv.get_location().size(); i++)
	{

		if (serv.get_location()[i].get_dir() == target.substr(0, serv.get_location()[i].get_dir().length())) // edited this
		{
			loc = serv.get_location()[i];
			return;
		}
	}
	errorCode = 404;
	return;
}

void Request::setRequestEnd(bool x)
{
	request_end = x;
}

bool Request::errorCase()
{
	if (errorCode != 0)
	{
		request_end = true;
		return (true);
	}
	return (false);
}

std::string Request::generate_file_name()
{
	std::stringstream strStream;
	std::string str;

	while (true)
	{

		srand((int)time(0));
		int r = rand() % 7000;

		strStream << r;
		strStream >> str;
		str = "./FILES/file" + str;
		if (!isResourceExist(str))
			break;
	}
	
	return (str + getBodyFileExtension());
}

bool Request::isResourceExist(std::string s)
{
	std::string filename = s;
	struct stat fileInfo;

	if (stat(filename.c_str(), &fileInfo) == 0)
		return true;
	return false;
}

std::string Request::getStrToAdd()
{
	std::string s;

	size_t contLen = (unsigned long)(std::atoi(header_fields.find("Content-Length:")->second[0].c_str()));
	if (request_data.size() + body_length > contLen)
	{
		return (request_data.substr(0, contLen - body_length));
	}
	else
	{
		s = request_data;
		request_data.clear();
		return (s);
	}
}

std::string Request::getBodyFileExtension()
{
	std::string extension = "";
	std::string s;
	std::vector<std::string> tokens;

	if (header_fields.find("Content-Type:") != header_fields.end())
	{
		
		s = header_fields.find("Content-Type:")->second[0];
		s.push_back(';');
		tokens = get_tokens(s, ";");
		tokens[0].push_back('/');
		tokens = get_tokens(tokens[0], "/");

		if (tokens.size() > 1)
			extension = "." + tokens[1];
	}
	return (extension);
}

std::string		Request::extractQuerieString()
{
	std::vector<std::string> 	tokens;
	std::string 				s;

	if (target.find("?", 0) != std::string::npos)
	{
		s = target + "?";
		tokens = get_tokens(s, "?");
		if (tokens.size() == 2)
			return (tokens[1]);
	}
	return (std::string());
}

Request::~Request() {}