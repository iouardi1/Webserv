#include "Request.hpp"
# include <fstream>

Request::Request() : chunk_size(0), current_length(0), request_data(std::string()),  index(0), current_pos(0), start_line_section(true), headers_section(false),
body_section(false),  serv(ft::server()), flag(0), fileData(std::pair<std::string, size_t>()), method(std::string()),  target(std::string()), 
http_version(std::string()),  header_fields(std::map<std::string, std::vector<std::string> >()),  chunk_size_line(true), 
requestBody(std::string()), loc(ft::location()), matchedServ(false), request_end(false), body_length(0), errorCode(0){}

Request::Request(Request const& x)
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
}

Request& Request::operator=(Request const& x)
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

	return (*this);
}

int 	Request::getErrorCode() const
{
	return (errorCode);
}

size_t	Request::getBodyLength() const
{
	return (body_length);
}

bool	Request::getRequestEnd() const
{
	return (request_end);
}

bool	Request::getMatchedServ() const
{
	return (matchedServ);
}

void	Request::setLoc(ft::location x)
{
	loc = x;
}

ft::location	Request::getLoc() const{
	return (loc);
}

size_t	Request::getChunkSize() const
{
	return (chunk_size);
}


size_t	Request::getCurrentLength() const
{
	return (current_length);
}

bool 	Request::getChunkSizeLine() const
{
	return (chunk_size_line);
}

size_t	Request::getCurrentPos() const
{
	return (current_pos);
}

size_t	Request::getIndex() const
{
	return (index);
}

std::string	Request::getRequestData() const
{
	return (request_data);
}

bool	Request::getStartLineSection() const
{
	return (start_line_section);
}

bool	Request::getHeadersSection() const
{
	return (headers_section);
}

bool	Request::getBodySection() const
{
	return (body_section);
}

int	Request::getflag() const
{
	return (flag);
}

std::pair<std::string, size_t> 	Request::getFileData() const
{
	return (fileData);
}

std::map<std::string, std::vector<std::string> >	Request::getHeaderFields() const
{
	return (header_fields);
}

std::string	Request::getMethod() const
{
	return (method);
}

std::string Request::getTarget() const
{
	return (target);
}

std::string	Request::getHttpVersion() const
{
	return (http_version);
}

void	Request::setMethod(std::string x)
{
	
	method = x;
}

void	Request::setTarget(std::string x)
{
	target = x;
}

void	Request::setHttpVersion(std::string x)
{
	http_version = x;
}

std::string		Request::getRequestBody() const
{
	return (requestBody);
}

void  Request::setHeaderFields(std::pair<std::string, std::vector<std::string> > value)
{
	header_fields.insert(value);
}

ft::server  Request::getServer() const
{
	return (serv);
}

void	Request::setServer(ft::server s)
{
	serv = s;
}

std::vector<std::string>    Request::get_tokens(std::string line, std::string delimiter)
{
  size_t                      _start = 0;
  size_t                      _end = 0;
  std::string                 token;
  std::vector<std::string>    tokens;

  if (delimiter == " ")
    line.push_back(delimiter[0]);
  while ((_end = line.find(delimiter, _start))!= std::string::npos)
  {
    token = line.substr(_start, _end - _start);
      _start = _end + delimiter.size();
    if (!token.empty())
      tokens.push_back(token);
  }

  return (tokens);
}

// void	Request::serverMatching(std::vector<ft::server> virtual_servers)
// {
// 	std::vector<ft::server> matched_servers;
// 	std::vector<ft::server> final_matched_servers;
// 	std::vector<std::string> tokens;
// 	std::vector<std::string> _tokens;
// 	std::string hostValue;
// 	std::string	port;
// 	std::string	ip_address;
// 	std::string	domain_name;

