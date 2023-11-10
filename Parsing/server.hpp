#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>

#include "location.hpp"

namespace ft{
	class server
	{
		private:
			std::vector<ft::location>					location_blocks;
			std::string									listen_directive;
			std::vector<std::string>					server_name_directive;
			std::string									max_body_size_directive;
			std::string 								root_directive;
			std::vector<std::vector<std::string> >		error_pages_directive;
			std::vector<std::string>					index_directive;

		public:
		server();
		server(server const& other);
		server& operator=(server const& other);
		~server();	

		std::string               					get_listen_directive() const;
		std::vector<std::string>  					get_server_name_directive() const;
		std::string               					get_max_body_size_directive() const;
		std::string               					get_root_directive() const;
		std::vector<std::vector<std::string> >  	get_error_pages_directive() const;
		std::vector<std::string>  					get_index_directive() const;
		std::vector<ft::location> 					get_location() const;


		void	set_location_blocks(ft::location  x) ;
		void	set_listen_directive(std::string  x);
		void	set_server_name_directive(std::vector<std::string>  x);
		void	set_max_body_size_directive(std::string);
		void	set_root_directive(std::string  x);
		void	set_error_pages_directive(std::vector<std::string>  x);
		void	set_index_directive(std::vector<std::string>  x);
		void	setter(std::string dir, std::string value, std::vector<std::string> v);


		
		std::vector<std::string>    			get_tokens(std::string line, std::string delimiter);
		std::pair<std::string, std::string>		getPortAndIpAddress() ;
		void									checkServerValidity();	
		void									checkMaxBodySizeValidity();
		void									checkListenDirectiveValidity();
		void									checkListenIpPart(std::string s);
		void									checkListenPortPart(std::string s);
	};
}
#endif