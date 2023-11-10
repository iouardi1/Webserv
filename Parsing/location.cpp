#include "location.hpp"

ft::location::location() : dir_directive(std::string()), root_directive(std::string()), index_directive(std::vector<std::string>()), return_directive(std::vector<std::string>()),
alias_directive(std::string()), autoindex_directive(std::string()), limit_except_directive(std::vector<std::string>()), cgi_directive(std::string()) {}

ft::location::location(ft::location const& other)
{
	dir_directive = other.get_dir();
	root_directive = other.get_root();
	index_directive = other.get_index();
	return_directive = other.get_return();
	alias_directive = other.get_alias();
	autoindex_directive = other.get_autoindex();
	limit_except_directive = other.get_limitexcept();	
	cgi_directive = other.get_cgi();
}

std::string	ft::location::get_cgi() const
{
	return (cgi_directive);
}

void	ft::location::set_cgi(std::string x)
{
	cgi_directive = x;
}

ft::location& ft::location::operator=(ft::location const& other)
{	dir_directive = other.get_dir();
	root_directive = other.get_root();
	index_directive = other.get_index();
	return_directive = other.get_return();
	alias_directive = other.get_alias();
	autoindex_directive = other.get_autoindex();
	limit_except_directive = other.get_limitexcept();
	cgi_directive = other.get_cgi();	

	return (*this);
}

std::string ft::location::get_dir() const
{
	return (dir_directive);
}

std::string ft::location::get_root() const
{
	return (root_directive);
}

std::vector<std::string> ft::location::get_return() const
{
	return (return_directive);
}

std::string ft::location::get_alias() const
{
	return (alias_directive);
}

std::string ft::location::get_autoindex() const
{
	return (autoindex_directive);
}

std::vector<std::string> ft::location::get_index() const
{
	return (index_directive);
}

std::vector<std::string> ft::location::get_limitexcept() const
{
	return (limit_except_directive);
}

void	ft::location::set_dir(std::string x)
{
	dir_directive = x;
}

void	ft::location::set_root(std::string x)
{
	root_directive = x;
}

void	ft::location::set_index(std::vector<std::string> x)
{
	index_directive = x;
}

void	ft::location::set_return(std::vector<std::string> x)
{
	return_directive = x;
}

void	ft::location::set_alias(std::string x)
{
	alias_directive = x;
}

void	ft::location::set_autoindex(std::string	x)
{
	autoindex_directive = x;
}

void	ft::location::set_limitexcept(std::vector<std::string> x)
{
	limit_except_directive = x;
}

void	ft::location::setter(std::string dir, std::string value, std::vector<std::string> v)
{
	
	std::string arr1[4] = {"root", "alias", "autoindex", "CGI"};
	std::string arr2[3] = {"index", "limit_except", "return"};
	void (ft::location::*f1[4])(std::string) = {&ft::location::set_root, &ft::location::set_alias, &ft::location::set_autoindex, &ft::location::set_cgi};
	void (ft::location::*f2[3])(std::vector<std::string>) = {&ft::location::set_index, &ft::location::set_limitexcept,  &ft::location::set_return};

	for (int i = 0; i < 4; i++)
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

void	ft::location::checkLocationValidity()
{
	// std::cout << ": " << autoindex_directive << std::endl;
	if (!autoindex_directive.empty() && autoindex_directive != "on" && autoindex_directive != "off")
		throw(std::invalid_argument("Location block: Invalid autoindex_directive value!"));
}

ft::location::~location(){}