CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
SRC = main.c  test.c helpers.c error_handle.c  idk.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
OBJ = obj
LIBFT = ./libft
MLX = ./minilibx-linux
GNL = ./get_next_line

OBJECTS = $(OBJ)/$(SRC:.c=.o)

all: $(NAME)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)


$(OBJ)/%.o:%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJECTS)  $(LIBFT)/libft.a 
	$(CC) $(CFLAGS) $(OBJECTS) -L$(MLX) -lmlx -lXext -lX11 -lm  -L$(LIBFT) -lft -o $(NAME)

clean:
	rm -rf $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)
	
re: fclean all

.PHONY: all clean fclean re 

#src *
#compiler *
#flags *
#objects *
#targets
#dependencies
#rules









