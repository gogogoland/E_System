NAME = expert_system
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++11 -Iincludes -Ilibft/includes/

SRCS = main.cpp\
	   TreatData.cpp\
	   Class.Elems.cpp\
	   Class.Storage.cpp\
	   function_to_add.cpp

OBJS = $(SRCS:.cpp=.o)
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[1;34m$(NAME)\033[0m done."
	@$(CC) -o $@ $(CFLAGS) $(OBJS)

%.o: srcs/%.cpp includes/Expert_system.hpp
	@$(CC) -c $(CFLAGS) $<

clean:
	@echo "Remove \033[1;30m$(OBJS)\033[0m"
	@$(RM) $(OBJS)

fclean: clean
	@echo "Remove \033[1;31m$(NAME)\033[0m"
	@rm -f $(NAME)

re: fclean all
