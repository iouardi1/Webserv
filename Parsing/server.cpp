#include "server.hpp"

ft::server::server() : listen_directive(std::string()), server_name_directive(std::vector<std::string>()), max_body_size_directive(std::string()),
 root_directive(std::string()), error_pages_directive(std::vector<std::vector<std::string> >()), index_directive(std::vector<std::string>()){}

ft::server::server(ft::server const& other)
{
	location_blocks = other.get_location();
	listen_directive = other.get_listen_directive();
	server_name_directive = other.get_server_name_directive();
	max_body_size_directive = other.get_max_body_size_directive();
	root_directive = other.get_root_directive();
	error_pages_directive = other.get_error_pages_directive();
	index_directive = other.get_index_directive();
}

ft::server&	ft::server::operator=(ft::server const& other)
{
	location_blocks = other.get_location();
	listen_directive = other.get_listen_directive();
	server_name_directive = other.get_server_name_directive();
	max_body_size_directive = other.get_max_body_size_directive();
	root_directive = other.get_root_directive();
	error_pages_directive = other.get_error_pages_directive();
	index_directive = other.get_index_directive();

	return (*this);	
}


/*************************[Geters]******************************/

std::vector<ft::location> ft::server::get_location() const
{
	return (location_blocks);
}

std::string ft::server::get_listen_directive() const
{
	return (listen_directive);
}

std::vector<std::string> ft::server::get_server_name_directive() const
{
	return (server_name_directive);
}

std::vector<std::string>    ft::server::get_tokens(std::string line, std::string delimiter)
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

std::pair<std::string, std::string>	ft::server::getPortAndIpAddress() 
{
	std::vector<std::string> tokens;

	if (listen_directive.empty())
		listen_directive = "80";
	// std::cout << "THE LISTEN: " << listen_directive << std::endl;
	tokens = get_tokens(listen_directive + ":", ":");
	if (tokens.size() == 1)
		return (std::make_pair("", tokens[0]));
	else if (tokens.size() == 2)
		return (std::make_pair(tokens[0], tokens[1]));
	else
		return (std::make_pair("", ""));
}

std::string ft::server::get_max_body_size_directive() const
{
	return (max_body_size_directive);
}

std::string ft::server::get_root_directive() const
{
	return (root_directive);
}

std::vector<std::vector<std::string> >	ft::server::get_error_pages_directive() const
{
	return (error_pages_directive);
}

std::vector<std::string> ft::server::get_index_directive() const
{
	return (index_directive);
}

/*************************[Seters]******************************/

void	ft::server::set_location_blocks(ft::location x) 
{
	x.checkLocationValidity();
	location_blocks.push_back(x);
}


void	ft::server::set_listen_directive(std::string  x) 
{
	listen_directive = x;
}

void	ft::server::set_server_name_directive(std::vector<std::string>  x) 
{
	server_name_directive = x;
}

void	ft::server::set_max_body_size_directive(std::string  x) 
{
	max_body_size_directive = x;
	checkMaxBodySizeValidity();
}

void	ft::server::set_root_directive(std::string  x) 
{
	root_directive = x;
}

void	ft::server::set_error_pages_directive(std::vector<std::string>  x) 
{
	error_pages_directive.push_back (x);
}

void	ft::server::set_index_directive(std::vector<std::string>  x) 
{
	index_directive = x;
}

void	ft::server::setter(std::string dir, std::string value, std::vector<std::string> v)
{
	
	std::string arr1[3] = {"listen", "root", "max_body_size"};
	std::string arr2[3] = {"server_name", "error_pages", "index"};
	void (ft::server::*f1[3])(std::string) = {&ft::server::set_listen_directive, &ft::server::set_root_directive, &ft::server::set_max_body_size_directive};
	void (ft::server::*f2[3])(std::vector<std::string>) = {&ft::server::set_server_name_directive, &ft::server::set_error_pages_directive, &ft::server::set_index_directive};

	for (int i = 0; i < 3; i++)
	{
		if (dir == arr1[i])
		{		
			(this->*f1[i])(value);
			return;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (dir == arr2[i])
		{
			(this->*f2[i])(v);
			return;
		}
	}
}

void	ft::server::checkMaxBodySizeValidity()
{
	std::string	validChars("0123456789");
	for (std::string::size_type i = 0; i < max_body_size_directive.size(); i++)
	{
		if (validChars.find(max_body_size_directive[i], 0) == std::string::npos)
			throw (std::invalid_argument("Server block: invalid max_body_size_directive"));
	}
}

void	ft::server::checkServerValidity()
{
	if (listen_directive.empty())
		throw(std::invalid_argument("Server block: listen_directive Not Found!"));
	if (root_directive.empty())
		throw(std::invalid_argument("Server block: root_directive Not Found!"));
	checkListenDirectiveValidity();
}

void	ft::server::checkListenDirectiveValidity()
{
	std::vector<std::string> 	tokens;
	std::string					s;

	if (listen_directive.find(":", 0)!= std::string::npos)
	{
		s = listen_directive + ":";
		tokens = get_tokens(s, ":");
		if (tokens.size() != 2)
			throw (std::invalid_argument("Server block: listen_directive : invalid value!"));
		checkListenIpPart(tokens[0]);
		checkListenPortPart(tokens[1]);	
	}
	else
		checkListenPortPart(listen_directive);
}

void	ft::server::checkListenIpPart(std::string s)
{
	std::vector<std::string> 	tokens;

	s.push_back('.');
	tokens = get_tokens(s, ".");
	if (tokens.size() != 4)
		throw (std::invalid_argument("Server block: listen_directive : invalid ip Address!"));
	for (size_t i = 0; i < 4; i++)
	{
		if ( !(tokens[i].size() >= 1 && tokens[i].size() <= 3 ) )
			throw (std::invalid_argument("Server block: listen_directive : invalid ip Address!"));

		for (size_t j = 0; j < tokens[i].size(); j++)
		{
			if ( !(tokens[i][j] >= '0' && tokens[i][j] <= '9') )
				throw (std::invalid_argument("Server block: listen_directive : invalid ip Address!"));
		}
		if ( !(std::atoi(tokens[i].c_str()) >= 0 && std::atoi(tokens[i].c_str()) <= 255 ))
			throw (std::invalid_argument("Server block: listen_directive : invalid ip Address!"));
	}
}

void	ft::server::checkListenPortPart(std::string s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		if ( !(s[i] >= '0' && s[i] <= '9') )
			throw (std::invalid_argument("Server block: listen_directive : invalid Port!"));
	}
}

ft::server::~server(){}