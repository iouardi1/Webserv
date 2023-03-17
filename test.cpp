/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:30:03 by het-tale          #+#    #+#             */
/*   Updated: 2023/03/07 09:30:45 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

int main() {
    // create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cout << "Error: Failed to create socket" << endl;
        return 1;
    }
    
    // server information
    string server_address = "localhost";
    int port = 8000;
    
    // create the socket address structure
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(server_address.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    
    // connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        cout << "Error: Failed to connect to server" << endl;
        return 1;
    }
    
    // create the POST request
    string message = "POST /path HTTP/1.1\r\n";
    message += "Host: localhost\r\n";
    message += "Content-Type: application/x-www-form-urlencoded\r\n";
    message += "Content-Length: 13\r\n\r\n";
    message += "data=example";
    
    // send the request
    if (send(sock, message.c_str(), strlen(message.c_str()), 0) < 0) {
        cout << "Error: Failed to send request" << endl;
        return 1;
    }
    
    // receive the response
    char response[4096];
    int size = recv(sock, response, 4096, 0);
    if (size < 0) {
        cout << "Error: Failed to receive response" << endl;
        return 1;
    }
    
    // print the response
    response[size] = '\0';
    cout << response << endl;
    
    // close the socket
    close(sock);
    
    return 0;
}