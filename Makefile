CC = clang++
FLAGS = -Wall -Wextra -Werror
SRCS = main.cpp

OBJ = $(SRCS:.cpp=.o)
RM = rm -f
NAME = npuzzle

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME) $(OBJ)

re: fclean all