
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "server.hpp"
#include <map>

class Request
{
	private:

		size_t 													chunk_size;
		size_t													current_length;
		std::string												request_data;
		size_t													index;
		size_t													current_pos;
		bool													start_line_section;
		bool													headers_section;
		bool													body_section;
		ft::server												serv;	
		int														flag;
		std::pair<std::string, size_t> 							fileData;
		std::string												method;
		std::string												target;
		std::string												http_version;
		std::map<std::string, std::vector<std::string> >		header_fields;
		bool													chunk_size_line;
		std::string												requestBody;
	
	public:

	/********************************************************/	

		Request();
		Request(Request const& x);
		~Request();
		Request& operator=(Request const& x);

	/********************************************************/

		std::string											getRequestData() const;
		size_t												getIndex() const;
		size_t												getCurrentPos() const;
		bool												getStartLineSection() const;
		bool												getHeadersSection() const;
		bool												getBodySection() const;
		int													getflag() const;
		ft::server											getServer() const;
		std::string											getMethod() const;
		std::string											getTarget() const;
		std::string											getHttpVersion() const;
		std::map<std::string, std::vector<std::string> >	getHeaderFields() const;
		std::pair<std::string, size_t> 						getFileData() const;
		size_t												getChunkSize() const;
		size_t												getCurrentLength() const;
		bool 												getChunkSizeLine() const;
		std::string											getRequestBody() const;

	/********************************************************/

		void	setServer(ft::server s);
		void	setTarget(std::string x);
		void	setMethod(std::string x);
		void	setHttpVersion(std::string x);
		void	setHeaderFields(std::pair<std::string, std::vector<std::string> > value);

	/********************************************************/

		// std::vector<std::string>	get_tokens2(std::string line, std::string delimiter);
		void 						parse(std::string s);
		void 						parse2(std::string s);
		void						setHeaderLine(std::string line);
		void						setRequestLine(std::string line);
		void						serverMatching(int socket, std::map<int, std::vector<ft::server> > 	socket_servers);
		std::string					generate_file_name();
		std::vector<std::string>	get_tokens(std::string line, std::string delimiter);
		bool						find_line(std::string s, size_t current_pos);
		
		
		
		



};

#endif