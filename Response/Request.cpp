#include "Request.hpp"


Request::Request() : serv(ft::server()), flag(0), fileData(std::pair<std::string, std::string>()), method(std::string()), target(std::string()), http_version(std::string()), header_fields(std::map<std::string, std::vector<std::string> >()){}

Request::Request(Request const& x)
{
	serv = ft::server();
	flag = x.getflag();
	fileData = x.getFileData();
	method = x.getMethod();
	target = x.getTarget();
	http_version = x.getHttpVersion();
	header_fields = x.getHeaderFields();
}

Request& Request::operator=(Request const& x)
{
	serv = x.getServer();
	flag = x.getflag();
	fileData = x.getFileData();
	method = x.getMethod();
	target = x.getTarget();
	http_version = x.getHttpVersion();
	header_fields = x.getHeaderFields();

	return (*this);
}

int	Request::getflag() const
{
	return (flag);
}

std::pair<std::string, std::string> 	Request::getFileData() const
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

// std::vector<std::string>    Request::get_tokens2(std::string line, std::string delimiter)
// {
//   size_t                      _start = 0;
//   size_t                      _end = 0;
// 	size_t                      _end2 = 0;
//   std::string                 token;
//   std::vector<std::string>    tokens;

//   if (delimiter == " ")
//     line.push_back(delimiter[0]);
//   while (((_end = line.find(delimiter, _start))!= std::string::npos) || (((_end2 = line.find("\r", _start))!= std::string::npos && std::cout << "okk ")) )
//   {
//     if (_end != std::string::npos)
//         _end2 = line.find("\t", _start);
//     else if (_end == std::string::npos )
//       _end = _end2;
//     if ( (_end != std::string::npos) && (_end2 != std::string::npos) &&  (_end > _end2) )
//       _end = _end2;
//     token = line.substr(_start, _end - _start);
//     _start = _end + 1;
//     if (!token.empty())
//       tokens.push_back(token);
//   }
//   return (tokens);
// }

void	Request::setRequestLine(std::string line)
{
  std::vector<std::string> tokens;
  std::string              attributes[3] = {"method", "target", "http_version"};
  void (Request::*f1[3])(std::string) = {&Request::setMethod, &Request::setTarget, &Request::setHttpVersion};

  tokens = get_tokens(line, " ");
  if (tokens.size() == 3)
  {
	for (std::vector<std::string>::size_type i = 0; i < tokens.size(); i++)
		(this->*f1[i])(tokens[i]);
  }
}

void  Request::setHeaderLine(std::string line)
{
  std::vector<std::string> tokens;
	std::vector<std::string> val;

  tokens = get_tokens(line, " ");

  //throw_Errors_here
  if (tokens.size() >= 2)
  {
	for (std::vector<std::string>::size_type i = 1; i < tokens.size(); i++)
		val.push_back(tokens[i]);
	std::cout << "tokens 0 :" << tokens[0] << " tokens 1:" << tokens.size() << std::endl;
    setHeaderFields(std::make_pair(tokens[0], val));
  }

}

std::string		Request::generate_file_name()
{	
	// int r = 0;

	// srand((int) time(0));
	// r = rand();
	return ("name.txt" );
}

void Request::parse(std::string s)
{
	std::vector<std::string> parts;
	std::vector<std::string> lines;
	std::string				fileName;
	std::ofstream 			body_file;
	

	if (flag == 0)
	{
		s.push_back('\r');
		s.push_back('\n');
		parts = get_tokens(s, "\r\n\r\n");

		if (parts.size())
		{
			flag++;
			parts[0].push_back('\r');
			parts[0].push_back('\n');
			lines = get_tokens(parts[0], "\r\n");
			if (lines.size())
			{
				setRequestLine(lines[0]);
				for(std::vector<std::string>::size_type i = 1; i < lines.size(); i++)
					setHeaderLine(lines[i]);
			}
			
		}

		if (method == "POST" && header_fields.find("Content-Length:") == header_fields.end() && header_fields.find("Transfer-Encoding:") == header_fields.end())
			throw(std::invalid_argument("400 Bad Request"));
		if (header_fields.find("Content-Length:") == header_fields.end() && header_fields.find("Transfer-Encoding:") == header_fields.end())
			return ;
		if(header_fields.find("Content-Length:") != header_fields.end() && parts.size() == 2)
		{
			fileName = generate_file_name();
			// std::ofstream 			body_file(fileName, std::ofstream::app);
			body_file.open(fileName, std::fstream::out | std::fstream::app);
			
			body_file << parts[1];
			body_file.close();

			if (header_fields.find("Content-Length:")->second.size())
			fileData = std::make_pair(fileName,header_fields.find("Content-Length:")->second[0] );
		}
		if (header_fields.find("Transfer-Encoding:") != header_fields.end() && header_fields.find("Transfer-Encoding:")->second.size() != 1 && header_fields.find("Transfer-Encoding:")->second[0] != "chunked")
		{
			//throw exception!!!!!!!!
		}
		if(header_fields.find("Transfer-Encoding:") != header_fields.end() && parts.size() == 2)
		{	
			parts[1].push_back('\r');
			parts[1].push_back('\n');
			lines = get_tokens(parts[1], "\r\n");
			fileName = generate_file_name();
			body_file.open(fileName, std::fstream::out | std::fstream::app);

			// if (lines.size())
			// 	set_file_size(lines[0]);
			
			
			for (std::vector<std::string>::size_type i = 1; i < lines.size(); i++)
				body_file << lines[i] << "\r\n";
			body_file.close();


		}
	}
	if (flag > 0)
	{
		std::vector<std::string>::size_type i1 = 0;

		if (header_fields.find("Transfer-Encoding:") != header_fields.end())
		{
			lines = get_tokens(s, "\r\n");
			// if (lines.size())
			// 	set_file_size(lines[0]);
			i1 = 1;
		}

	
		body_file.open(fileName, std::fstream::out | std::fstream::app);
		for (std::vector<std::string>::size_type i = i1; i < lines.size(); i++)
			body_file << lines[i] << "\r\n";
		body_file.close();
	}

}

void	Request::serverMatching(int socket, std::map<int, std::vector<ft::server> > socket_servers)
{

	if (header_fields.find("Host:") == header_fields.end())
		throw (std::invalid_argument("400 Bad Request"));
	
	std::string toMatch;
	bool 		matched  = false;

	std::string hostValue;
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
}

Request::~Request() {}