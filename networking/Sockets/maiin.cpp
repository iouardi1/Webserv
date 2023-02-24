/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maiin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 22:39:24 by iouardi           #+#    #+#             */
/*   Updated: 2023/02/24 22:50:32 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listeningSocket.hpp"

int main()
{
	std::cout << "Starting..." << std::endl;
	// std::cout << "Simple socket..." << std::endl;
	// HDE::mySocket ss = HDE::mySocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
	std::cout << "Binding Socket..." << std::endl;
	HDE::BindingSocket	bs = HDE::BindingSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
	std::cout << "listening Socket..." << std::endl;
	HDE::listeningSocket	ls = HDE::listeningSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
	std::cout << "Success!" << std::endl;
}