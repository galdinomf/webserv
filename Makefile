SRCS = main.cpp\
	   ASocket.cpp\
	   callSocket.cpp\
	   BindSocket.cpp\
	   HTTPServer.cpp\
	   HTTPServer_start.cpp\
	   HTTPRequest.cpp\
	   HTTPResponse.cpp\
	   parse_request.cpp\
	   MsgProcessor.cpp\
	   MsgProcessor2.cpp\
	   MsgProcessor3.cpp\
	   Configs.cpp\

OBJ_DIR = obj/
SRC_DIR = src/

OBJS = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.cpp=.o)))

FLAGS = -Wextra -Wall -Werror -std=c++98 -g

NAME = webserv

RM = rm -f

CC = c++

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ -I ./includes

clean:
	$(RM) $(OBJS)
	rmdir $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: clean fclean re all
