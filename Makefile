# ==========================
#   get_next_line - Makefile
# ==========================

NAME	= get_next_line.a
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror -g
SRC		= get_next_line.c get_next_line_utils.c
OBJ		= $(SRC:.c=.o)

# Rules
all: $(NAME)

 $(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(NAME)
	@clear
	$(CC) $(CFLAGS) main.c $(NAME) -o tests
	@./tests

clean:
	rm -f $(OBJ)
	@echo "Object files removed"

fclean: clean
	rm -f $(NAME) tests
	@echo "Library and test binary removed"

re: fclean all

.PHONY: all clean fclean re tests