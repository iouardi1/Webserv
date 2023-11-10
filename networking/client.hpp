/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:32:24 by iouardi           #+#    #+#             */
/*   Updated: 2023/04/01 00:29:43 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AED5C75D_038B_4348_9995_2FD3969B7DA0
#define AED5C75D_038B_4348_9995_2FD3969B7DA0

#include "../Parsing/http.hpp"
#include "../Parsing/server.hpp"
#include "../Parsing/Request.hpp"
#include "../Parsing/location.hpp"
#include <vector>


class   client
{
	private:
		int                         								socket_server;
		std::vector<std::pair<std::pair<int, bool>, Request> >		socket_responses;
		std::string 												resp_message;
		int															flag;
		std::map<int, size_t>										itr_map;
		std::string	buffer;

	public:
		client();
		~client();
		client(const client& copy);
		client(int sock);
		client(int sock_res, bool flag, Request req);
		client& operator=(const client& copy);


		//* setters
		void    set_socket_server(int socket_);
		void    set_socket_responses(int socket_, bool flag, Request client_request);
		void	set_sock_flag(bool flag, int index);
		bool	setRequestEnd_(bool x, int index);
		void	set_resp_message(std::string msg);
		void	setFlag(int flag);
		void 	set_itr_map(int);
		void	setBuffer(std::string b);
		// bool	parse_request(std::string s, std::map<int, std::vector<ft::server> > m);

	
		//* getters
		int                 									get_socket_server() const;
		std::vector<std::pair<std::pair<int, bool>, Request> >	get_socket_responses() const;
		bool													parse_request(std::string s, std::map<int, std::vector<ft::server> > m, int index);
		bool    												get_sock_flag(int index) const;
		std::string												get_resp_message() const;
		int														getFlag() const;
		std::map<int, size_t>										get_itr_map() const;
		std::string												getBuffer() const;


		//* utiles
		void    remove_sock(int index, int sock);
};


#endif
