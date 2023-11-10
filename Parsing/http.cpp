#include "http.hpp"
#include <stdexcept>


http::http() : virtual_servers(std::vector<ft::server>()), socket_servers(std::map<int, std::vector<ft::server> >()) {}

http::http(http const& other)
{
	virtual_servers = other.getVirtualServers();
    socket_servers = other.getSocketServers();
}

std::map<int, std::vector<ft::server> > http::getSocketServers() const
{
    return (socket_servers);
}

std::vector<ft::server> http::getVirtualServers() const
{
	return (virtual_servers);
}

http& http::operator=(http const& other)
{
	virtual_servers = other.getVirtualServers();
    socket_servers = other.getSocketServers();

	return (*this);
}

void	http::setSocketServers(std::map<int, std::vector<ft::server> > x)
{
    socket_servers = x;
}

void    http::set_location(std::string s, ft::location& loc)
{
    std::vector<std::string>    tokens;
	std::string arr[4] = {"root", "alias", "autoindex", "CGI"};
	std::string arr2[3] = {"index", "limit_except", "return"};

    tokens = get_tokens(s, " ");

    if (tokens.size())
    {
        for(int i = 0; i < 4; i++)
        {
            if (tokens[0] == arr[i])
            {
                
                if (tokens.size() != 2)
                    throw (std::invalid_argument("Location block: directive expects only 1 value but found more!"));
                loc.setter(tokens[0], tokens[1], std::vector<std::string>());
                return;
            }
        }

        for(int i = 0; i < 3; i++)
        {
            if (tokens[0] == arr2[i])
            {
                std::vector<std::string> vec;
                if (tokens[0] != "return" && tokens.size() < 2)
                    throw (std::invalid_argument("Location block: directive expects 1 value at least but found less!"));
				else if (tokens[0] == "return" && tokens.size() != 3)
					throw (std::invalid_argument("Location block: return directive expects 2 values but found less/more!"));
                for (std::vector<std::string>::size_type i = 1; i < tokens.size(); i++)
                    vec.push_back(tokens[i]);
                loc.setter(tokens[0], std::string(), vec);
                return;
            }
        }

        throw(std::invalid_argument("Location block: Unvalid directive!"));
    }
}

