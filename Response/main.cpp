/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:24:04 by het-tale          #+#    #+#             */
/*   Updated: 2023/03/19 15:15:29 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../OldStuff/HttpResponse.hpp"
#include <dirent.h>
#include <sstream>
#include <string>
#include<cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

std::string	generateErrorPages(int code)
{
	std::string buffer;
	std::stringstream ss;
	ss << code;
	std::map<int, std::string> http_codes;

	http_codes.insert(std::make_pair(200, "OK"));
	http_codes.insert(std::make_pair(201, "Created"));
	http_codes.insert(std::make_pair(204, "No Content"));
	http_codes.insert(std::make_pair(301, "Moved Permanently"));
	http_codes.insert(std::make_pair(302, "Found"));
	http_codes.insert(std::make_pair(304, "Not Modified"));
	http_codes.insert(std::make_pair(400, "Bad Request"));
	http_codes.insert(std::make_pair(401, "Unauthorized"));
	http_codes.insert(std::make_pair(403, "Forbidden"));
	http_codes.insert(std::make_pair(404, "Not Found"));
	http_codes.insert(std::make_pair(500, "Internal Server Error"));
	http_codes.insert(std::make_pair(501, "Not Implemented"));
	http_codes.insert(std::make_pair(401, "Unauthorized"));
	http_codes.insert(std::make_pair(503, "Service Unavailable"));

	buffer = "<!DOCTYPE html><html lang='en'><head><title>";
	buffer.append(ss.str());
	buffer.append(" ");
	buffer.append(http_codes[code]);
	buffer.append("</title></head><body><center><h1>");
	buffer.append(ss.str());
	buffer.append(" ");
	buffer.append(http_codes[code]);
	buffer.append("</h1></center><hr><center>webserv/x.x</center></body></html>");
	return buffer;
}

std::string	generatRandomFileName(std::string file)
{
	srand(time(0));
	std::string randName;
	static int	i = 0;

	randName = file.append("_").append(std::to_string(i));
	i++;
	return randName;
}

void deleteFolderContent(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                std::string subPath = std::string(path) + "/" + std::string(entry->d_name);
                if (entry->d_type == DT_DIR) {
                    deleteFolderContent(subPath.c_str());
                    rmdir(subPath.c_str());
                } else {
                    if (remove(subPath.c_str()) == -1)
						//std::cout << "fail\n";
                }
            }
        }
        closedir(dir);
    }
}

int main()
{
	// std::string name = "hasnaaC";
	// std::string::reverse_iterator it = name.rbegin();
	// if (*it == 'B')
	// 	//std::cout << *it << std::endl;
	// else
	// 	//std::cout << "hello" << std::endl;

	// std::string root_dir = "./";  // Root directory path
    // std::string filename = "includess";  // Name of the file to search for
    
    // DIR* dir = opendir(root_dir.c_str());
    // if (dir) {
    //     struct dirent* entry;
    //     while ((entry = readdir(dir)) != NULL) {
    //         std::string entry_name(entry->d_name);
    //         if (entry_name == filename) {
    //             //std::cout << "File found in root directory.\n";
    //             closedir(dir);
    //             return 0;
    //         }
    //     }
    //     closedir(dir);
    // }
    
    // //std::cout << "File not found in root directory.\n";
    // return 1;


	// std::string fileName("includes/test.hpp");
	// struct stat fileInfo;
	// if (stat(fileName.c_str(), &fileInfo) == 0)
	// {
	// 	if (S_ISDIR(fileInfo.st_mode))
	// 		 //std::cout << "File found in root directory. and is a directory\n";
	// 	else
	// 		//std::cout << "bla bla\n";
	// }
	// else
	// 	//std::cout << "File not found in root directory.\n";


	// std::ifstream file("server.c");  // Open file for reading
    // std::string line;
    
    // if (file.is_open()) {
    //     while (getline(file, line)) {
    //         //std::cout << line << std::endl;  // Print each line
    //     }
    //     file.close();  // Close file when done
    // }
    // else {
    //     //std::cout << "Unable to open file." << std::endl;
    //     return 1;
    // }
    
    // return 0;


	// std::string buffer;
	
	// std::ifstream file("server.c");  // Open file for reading
    // std::string line;
    
	// //std::cout << "Before \n";
	// //std::cout << buffer;
	
    // if (file.is_open())
	// {
    //     while (getline(file, line))
	// 	{
	// 		buffer.append(line);
	// 		buffer.append("\n");
    //     }
    //     file.close();  // Close file when done
    // }

	// //std::cout << "After \n";
	// //std::cout << buffer;


	// DIR *dir;
    // struct dirent *ent;

    // dir = opendir(".");
    // if (dir != NULL) {
    //     while ((ent = readdir(dir)) != NULL) {
    //         //std::cout << ent->d_name << std::endl;
    //         //std::cout << ent->d_namlen << std::endl;
    //         //std::cout << ent->d_ino << std::endl;
    //     }
    //     closedir(dir);
    // } else {
    //     std::cerr << "Could not open directory." << std::endl;
    //     return 1;
    // }

	// std::ofstream file("index1.html");
	// file << generateErrorPages(500);

	// DIR *dir;
    // struct dirent *ent;
    // struct stat st;

    // dir = opendir(".");
    // if (dir != NULL) {
    //     while ((ent = readdir(dir)) != NULL) {
    //         stat(ent->d_name, &st);
    //         //std::cout << "Name: " << "| " << ent->d_name << " | " ;//<< st.st_size << " " << ctime(&st.st_ctime);
	// 		//std::cout << "Size: " << "| " << st.st_size << " | ";
	// 		//std::cout << "Time: " << "| " << ctime(&st.st_ctime);
    //     }
    //     closedir(dir);
    // } else {
    //     perror("");
    //     return EXIT_FAILURE;
    // }

    // return EXIT_SUCCESS;

	// std::string htmlFile;

	// DIR *dir;
    // struct dirent *ent;
    // struct stat st;
	// std::stringstream ss;

    // dir = opendir(".");
	// htmlFile = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Index of /</title></head><body><h1>Index of /</h1><table><thead><tr><th style='padding: 10px;'>Name</th><th style='padding: 10px;'>Size</th><th style='padding: 10px;'>Last Modified</th></tr></thead><tbody>";
    // if (dir != NULL)
	// {
    //     while ((ent = readdir(dir)) != NULL)
	// 	{
    //         stat(ent->d_name, &st);
	// 		htmlFile.append("<tr><td style='padding-left: 10px;'>");
	// 		htmlFile.append(ent->d_name);
	// 		htmlFile.append("</td>");
	// 		htmlFile.append("<td style='padding-left: 10px;'>");
	// 		ss << st.st_size;
	// 		htmlFile.append(ss.str());
	// 		htmlFile.append("</td>");
	// 		htmlFile.append("<td style='padding-left: 10px;'>");
	// 		htmlFile.append(ctime(&st.st_ctime));
	// 		htmlFile.append("</td></tr>");
    //     }
    //     closedir(dir);
    // }
	// htmlFile.append("</tbody></table></body></html>");
	// std::ofstream file("index2.html");
	// file << htmlFile;

	// int code;
	// std::string hello;
	
	// hello = "hasnaa";
	// code = 99;
	// std::stringstream ss;
	// ss << code;
	// hello += ss.str();
	// //std::cout << hello << std::endl;

	// std::string				file("index");
	// std::string::iterator	it;
	// int						position = -1;
	// int						i = 0;
	
	// for (it = file.begin(); it != file.end(); it++)
	// {
	// 	if (*it == '.')
	// 		position = i;
	// 	i++;
	// }
	// //std::cout << position << std::endl;
	// //std::cout << file.substr(position + 1) << std::endl;


	//deleteFolderContent("../myfolder");
	// if (remove("myfolder/index") == -1)
	// 	//std::cout << "fail\n";

	// const char* filename = "/index.html";

    // const char* last_slash = strrchr(filename, '/'); // Find last occurrence of '/' character
    
    // if (last_slash == NULL) { // If no '/' character was found
    //     //std::cout << "Unable to determine directory of file." << std::endl;
    // } else {
    //     int length = last_slash - filename; // Calculate length of directory path
	// 	if (!length)
	// 	{
	// 		char directory[length+2]; // Create char array to hold directory path
			
	// 	}
	// 	else
	// 	{
	// 		char directory[length+2];
	// 		strncpy(directory, filename, length); // Copy directory path to char array
	// 	}
    //     directory[length] = '\0'; // Null-terminate char array
        
    //     //std::cout << "Directory: " << directory << std::endl;
    // }

	// char path[] = "/Users/het-tale/cursus/42_webserv/myfolder/file1";
    // char* dir = dirname(path);
    // //std::cout << "Parent directory: " << dir << std::endl;
	// if (remove(path) == -1)
	// {
	// 	if (access(dir, W_OK) == 0)
	// 		//std::cout << "Internal error " << dir << std::endl;
	// 	else
	// 		//std::cout << "Forbidden " << dir << std::endl;
	// }

	//  time_t now = time(0);
    // struct tm* timeinfo = gmtime(&now);
    // char buffer[80];

    // strftime(buffer, 80, "Date: %a, %d %b %Y %H:%M:%S GMT", timeinfo);
    // //std::cout << buffer << std::endl;

	// //std::cout << generatRandomFileName("hello") << std::endl;
	// //std::cout << generatRandomFileName("hello") << std::endl;

	std::string path = "/Users/het-tale/cursus/42_webserv/";
	std::string dir = "/okk";
	std::string newPath;
	//std::cout << path.size() << std::endl;
	newPath.insert(0, path.c_str(), path.size() - 1);
	newPath.append(dir);
	//std::cout << newPath << std::endl;
}

