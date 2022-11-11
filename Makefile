NAME = miniRT
SRCS = allocator.c\
       checker.c\
       converter.c\
       draw.c\
       event_handler.c\
       event_pattern.c\
       event_transformation.c\
       exit.c\
       file_processor.c\
       get_next_line.c\
       get_next_line_utils.c\
       initializer.c\
       intersect_closest.c\
       intersect_cone.c\
       intersect_cylinder.c\
       intersect_plane.c\
       intersect_sphere.c\
       intersect_world.c\
       lighting.c\
       linked_list.c\
       main.c\
       matrix_inverse.c\
       matrix_multiplication.c\
       matrix_rotation.c\
       matrix_transformation.c\
       matrix_transpose.c\
       normal_transformation.c\
       object_color.c\
       object_pattern.c\
       parser_util_split.c\
       ray.c\
       set_additional.c\
       set_essential.c\
       set_world.c\
       shadow.c\
       specular_tangent.c\
       string_utils.c\
       uv_mapper.c\
       vec4_operations.c\
       vector_operation_1.c\
       vector_operation_2.c\
       viewport.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -f

%.o : %.c
	$(CC) $(CFLAGS) -Imlx -O3 -c $< -o $@

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
