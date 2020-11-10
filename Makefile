##
## EPITECH PROJECT, 2019
## CORE MAKEFILE
## File description:
## BINARY MAKER
##

ROOT_PATH		=	../
INCLUDE_PATH	=	include/
SRC_PATH		=	src/

NAME 		= 	plazza

PRINT		=	@echo -e
RM			=	@rm -f

DEFAULT	=	\033[0m
GREEN	=	\033[0;32m
RED		=	\033[1;31m


CPPFLAGS 	+=	-W -Wall -Wextra -I./$(INCLUDE_PATH)
CPPFLAGS 	+=	-Werror
CPPFLAGS	+=	-pedantic -Wpedantic
CPPFLAGS	+=	-Wno-long-long
CPPFLAGS 	+=	-I./$(INCLUDE_PATH)

LDFLAGS 	+=	-lrt -pthread

SRC		=	$(SRC_PATH)Kitchen.cpp			\
			$(SRC_PATH)LoadBalancer.cpp	\
			$(SRC_PATH)Pizza.cpp	\
			$(SRC_PATH)Reception.cpp			\
			$(SRC_PATH)Utils.cpp	\

MAIN	=	main.cpp	\

OBJ 	= 	$(SRC:.cpp=.o)

$(NAME): $(OBJ)
	g++ $(CPPFLAGS) $(MAIN) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS) && \
	echo "\n[ $(GREEN)$(NAME) created !$(DEFAULT) ]" || \
	echo "\n[ $(RED)Error compiling $(NAME)$(DEFAULT) ]"

all: $(NAME)

$(SRC_LIB): $(OBJ)
	@mkdir $(LIBSRC_PATH)
	$(AR) rc $@ $^

lib: $(SRC_LIB)

clean:
	$(RM) $(OBJ) $(OBJ:.o=.gcno) $(OBJ:.o=.gcda)
	$(RM) $(SRC_LIB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re lib