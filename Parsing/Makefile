NAME = test
CC = c++
OBJS = ${SRC:.cpp=.o}
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = test.cpp http.cpp server.cpp location.cpp

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all