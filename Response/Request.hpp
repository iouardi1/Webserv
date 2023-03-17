
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../Parsing/server.hpp"
# include <fstream>
#include <map>

class Request
{
	private:
		ft::server												serv;	
		int														flag;
		std::pair<std::string, std::string> 					fileData;
		std::string												method;
		std::string												target;
		std::string												http_version;
		std::map<std::string, std::vector<std::string> >		header_fields;//vector
	
	public:

	/********************************************************/	

		Request();
		Request(Request const& x);
		~Request();
		Request& operator=(Request const& x);

	/********************************************************/

		int													getflag() const;
		ft::server											getServer() const;
		std::string											getMethod() const;
		std::string											getTarget() const;
		std::string											getHttpVersion() const;
		std::map<std::string, std::vector<std::string> >	getHeaderFields() const;
		std::pair<std::string, std::string> 				getFileData() const;

	/********************************************************/

		void	setServer(ft::server s);
		void	setTarget(std::string x);
		void	setMethod(std::string x);
		void	setHttpVersion(std::string x);
		void	setHeaderFields(std::pair<std::string, std::vector<std::string> > value);

	/********************************************************/

		// std::vector<std::string>	get_tokens2(std::string line, std::string delimiter);
		void 						parse(std::string s);
		void						setHeaderLine(std::string line);
		void						setRequestLine(std::string line);
		void						serverMatching(int socket, std::map<int, std::vector<ft::server> > 	socket_servers);
		std::string					generate_file_name();
		std::vector<std::string>	get_tokens(std::string line, std::string delimiter);
		
		
		
		



};

#endif