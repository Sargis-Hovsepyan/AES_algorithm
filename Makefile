NAME = aes

SRCS = $(wildcard sources/*.cpp)
OBJS = $(SRCS:.cpp=.o)

CC = c++
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I ./includes


.cpp.o:
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(<:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n"
	@echo "\033[0;32mCompiling AES algorithm..."
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "Done!\033[0m"

clean:
	@echo "\033[0;31mRemoving binaries..."
	@rm -rf $(OBJS)
	@echo "Done!\n\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	@$(RM) $(NAME)
	@echo "Done!\n\033[0m"

re: fclean all

.PHONY: all clean, fclean, re
