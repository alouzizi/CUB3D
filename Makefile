NAME = cub3d


SRCS = map.c \
		player.c \
		utils.c \
		cub3D.c \
		parsing/assests_check.c \
		parsing/check_p_map.c \
		parsing/get_map.c \
		parsing/init.c \
		parsing/map_utilc.c\
		parsing/map_utils.c \
		parsing/player_chek_utils.c \
		parsing/utils.c \
		gnl/get_next_line.c

CC = cc

OBJ = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

MLX = -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJ) cub3d.h $(LIBFT)
	$(CC) $(MLX) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@make -C./libft

%.o: %.c cub3D.h
	$(CC) $(MLX) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@make clean -C libft
fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft
re: fclean all
