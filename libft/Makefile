NAME =	libft.a
INC = libft.h 
SRCS =	ft_atoi.c\
		ft_bzero.c \
		ft_isdigit.c \
		ft_memset.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_realloc.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlen.c  \
		ft_strncmp.c \
		ft_strtrim.c \
		ft_substr.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
AR = @ar -rcs

all: $(NAME)

$(NAME):$(OBJS) $(INC)
	$(AR) $(NAME) $(OBJS)

%.o : %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean:clean
	@$(RM) $(NAME)

re: fclean all