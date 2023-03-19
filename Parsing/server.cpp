#include "server.hpp"

ft::server::server() : listen_directive(std::string()), server_name_directive(std::vector<std::string>()), max_body_size_directive(std::string()),
 root_directive(std::string()), error_pages_directive(std::vector<std::string>()), index_directive(std::vector<std::string>()){}

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

std::vector<std::string> ft::server::get_error_pages_directive() const
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
}

void	ft::server::set_root_directive(std::string  x) 
{
	root_directive = x;
}

void	ft::server::set_error_pages_directive(std::vector<std::string>  x) 
{
	error_pages_directive = x;
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

ft::server::~server(){}