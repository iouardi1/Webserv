/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raniaidrissi <raniaidrissi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:16:44 by ridrissi          #+#    #+#             */
/*   Updated: 2023/03/06 01:16:25 by raniaidriss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include <stdlib.h> 


#include "http.hpp"


int main()
{
	try
	{
	
		http instance;
		std::string s("f.config");


		instance.parser(s);

		
		std::cout  << "\033[1;35m/**************************************[PRINT NUMBER OF VIRTUAL SERVERS]****************************************/\033[0m" << std::endl;
		
		std::cout << "\033[1;35m                                        NUMBER OF VIRTUAL SERVERS :\033[0m"<< (instance.getVirtualServers()).size()  << std::endl;

		// std::cout << "\033[1;35m/***************************************************************************************************************/\033[0m" << std::endl;

		std::cout << "\033[1;35m/***********************************[PRINT VIRTUAL SERVERS CONTENT]*********************************************/\033[0m" << std::endl;

		for ( std::vector<ft::server>::size_type n = 0; n <  (instance.getVirtualServers()).size(); n++)
		{
			std::cout << std::endl << "\033[1;33m/**************************[  \033[1;35mSERVER (" << n <<")  \033[1;33m]****************************/\033[0m" << std::endl << std::endl;
			std::cout << "\033[1;35m/**************************[\033[1;33merror_pages\033[1;35m]****************************/\033[0m" << std::endl;
			std::cout << "[size] : " <<  (instance.getVirtualServers())[n].get_error_pages_directive().size() << std::endl;
			std::cout << "[Content] : ";
			for (std::vector<std::string>::size_type i = 0; i < (instance.getVirtualServers())[n].get_error_pages_directive().size(); i++)
				std::cout << ((instance.getVirtualServers())[n].get_error_pages_directive())[i] << " ";
			
			std::cout << std::endl << "\033[1;35m/**************************[\033[1;33mindex\033[1;35m]****************************/\033[0m" << std::endl;
			std::cout << "[size] : " <<  (instance.getVirtualServers())[n].get_index_directive().size() << std::endl;
			std::cout << "[Content] : ";
			for (std::vector<std::string>::size_type i = 0; i < (instance.getVirtualServers())[n].get_index_directive().size(); i++)
				std::cout << ((instance.getVirtualServers())[n].get_index_directive())[i] << " ";	
			
			std::cout << std::endl << "\033[1;35m/**************************[\033[1;33mserver_name\033[1;35m]****************************/\033[0m" << std::endl;
			std::cout << "[size] : " << (instance.getVirtualServers())[n].get_server_name_directive().size() << std::endl;
			std::cout << "[Content] : ";
			for (std::vector<std::string>::size_type i = 0; i < (instance.getVirtualServers())[n].get_server_name_directive().size(); i++)
				std::cout << ((instance.getVirtualServers())[n].get_server_name_directive())[i] << " ";		


			std::cout << std::endl << "\033[1;35m/**************************[\033[1;33mroot\033[1;35m]****************************/\033[0m" << std::endl;
			if(! ((instance.getVirtualServers())[n].get_root_directive().empty()))
				std::cout << "[root] : " << (instance.getVirtualServers())[n].get_root_directive() << std::endl;


			std::cout << "\033[1;35m/**************************[\033[1;33mlisten\033[1;35m]****************************/\033[0m" << std::endl;
			if (! ((instance.getVirtualServers())[n].get_listen_directive().empty()))
				std::cout << "[listen] : " << (instance.getVirtualServers())[n].get_listen_directive() << std::endl;

			std::cout << "\033[1;35m/**************************[\033[1;33mmax_body_size\033[1;35m]****************************/\033[0m" << std::endl;	
			if (! ((instance.getVirtualServers())[n].get_max_body_size_directive().empty()))
				std::cout << "[max_body_size] : " << (instance.getVirtualServers())[n].get_max_body_size_directive() << std::endl;






			std::cout << "\033[1;35m/**************************[\033[1;33mlocation_blocks\033[1;35m]****************************/\033[0m" << std::endl;
			std::cout << "                          \033[1;33mNUMBER OF LOCATION BLOCKS : \033[0m" <<(instance.getVirtualServers())[n].get_location().size() << std::endl;
			
			
					for (std::vector<ft::location>::size_type y = 0; y <  (instance.getVirtualServers())[n].get_location().size() ; y++)
					{
						std::cout << std::endl << "\033[1;36m/**************************[  \033[1;34mlocation_block (" << y << ")  \033[1;36m]****************************/\033[0m"<< std::endl << std::endl;
							std::cout << "\033[1;34m/*************[\033[1;36mroot_location\033[1;34m]*******************/\033[0m" << std::endl;
						if(! (((instance.getVirtualServers())[n].get_location())[y].get_root().empty()))
							std::cout << "ROOT : " << ((instance.getVirtualServers())[n].get_location())[y].get_root() << std::endl;
							
							std::cout << "\033[1;34m/*************[\033[1;36mdir_location\033[1;34m]*******************/\033[0m" << std::endl;
						if(! (((instance.getVirtualServers())[n].get_location())[y].get_dir().empty()))
							std::cout << "DIR : " << ((instance.getVirtualServers())[n].get_location())[y].get_dir() << std::endl;
						
							std::cout << "\033[1;34m/*************[\033[1;36mreturn_location\033[1;34m]*******************/\033[0m" << std::endl;
					
						
							std::cout <<  "size: " <<  ((instance.getVirtualServers())[n].get_location())[y].get_return().size() << std::endl;
							std::cout << "Content: ";
						for (std::vector<std::string>::size_type i = 0; i < ((instance.getVirtualServers())[n].get_location())[y].get_return().size(); i++)
							std::cout << (((instance.getVirtualServers())[n].get_location())[y].get_return())[i] << " ";
							
							std::cout << std::endl << "\033[1;34m/*************[\033[1;36malias_location\033[1;34m]*******************/\033[0m" << std::endl;
						if(! (((instance.getVirtualServers())[n].get_location())[y].get_alias().empty()))
						std::cout << "ALIAS :" << ((instance.getVirtualServers())[n].get_location())[y].get_alias()<< std::endl;
							
							std::cout << "\033[1;34m/*************[\033[1;36mautoindex_location\033[1;34m]*******************/\033[0m" << std::endl;
						if(! (((instance.getVirtualServers())[n].get_location())[y].get_autoindex().empty()))
							std::cout << "AUTOINDEX: " << ((instance.getVirtualServers())[n].get_location())[y].get_autoindex() << std::endl;
							
							std::cout << std::endl << "\033[1;34m/*************[\033[1;36mindex_location\033[1;34m]*******************/\033[0m" << std::endl;
							std::cout <<  "size: " <<  ((instance.getVirtualServers())[n].get_location())[y].get_index().size() << std::endl;
							std::cout << "Content: ";
						for (std::vector<std::string>::size_type i = 0; i < ((instance.getVirtualServers())[n].get_location())[y].get_index().size(); i++)
							std::cout << (((instance.getVirtualServers())[n].get_location())[y].get_index())[i] << " ";	
										
							std::cout << std::endl << "\033[1;34m/*************[\033[1;36mlimitexcept_location\033[1;34m]*******************/\033[0m" << std::endl;
							std::cout <<  "size: " <<   ((instance.getVirtualServers())[n].get_location())[y].get_limitexcept().size() << std::endl;
							std::cout << "Content: ";
						for (std::vector<std::string>::size_type i = 0; i < ((instance.getVirtualServers())[n].get_location())[y].get_limitexcept().size(); i++)
							std::cout << (((instance.getVirtualServers())[n].get_location())[y].get_limitexcept())[i] << " ";				
						
					}
		}

	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	
	
}