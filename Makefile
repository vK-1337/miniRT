SRCS =	main.c \
		parsing.c \
		init.c \
		gnl/get_next_line_utils.c \
		gnl/get_next_line.c \
		utils.c \

OBJS = $(SRCS:.c=.o) ./libft/libft.a

NAME = minirt

LIBFT = ./libft/libft.a

LDFLAGS = -L ./libft -lft

CFLAGS = -Wall -Werror -Wextra -g3

# colors
GREEN = \033[0;32m
NC = \033[0m
YELLOW = \e[0;93m

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "	 			+---------------------+\n \
					|  $(YELLOW)    miniRT $(GREEN)[OK]$(NC)    |\n \
					+---------------------+"

$(LIBFT):
	make -C ./libft

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(LIBFT) $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean
	make all

.PHONY: all clean fclean re
