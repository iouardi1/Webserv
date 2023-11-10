NAME = webserv
CC = c++
OBJS = ${SRC:.cpp=.o}
CPPFLAGS = -std=c++98 -Wall -Wextra -Werror
SRC =	Parsing/http.cpp \
		Parsing/server.cpp \
		Parsing/Request.cpp \
		Parsing/location.cpp \
		networking/miniserver.cpp  \
		networking/client.cpp \
		networking/mySocket.cpp \
		Response/Response.class.cpp \
		Response/CGI.class.cpp

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all