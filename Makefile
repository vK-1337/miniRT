SRCS =	main.c \
		parsing.c \
		init.c \

OBJS = $(SRCS:.cpp=.o) ./libft/libft.a

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
		|  $(YELLOW)  miniRT $(GREEN)[OK]$(NC)   |\n \
		+---------------------+"

$(LIBFT):
	make -C ./libft

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re