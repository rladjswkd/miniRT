NAME = fractol
SRCS = color.c\
       draw.c\
       fractal.c\
       handler.c\
       main.c\
       newton_fractal.c\
       newton_math.c\
       status.c\
       utils.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -f

%.o : %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

bonus: $(NAME)

clean :
	$(RM) $(RMFLAGS) $(OBJS)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re 
