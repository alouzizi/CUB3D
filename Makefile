NAME = cub3d


SRCS = map.c \
		player.c \
		utils.c \
		cub3D.c 
CC = cc

OBJ = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

MLX = -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJ) cub3d.h
	$(CC) $(MLX) $(OBJ) -o $(NAME)

%.o: %.c cub3D.h
	$(CC) $(MLX) -c $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all

