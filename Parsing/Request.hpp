#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "server.hpp"
#include <cstdlib>
#include <map>
#include <math.h>
#include <sstream>
#include <time.h> 
#include <sys/stat.h>

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
		ft::location											loc;
		bool 													matchedServ;
		bool													request_end;
		size_t													body_length;
		int 													errorCode;
		std::string												_bodyFile;
		bool													chunkedBody;
		bool													unchunkedBody;
		bool													FirstSection;
		size_t 													i_index;
		
	
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
		ft::location										getLoc() const;
		bool												getMatchedServ() const;
		bool												getRequestEnd() const;
		size_t												getBodyLength() const;
		int 												getErrorCode() const;
		std::string											get_bodyFile() const;
		bool												getChunkedBody() const;
		bool												getUnchunkedBody() const;
		bool												getFirstSection() const;
		size_t												getI_index() const;
		
		


	/********************************************************/

		void	setLoc(ft::location x);
		void	setServer(ft::server s);
		void	setTarget(std::string x);
		void	setMethod(std::string x);
		void	setHttpVersion(std::string x);
		void	setHeaderFields(std::pair<std::string, std::vector<std::string> > value);
		void	setRequestEnd(bool x);
		void	setChunkedBody(bool x) ;
		void	setUnchunkedBody(bool x) ;

	/********************************************************/

		// std::vector<std::string>	get_tokens2(std::string line, std::string delimiter);
		// void 						parse2(std::string s);
		bool 						parse(int socket, std::string s, std::map<int, std::vector<ft::server> > m);
		void						setHeaderLine(std::string line);
		void						setRequestLine(std::string line);
		void						serverMatching(int socket, std::map<int, std::vector<ft::server> > 	socket_servers);
		std::string					generate_file_name();
		std::vector<std::string>	get_tokens(std::string line, std::string delimiter);
		bool						find_line(std::string s, size_t current_pos, std::string &line);
		void						checkRequestErrors();
		void						transferEncodingChunked(std::string s1);
		void						ContentLengthCase();
		void						CheckBody();
		size_t						hexToDec(std::string s);
		int							hexToDecHelper(char c);
		void						locationMatching();
		void						checkUriErrors();
		void						CheckBodyMaxSize();
		bool						errorCase();
		std::string					getBodyFileExtension();
		bool 						isResourceExist(std::string s);
		std::string					getStrToAdd();
		bool						isHexChar(char c);
		bool						isHexStr(std::string s);
		void 						transferEncodingChunked2();
		std::string					extractQuerieString();
		void						extractContentLen(size_t &len);
		void 						CheckBodyMaxSizee(size_t ln);

		



};

#endif