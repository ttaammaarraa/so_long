include src.mk

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
LIBFT = ./libft
MLX = ./minilibx-linux
GNL = ./get_next_line

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJECTS)  $(LIBFT)/libft.a 
	$(CC) $(CFLAGS) $(OBJECTS) -L$(MLX) -lmlx -lXext -lX11 -lm  -L$(LIBFT) -lft -o $(NAME)

clean:
	rm -f $(OBJECTS)
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









