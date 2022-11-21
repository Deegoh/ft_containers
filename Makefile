ifeq ($(shell uname), Linux)
	CC = g++
else ifeq ($(shell c++-12 -dumpversion), 12)
	CC = g++-12
else
	CC = c++
endif
RM = rm -rf
CFLAGS = -Werror -Wall -Wextra
CFLAGS += -std=c++98 -pedantic
CFLAGS += -g -fsanitize=address

SRC_DIR = src/
_SRC =	main.cpp\
#		pdf.cpp

SRC = $(addprefix $(SRC_DIR), $(_SRC))

INC_DIR = inc/
HEADER=	iterator.hpp\
		vector.hpp
INC = $(addprefix $(INC_DIR), $(HEADER))

NAME = a.out

OBJ_DIR = obj/
_OBJ = $(_SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(_OBJ))

.PHONY: all clean fclean re run debug std

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC) ./Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_STD): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC) ./Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -DSTD=1 -I $(INC_DIR) -o $@ -c $<

std: $(OBJ_STD)
	$(CC) $(CFLAGS) -DSTD=1 $(OBJ) -o $(NAME)

run:
	./$(NAME)

debug: CFLAGS += -g -fsanitize=address
debug: re

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME).dSYM

re: fclean all