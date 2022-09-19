CC = g++
FLAGS = -Wall -Wextra -Werror
SRCS = main.cpp Node.cpp Tree.cpp Puzzle.cpp

OBJ = $(SRCS:.cpp=.o)
RM = rm -f
NAME = npuzzle

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) Node.hpp Tree.hpp Puzzle.hpp
	$(CC) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME) $(OBJ)

re: fclean all