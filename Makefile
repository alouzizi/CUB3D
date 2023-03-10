NAME = cub3d
HEADER = cub3d.h

SRCS =	player.c \
		utils.c \
		cub3D.c  \
		cast.c \
		projection.c \
		get_next_line.c \
		parsing/parsing.c \
		parsing/utils.c \
		parsing/utils2.c \
		parsing/get_data.c

CC = cc

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

MLX = -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJS) cub3d.h $(LIBFT)
	$(CC) $(FLAGS) $(MLX) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@make -C./libft

$(OBJS) : $(HEADER)

$(OBJS) : %.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@make clean -C libft
fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft
re: fclean all