// 	if (header_fields.find("Host:") == header_fields.end())
// 		throw (std::invalid_argument("400 Bad Request"));
// 	hostValue = header_fields.find("Host:")->second + ":";
// 	tokens = get_tokens(hostValue, ":");
// 	if (tokens.size())
// 	{
// 		/***************[set Port]***************/
// 		if (tokens.size() == 1)
// 			port = "80";
// 		else if (tokens.size() == 2)
// 			port = tokens[1];
// 		/***************[check if i have ip_address or a domain name]***************/
// 		_tokens = get_tokens(tokens[0] + ".", ".");
// 		if (_tokens.size() == 4 && _tokens[0].size() == 3 && _tokens[1].size() == 3
// 			&& _tokens[2].size() == 3 && _tokens[3].size() == 3)
// 		{
// 			ip_address = tokens[0];
// 		}
// 		else
// 			domain_name = tokens[0];
// 		/***************[ip_address case]***************/
// 		if (!ip_address.empty())
// 		{
// 			/***************[first : match by ip_address]***************/
// 			for (std::vector<ft::server>::size_type i = 0; i < virtual_servers.size(); i++)
// 			{
// 				if ( ((virtual_servers[i].getPortAndIpAddress()).first).empty() 
// 					|| ((virtual_servers[i].getPortAndIpAddress()).first) == ip_address )
// 				{
// 					matched_servers.push_back(virtual_servers[i]);
// 				}
// 			}
// 			/***************[second : match by port]***************/
// 			for (std::vector<ft::server>::size_type i = 0; i < matched_servers.size(); i++)
// 			{
// 				if ( !((matched_servers[i].getPortAndIpAddress()).second).empty() 
// 					&& ((matched_servers[i].getPortAndIpAddress()).second) == port )
// 				{
// 					final_matched_servers.push_back(matched_servers[i]);
// 				}
// 			}
// 			/***************[last: set server]***************/
// 			if (final_matched_servers.size())
// 				serv = final_matched_servers[0];

// 		}	/***************[domain_name case]***************/
// 		else if (!domain_name.empty())
// 		{
// 			/***************[first : match by port]***************/
// 			for (std::vector<ft::server>::size_type i = 0; i < virtual_servers.size(); i++)
// 			{
// 				if ( !((virtual_servers[i].getPortAndIpAddress()).second).empty() 
// 					&& ((virtual_servers[i].getPortAndIpAddress()).second) == port )
// 				{
// 					matched_servers.push_back(virtual_servers[i]);
// 				}
// 			}	
// 			/***************[second : match by server_name]***************/		
// 			for (std::vector<ft::server>::size_type i = 0; i < matched_servers.size(); i++)
// 			{
// 				for (std::vector<std::string>::size_type y = 0; i < matched_servers[i].get_server_name_directive().size(); y++)
// 				{
// 					if ((matched_servers[i].get_server_name_directive())[y] == domain_name)
// 					{
// 						final_matched_servers.push_back(matched_servers[i]);
// 						break;
// 					}
// 				}
// 			}
// 			/***************[last: set server]***************/
// 			if (final_matched_servers.size())
// 				serv = final_matched_servers[0];
// 			else if (matched_servers.size())
// 				serv = matched_servers[0];

// 		}

// 	}
	
// }


