#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace ft
{
	class location
	{
		private:
			std::string						dir_directive;
			std::string 					root_directive;
			std::vector<std::string>		index_directive;
			std::vector<std::string>		return_directive;
			std::string						alias_directive;
			std::string						autoindex_directive;
			std::vector<std::string>		limit_except_directive;
			std::string						cgi_directive;

		public:
		location();
		location(location const& other);
		location& operator=(location const& other);
		~location();

		std::string	get_cgi() const;
		std::string get_dir() const;
		std::string get_root() const;
		std::string get_alias() const;
		std::string get_autoindex() const;
		std::vector<std::string> get_index() const;
		std::vector<std::string> get_limitexcept() const;
		std::vector<std::string> get_return() const;


		void	set_cgi(std::string x);
		void	set_dir(std::string x);
		void	set_root(std::string x);
		void	set_index(std::vector<std::string> x);
		void	set_return(std::vector<std::string> x);
		void	set_alias(std::string x);
		void	set_autoindex(std::string	 x);
		void	set_limitexcept(std::vector<std::string> x);
		void	setter(std::string dir, std::string value, std::vector<std::string> v);
		void	checkLocationValidity();

	};
}

#endif