include src.mk

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
LIBFT = ./libft
FT_PRINTF = ./ft_printf
MLX = ./minilibx-linux
GNL = ./get_next_line

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(FT_PRINTF)/libftprintf.a:
	@make -C $(FT_PRINTF)


$(NAME):$(OBJECTS)  $(LIBFT)/libft.a $(FT_PRINTF)/libftprintf.a
	$(CC) $(CFLAGS) $(OBJECTS) -L$(MLX) -lmlx -lXext -lX11 -lm  -L$(LIBFT) -lft -L$(FT_PRINTF) -lftprintf -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS)
	@make clean -C $(LIBFT)
	@make clean -C $(FT_PRINTF)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(FT_PRINTF)
re: fclean all

.PHONY: all clean fclean re 

#src *
#compiler *
#flags *
#objects *
#targets
#dependencies
#rules