void	Request::setRequestLine(std::string line)
{
	
	std::vector<std::string> tokens;
	std::string              attributes[3] = {"method", "target", "http_version"};
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

void  Request::setHeaderLine(std::string line)
{
	std::vector<std::string> tokens;
	std::vector<std::string> val;

	tokens = get_tokens(line, " ");

  //throw_Errors_here
	if (tokens.size() < 2)
	{
		errorCode = 400;
		return;		
	}
		

	for (std::vector<std::string>::size_type i = 1; i < tokens.size(); i++)
		val.push_back(tokens[i]);

	setHeaderFields(std::make_pair(tokens[0], val));
	
}

std::string		Request::generate_file_name()
{	
	// int r = 0;

	// srand((int) time(0));
	// r = rand();
	return ("name.txt" );
}

// void Request::parse(std::string s)
// {
// 	std::vector<std::string> parts;
// 	std::vector<std::string> lines;
// 	std::string				fileName;
// 	std::ofstream 			body_file;
	

// 	if (flag == 0)
// 	{
// 		s.push_back('\r');
// 		s.push_back('\n');
// 		parts = get_tokens(s, "\r\n\r\n");

// 		if (parts.size())
// 		{
// 			flag++;
// 			parts[0].push_back('\r');
// 			parts[0].push_back('\n');
// 			lines = get_tokens(parts[0], "\r\n");
// 			if (lines.size())
// 			{
// 				setRequestLine(lines[0]);
// 				for(std::vector<std::string>::size_type i = 1; i < lines.size(); i++)
// 					setHeaderLine(lines[i]);
// 			}
			
// 		}

// 		if (method == "POST" && header_fields.find("Content-Length:") == header_fields.end() && header_fields.find("Transfer-Encoding:") == header_fields.end())
// 			throw(std::invalid_argument("400 Bad Request"));
// 		if (header_fields.find("Content-Length:") == header_fields.end() && header_fields.find("Transfer-Encoding:") == header_fields.end())
// 			return ;
// 		if(header_fields.find("Content-Length:") != header_fields.end() && parts.size() == 2)
// 		{
// 			fileName = generate_file_name();
// 			// std::ofstream 			body_file(fileName, std::ofstream::app);
// 			body_file.open(fileName, std::fstream::out | std::fstream::app);
			
// 			body_file << parts[1];
// 			body_file.close();

// 			// if (header_fields.find("Content-Length:")->second.size())
// 			// fileData = std::make_pair(fileName,header_fields.find("Content-Length:")->second[0] ); // error_heeere
// 		}
// 		if (header_fields.find("Transfer-Encoding:") != header_fields.end() && header_fields.find("Transfer-Encoding:")->second.size() != 1 && header_fields.find("Transfer-Encoding:")->second[0] != "chunked")
// 		{
// 			//throw exception!!!!!!!!
// 		}
// 		if(header_fields.find("Transfer-Encoding:") != header_fields.end() && parts.size() == 2)
// 		{	
// 			parts[1].push_back('\r');
// 			parts[1].push_back('\n');
// 			lines = get_tokens(parts[1], "\r\n");
// 			fileName = generate_file_name();
// 			body_file.open(fileName, std::fstream::out | std::fstream::app);

// 			// if (lines.size())
// 			// 	set_file_size(lines[0]);
			
			
// 			for (std::vector<std::string>::size_type i = 1; i < lines.size(); i++)
// 				body_file << lines[i] << "\r\n";
// 			body_file.close();


// 		}
// 	}
// 	if (flag > 0)
// 	{
// 		std::vector<std::string>::size_type i1 = 0;

// 		if (header_fields.find("Transfer-Encoding:") != header_fields.end())
// 		{
// 			lines = get_tokens(s, "\r\n");
// 			// if (lines.size())
// 			// 	set_file_size(lines[0]);
// 			i1 = 1;
// 		}

	
// 		body_file.open(fileName, std::fstream::out | std::fstream::app);
// 		for (std::vector<std::string>::size_type i = i1; i < lines.size(); i++)
// 			body_file << lines[i] << "\r\n";
// 		body_file.close();
// 	}

// }

void	Request::serverMatching(int socket, std::map<int, std::vector<ft::server> > socket_servers)
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
		bool 		matched  = false;

		if (header_fields.find("Host:")->second.size())
			hostValue = header_fields.find("Host:")->second[0] + ":";
		std::vector<std::string> tokens = get_tokens(hostValue, ":");
		std::map<int, std::vector<ft::server> >::iterator It = socket_servers.find(socket);

		if (tokens.size())
			toMatch = tokens[0];

		if (It != socket_servers.end())
		{
			for (std::vector<ft::server>::size_type	i = 0; i < (It->second).size(); i++)
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

bool		Request::find_line(std::string s, size_t current_pos)
{
	size_t i = 0;

	if ((i = s.find("\r\n", current_pos)) != std::string::npos)
	{
		index = i;
		return (true);
	}
	return (false);
}



void	Request::checkRequestErrors()
{
	if (method == "POST" && header_fields.find("Content-Length:") == header_fields.end()
		&& header_fields.find("Transfer-Encoding:") == header_fields.end())
	{
		errorCode = 400;
		return;		
		
	}

	if ( (header_fields.find("Transfer-Encoding:") != header_fields.end()
	&& header_fields.find("Transfer-Encoding:")->second.size() > 1 )|| 
	(header_fields.find("Transfer-Encoding:") != header_fields.end()
	&& header_fields.find("Transfer-Encoding:")->second.size()
	&& header_fields.find("Transfer-Encoding:")->second[0] != "chunked" ))
	{
		errorCode = 501;
		return;		
		
	}
}

void	Request::checkUriErrors()
{
	std::string	uri = target;
	std::string	allowedUriContent("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-.~:/?#[]@!$&'()+,;=%");

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

int		Request::hexToDecHelper(char c)
{
	std::string	str1("0123456789abcdef");
	std::string	str2("0123456789ABCDEF");

	for (std::string::size_type i = 0; i < str1.size(); i++)
	{
		if (c == str1[i])
			return (i + 1);
	}

	for (std::string::size_type i = 0; i < str2.size(); i++)
	{
		if (c == str2[i])
			return (i + 1);
	}
	return (0);
}

size_t	Request::hexToDec(std::string s)
{
	size_t	len = 0;
	size_t	j = 0;
	int	i = s.size(); //edited this

	if (i)
		i--;
	while (i >= 0)
	{
		len += hexToDecHelper(s[i]) * pow(16.00, j);
		j++;
		i--;
	}
	return (len);
}

void	Request::CheckBodyMaxSize()
{
	size_t maxSizeAllowed = std::atoi(serv.get_max_body_size_directive().c_str());
	if (body_length > maxSizeAllowed)
	{
		errorCode = 413;
		return;		
	}
		
}

void	Request::transferEncodingChunked()
{
	if (chunk_size_line)
	{
		current_length = 0;
		std::string line = request_data.substr(current_pos, index - current_pos) + ";";
		std::vector<std::string> tokens = get_tokens(line, ";");
		if (tokens.size())
		{
			chunk_size = hexToDec(tokens[0]);
		}
		if (chunk_size == 0)
		{
			body_section = false;
			request_end = true;
		}	
		chunk_size_line = false;
		current_pos = index + 2;                
	}
	else
	{
		requestBody.append(request_data.substr(current_pos, index - current_pos));
		current_length += request_data.substr(current_pos, index - current_pos).size();
		current_pos = index + 2;
		if (current_length == chunk_size)
		{
			chunk_size_line = true;       
			body_length += current_length;
			CheckBodyMaxSize();
			if (errorCase())
				return ;
		}         
	}
}

void	Request::CheckBody()
{
	if (header_fields.find("Content-Length:") == header_fields.end()
		&& header_fields.find("Transfer-Encoding:") == header_fields.end())
	{
		
		request_end = true;
		body_section = false;
	}
	else
		body_section = true;
}

void	Request::ContentLengthCase()
{
	requestBody.append(request_data.substr(current_pos, index - current_pos));
	body_length += request_data.substr(current_pos, index - current_pos).size();
	CheckBodyMaxSize();
	if (errorCase())
		return ;
	current_pos = index + 2;
	if (header_fields.find("Content-Length:")->second.size()
	&& body_length == (unsigned long)(std::atoi(header_fields.find("Content-Length:")->second[0].c_str())) )
	{
		body_section = false;  	
		request_end = true;
	}
}

bool 			Request::parse(int socket, std::string s, std::map<int, std::vector<ft::server> > m)
{
	request_data.append(s);
	errorCode = 0;
    while (find_line(request_data, current_pos) && !request_end)
    {
		std::cout << "\nHEEEEEERE" << std::endl;
        if (start_line_section)
        {
			setRequestLine(request_data.substr(current_pos, index - current_pos));
			if (errorCase())
				return (true);
			start_line_section = false;
			headers_section = true;
			current_pos = index + 2; 
			checkUriErrors();
			if (errorCase())
				return (true);
        }
        if (headers_section)
        {
			
			
 			if (current_pos == index)
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
				setHeaderLine(request_data.substr(current_pos, index - current_pos));
				if (errorCase())
					return (true);
			}

			current_pos = index + 2;           
        }
        if (body_section)
        {
			if (header_fields.find("Transfer-Encoding:") != header_fields.end())
			{
				transferEncodingChunked();
				if (errorCase())
					return (true);
			}
			else if (header_fields.find("Content-Length:") != header_fields.end())
			{
				ContentLengthCase();
				if (errorCase())
					return (true);
			}

        }
    }
	return (request_end);

}

void	Request::locationMatching()
{
	std::string					uri = target;				
	size_t						pos = 0;

	for (size_t i = 0; i < serv.get_location().size(); i++)
	{
	
		if (serv.get_location()[i].get_dir() == target )
		{
			loc = serv.get_location()[i];
			return ;
		}
	}

			// //std::cout << "\033[1;36mEEEEEEE: \033[0m" << uri << std::endl;
	while ((pos = uri.rfind("/", pos)) != std::string::npos )
	{
		uri = uri.substr(0, pos);
		if (uri.empty())
		{
			errorCode = 404;
			return;			
			
		}
		for (size_t i = 0; i < serv.get_location().size(); i++)
		{
			if (serv.get_location()[i].get_dir() == uri )
			{
				loc = serv.get_location()[i];
				
				return ;
			}
		}	
		pos = 0;	
	}
	
}

void	Request::setRequestEnd(bool x)
{
	request_end = x;
}

bool	Request::errorCase()
{
	if (errorCode != 0)
	{
		request_end = true;
		return (true);
	}
	return (false);
}

Request::~Request() {}