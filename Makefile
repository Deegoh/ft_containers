ifeq ($(shell uname), Linux)
	CC = g++
else ifeq ($(shell c++-12 -dumpversion), 12)
	CC = g++-12
else
	CC = c++
endif
RM = rm -rf
CFLAGS = -Werror -Wall -Wextra -Wfatal-errors
CFLAGS += -std=c++98 -pedantic
CFLAGS += -g3 -fsanitize=address

SRC_DIR = src/
_SRC =	main.cpp\
		vector_tester.cpp
#		pdf.cpp

SRC = $(addprefix $(SRC_DIR), $(_SRC))

INC_DIR = inc/
HEADER=	comparators.hpp\
		iterator_traits.hpp\
		random_access_iterator.hpp\
		reverse_iterator.hpp\
		rbt_iterator.hpp\
		utility.hpp\
		base.hpp\
		vector.hpp\
		vector_tester.hpp\
		map.hpp\
		rb_tree.hpp\
		stack.hpp


INC = $(addprefix $(INC_DIR), $(HEADER))

STD = 0

NAME = a.out

OBJ_DIR = obj/
_OBJ = $(_SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(_OBJ))

.PHONY: all clean fclean re run debug std ft comp leak

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC) ./Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -DSTD=$(STD) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:
	./$(NAME)

ft: re
	./$(NAME) > ft.txt
	cat ft.txt

std: STD = 1
std: re
	./$(NAME) > std.txt
	cat std.txt

comp:
	$(MAKE) ft -C ./
	$(MAKE) std -C ./
	diff std.txt ft.txt

leak: CFLAGS = -Werror -Wall -Wextra -std=c++98 -pedantic -g3
leak: re
	leaks -atExit -- ./$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME).dSYM

re: fclean all