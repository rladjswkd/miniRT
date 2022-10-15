NAME = minirt
SRCS = checker.c\
       converter.c\
       get_next_line.c\
       get_next_line_utils.c\
       main.c\
       parser.c\
       parser_util_split.c\
       string_utils.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -f

%.o : %.c
	$(CC) $(CFLAGS) -Imlx -g -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C mlx 2> /dev/null
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	@make clean -C mlx
	$(RM) $(RMFLAGS) $(OBJS)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)

bonus : $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus