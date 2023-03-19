#ifndef HTTP_HPP
#define HTTP_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "server.hpp"
#include "location.hpp"
#include <fstream>
#include <map>

class http
{
	private:
		std::vector<ft::server>						virtual_servers;
		std::map<int, std::vector<ft::server> > 	socket_servers;
	public:
		http();
		http(http const& other);
		~http();
		http& 						operator=(http const& other);
		void 						parser(std::string config_file);
		std::vector<ft::server> 	getVirtualServers() const;
		std::vector<std::string>    get_tokens(std::string line, std::string delimiter);
		void    					error_generator(std::string const& error);		
		void    					set_server(std::string s, ft::server& serv, bool *location_block_open, bool *location_on, ft::location &loc,  bool *location_first_line);	
		void  						set_location(std::string s, ft::location& loc);
		void						setSocketServers(std::map<int, std::vector<ft::server> > x);
		void											check_servers_conflict() const;
		std::map<std::string, std::vector<ft::server> > get_ipPort_matched_servers() const;
		std::map<int, std::vector<ft::server> > 		getSocketServers() const;
		
		

};

#endif