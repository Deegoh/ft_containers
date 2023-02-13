ifeq ($(shell uname), Linux)
	CXX = g++
else ifeq ($(shell c++-12 -dumpversion), 12)
	CXX = g++-12
else
	CXX = c++
endif
RM = rm -rf
CXXFLAGS = -Werror -Wall -Wextra -Wfatal-errors
CXXFLAGS += -std=c++98 -pedantic
CXXFLAGS += -g3 -fsanitize=address

SEED = 10

SRC_DIR = src/
_SRC =	main.cpp

SRC = $(addprefix $(SRC_DIR), $(_SRC))

INC_DIR = inc/
HEADER=	comparators.hpp\
		iterator_traits.hpp\
		random_access_iterator.hpp\
		reverse_iterator.hpp\
		rbt_iterator.hpp\
		utility.hpp\
		vector.hpp\
		map.hpp\
		rb_tree.hpp\
		stack.hpp\
		set.hpp


INC = $(addprefix $(INC_DIR), $(HEADER))

STD = 0

NAME = a.out

OBJ_DIR = obj/
_OBJ = $(_SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(_OBJ))

.PHONY: all clean fclean re run debug std ft comp leak tester

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC) ./Makefile | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -DSTD=$(STD) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

run:
	./$(NAME)

ft: re
	./$(NAME) $(SEED) > ft.txt
	cat ft.txt

std: STD = 1
std: re
	./$(NAME) $(SEED) > std.txt
	cat std.txt

comp:
	$(MAKE) ft -C ./
	$(MAKE) std -C ./
	diff std.txt ft.txt

tester:
	$(MAKE) re -C ./tester
	$(MAKE) comp -C ./tester

leak: CFLAGS = -Werror -Wall -Wextra -std=c++98 -pedantic -g3
leak: re
	leaks -atExit -- ./$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME).dSYM

re: fclean all