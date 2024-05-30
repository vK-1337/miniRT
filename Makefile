#Colors / base 16 / Bright
DEF_COLOR		= \033[0;39m
GRAY			= \033[0;90m
RED				= \033[0;91m
GREEN			= \033[0;92m
YELLOW			= \033[0;93m
BLUE			= \033[0;94m
MAGENTA			= \033[0;95m
CYAN			= \033[0;96m
WHITE			= \033[0;97m

#Colors / Perso / Bright

ORANGE			= \033[38;5;214m

#Mlx42

MLX_DIR			= mlx42/
MLX_NAME		= libmlx.a
MLX				= $(MLX_DIR)$(MLX_NAME)

#Libft

LIBFT_DIR		= libft/
LIBFT_NAME		= libft.a
LIBFT			= $(LIBFT_DIR)$(LIBFT_NAME)

#Variables

NAME			= MiniRT
CC				= cc
FLAGS			= -Wall -Werror -Wextra -g3
RM				= rm -f
AR				= ar rcs
NORM			= ./includes\
					./libft/include/\
					./libft/src_lib
INCLUDE			= 	-I ./includes/\
					-I ./libft/include/\
					-I ./mlx42/

#Sources

OBJ_DIR_F 		= obj/
SRC_DIR_F		= src/
SRC_FUNCTIONS_F	= main color_calculation tuple_calculations tuple_calculations2 rays \
					matrix_calcul matrix_deter_cofac matrix_utils matrix_utils2 utils init \
					parsing get_next_line get_next_line_utils cylindre_lst sphere_lst plan_lst \
					reflections light tuple_init camera matrix_transformation\

FRACT_SRC		= $(addprefix $(SRC_DIR_F), $(addsuffix .c, $(SRC_FUNCTIONS_F)))
FRACT_OBJ		= $(addprefix $(OBJ_DIR_F), $(addsuffix .o, $(SRC_FUNCTIONS_F)))

IFMAKE_DIR_F	= .cache_exists

#instructions

all:			$(MLX) $(LIBFT) $(NAME)

$(IFMAKE_DIR_F):
					@mkdir -p $(OBJ_DIR_F)

$(MLX):
					@echo "Getting MinilibX ready"
					@make -sC $(MLX_DIR)

$(LIBFT):
					@echo "Getting libft ready"
					@make -sC $(LIBFT_DIR)

$(OBJ_DIR_F)%.o: $(SRC_DIR_F)%.c | $(IFMAKE_DIR_F)
					@echo "$(ORANGE)Loading... $< $(DEF_COLOR)"
					@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR_F)MiniRT/%.o: $(SRC_DIR_F)MiniRT/%.c | $(IFMAKE_DIR_F)
					@echo "$(ORANGE)Loading... $< $(DEF_COLOR)"
					@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(FRACT_OBJ)
					@echo "Compiling MiniRT..."
					@$(CC) $(FLAGS) -o $(NAME) $(FRACT_OBJ) $(MLX) $(LIBFT) $(INCLUDE) -lXext -lX11 -lm -g3
					@echo "MiniRT ready."

bonus:			all

clean:
					@echo "Removing object files"
					@rm -rf $(OBJ_DIR_F)
					@make clean -C $(LIBFT_DIR)

fclean:			clean
					@echo "Removing Mini_rt..."
					@rm -f $(NAME)
					@rm -f $(LIBFT_DIR)$(LIBFT_NAME)

re:				fclean all
					@echo "$(BLUE)Cleaned and rebuilt everything for MiniRT$(DEF_COLOR)"

norm:
					@norminette $(SRC_DIR_F) $(NORM) $(LIBFT_DIR) | grep -v Norme -B1 || true
					@echo "Norminet the cat says : $(RED)M$(ORANGE)e$(YELLOW)o$(GREEN)w$(CYAN) !$(BLUE)!$(MAGENTA)!$(DEF_COLOR)"

.PHONY: all re clean fclean norm bonus
