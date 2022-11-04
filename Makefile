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
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@ -pthread
#	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -g -c $< -o $@ -pthread

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) -pthread

bonus: $(NAME)

clean :
	$(RM) $(RMFLAGS) $(OBJS)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re 