void    http::set_server(std::string s, ft::server& serv,  bool *location_block_open, bool *location_on, ft::location &loc, bool *location_first_line )
{
    std::vector<std::string>    tokens;
    
    std::string                 arr[3] = {"listen", "root", "max_body_size"};
    std::string                 arr2[4] = {"server_name", "error_pages", "index"};

    
    size_t                      opening_pos = 0;
	size_t                      closing_pos = 0;
    
	std::string					s1;
	std::string					s2;
	std::string					s3;

    tokens = get_tokens(s, " ");

    if (tokens.size())
    {
        if (*location_block_open == false && *location_on == false)
        {
                
            for(int i = 0; i < 3; i++)
            {
                if (tokens[0] == arr[i])
                {
                    if (tokens.size() != 2)
                        throw (std::invalid_argument("Server block: directive root/listen expect only 1 value but found more!"));
                    serv.setter(tokens[0], tokens[1], std::vector<std::string>());
                    return;
                }
            }

            for(int i = 0; i < 4; i++)
            {
                if (tokens[0] == arr2[i])
                {
                    std::vector<std::string> vec;
                    if (tokens.size() < 2)
                        throw (std::invalid_argument("Server block: directives expecting 1 value at least but found less!"));
                
                    for (std::vector<std::string>::size_type i = 1; i < tokens.size(); i++)
                        vec.push_back(tokens[i]);
                    serv.setter(tokens[0], std::string(), vec);
                    return;
                }
            }
        }

        if (*location_on || (*location_block_open) || (tokens[0] == "location" && !(*location_block_open)))
        {
            *location_on = true; 
                    
                if (!(*location_block_open)  && ((opening_pos = s.find("{", 0)) != std::string::npos) )
                {
					
                    *location_on = false;
					if (*location_first_line)
                    	loc = ft::location();

					

                    (*location_block_open) = true;
                    s1 = s.substr(0, opening_pos);
                    s2 = s.substr(opening_pos + 1, s.size()  - opening_pos);
                    /******[handle the first substr]******/
                    tokens = get_tokens(s1, " ");

				
                    if (*location_first_line && tokens.size() != 2)
                    {
						throw (std::invalid_argument("Location block: Errors in number of args!"));
 
                    }
                    else if (!(*location_first_line) && tokens.size() != 0)
                    {
						throw (std::invalid_argument("Location block: location doesn't expect any arguments but found N args!"));			
                    }

					if (*location_first_line)
                   		loc.set_dir(tokens[1]);
					
                    s = s2;   
                    
                }

				if (!(*location_block_open)  && ((opening_pos = s.find("{", 0)) == std::string::npos) && *location_first_line)
				{
					tokens = get_tokens(s, " ");
					if (tokens.size() != 2)
					{
						throw (std::invalid_argument("[Location block]: Errors in number of args!"));
					}
					loc = ft::location();
					loc.set_dir(tokens[1]);

					
				}
            	*location_first_line = false;
                
                if (s.size() && (*location_block_open))
                {
                    if (((closing_pos = s.find("}", 0)) != std::string::npos) )
                    {
                        (*location_block_open) =  false;
                        s1 = s.substr(0, closing_pos);
                        s3 = s.substr(closing_pos + 1, s.size()  - closing_pos);
                        if (s3.size() != 0)
                        {
							throw (std::invalid_argument("Server block: Syntax Error!"));
                        						
                        }
                        set_location(s1, loc);
                        loc.checkLocationValidity();
                        serv.set_location_blocks(loc)/*.push_back(loc)*/;
						
                        // std::cout << "setting loc: " <<  serv.get_location().size()<<std::endl;

						*location_first_line = true;
						*location_block_open = false;
						*location_on = false;
                        
                        return;

                    }
                    else
                    {
                        set_location(s, loc);
                        return;
                    }
                }
        }
        else
        {
            throw(std::invalid_argument("Server block: Unvalid directive!"));
        }
    }
}

std::vector<std::string>    http::get_tokens(std::string line, std::string delimiter)
{
    size_t                      _start = 0;
    size_t                      _end = 0;
	size_t                      _end2 = 0;
	// size_t                      temp_end = 0;
    std::string                 token;
    std::vector<std::string>    tokens;

   	line.push_back(delimiter[0]);
	
   while (    ((_end = line.find(delimiter, _start))!= std::string::npos) || (((_end2 = line.find("\t", _start))!= std::string::npos && std::cout << "okk ")) )// rania mahada??
    {
		
        if (_end != std::string::npos)
            _end2 = line.find("\t", _start);
        else if (_end == std::string::npos )
            _end = _end2;

		
		if ( (_end != std::string::npos) && (_end2 != std::string::npos) &&  (_end > _end2) )
			_end = _end2;
        token = line.substr(_start, _end - _start);
		// erase_tab(token);
        _start = _end + 1;
		if (!token.empty())
        	tokens.push_back(token);
    }

    return (tokens);
}

void    http::error_generator(std::string const& error)
{
    std::cout << error << std::endl;
}

void http::parser(std::string config_file)
{
    ft::server     				serv;
    ft::location                loc;
    std::ifstream               fileToRead(config_file.c_str()); //edited this
    std::string                 line;
    std::vector<std::string>    tokens;

	/***[look for block opening in server token line]***/
	size_t                      opening_pos = 0;
	size_t                      closing_pos = 0;
	std::string					s1;
	std::string					s2;
	std::string					s3;
	bool						server_first_line = true;
	bool						location_first_line = true;
    bool						server_on = false;
	bool						server_block_open = false;
	bool						location_block_open = false;
    bool						location_on = false;


	while (std::getline(fileToRead, line))
	{
		
		tokens = get_tokens(line, " ");
		if ((tokens.size() && tokens[0] == "server" && !server_block_open) || server_block_open || server_on)
		{
			
			server_on = true;
			if (!server_block_open  && ((opening_pos = line.find("{", 0)) != std::string::npos) )
			{
				server_on = false;
				serv = ft::server();

				server_block_open = true;
				s1 = line.substr(0, opening_pos);
				s2 = line.substr(opening_pos + 1, line.size()  - opening_pos);
				/******[handle the first substr]******/
				tokens = get_tokens(s1, " ");
				if (server_first_line && tokens.size() != 1)
				{
					throw(std::invalid_argument("Server block: 1.server doesn't expect any arguments but found N args!"));
				}
				else if (!server_first_line && tokens.size() != 0)
				{
					throw(std::invalid_argument("Server block: 2.server doesn't expect any arguments but found N args!"));			
				}

				line = s2;   
				
			}
			 
			if (!server_block_open  && ((opening_pos = line.find("{", 0)) == std::string::npos) && server_first_line)
			{
				tokens = get_tokens(line, " ");
                if (tokens.size() != 1)
                {
					throw(std::invalid_argument("Server block: 3.server doesn't expect any arguments but found N args!"));

                }

			}
			server_first_line = false;
			
			if (line.size() && server_block_open)
			{
				if (!location_block_open && ((closing_pos = line.find("}", 0)) != std::string::npos) )
				{
					server_block_open =  false;
					s1 = line.substr(0, closing_pos);
					s3 = line.substr(closing_pos + 1, line.size()  - closing_pos);
					if (s3.size() != 0 )
					{
						throw(std::invalid_argument("Http block: Syntax Error!"));						
					}
					set_server(s1, serv, &location_block_open, &location_on, loc, &location_first_line);
                    serv.checkServerValidity();
					virtual_servers.push_back(serv);

					server_first_line = true;
					server_on = false;
					server_block_open = false;

				}
				else
				{
					set_server(line, serv, &location_block_open, &location_on, loc, &location_first_line);
				}
			}
		}
		else if (tokens.size() && tokens[0] != "server")
		{
			throw(std::invalid_argument("Http block: unexpected directive!"));

		}
	}
	if (server_block_open)
		throw(std::invalid_argument("Server block: \"}\" not found!"));
		
            
 
	fileToRead.close();
}

void	http::check_servers_conflict() const
{
	std::map<std::string, int> different_servers;

	for (std::vector<ft::server>::size_type i = 0; i < virtual_servers.size(); i++)
	{
		std::string					key;
		key +=  virtual_servers[i].get_listen_directive();
		for (std::vector<std::string>::size_type y = 0; y < virtual_servers[i].get_server_name_directive().size(); y++)
			key += virtual_servers[i].get_server_name_directive()[y];
		
		different_servers.insert(std::make_pair(key, i));
	}

	if (different_servers.size() != virtual_servers.size())
		throw (std::invalid_argument("Servers Conflict!"));
}

std::map<std::string, std::vector<ft::server> > http::get_ipPort_matched_servers() const
{
	std::map<std::string, std::vector<ft::server> > unique_ipPort;

	for (std::vector<ft::server>::size_type i = 0; i < virtual_servers.size(); i++)
	{
		if (unique_ipPort.find(virtual_servers[i].get_listen_directive()) != unique_ipPort.end())
			(unique_ipPort.find(virtual_servers[i].get_listen_directive()))->second.push_back(virtual_servers[i]);

		unique_ipPort.insert(std::make_pair(virtual_servers[i].get_listen_directive(), std::vector<ft::server>(1, virtual_servers[i]) ));
	}

	return (unique_ipPort);
}

http::~http(){}