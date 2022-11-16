NAME = miniRT
BONUS_NAME = miniRT_bonus

BONUS_FILES = allocator_bonus.c\
       checker_bonus.c\
       converter_bonus.c\
       draw_bonus.c\
       event_handler_bonus.c\
       event_pattern_bonus.c\
       event_transformation_bonus.c\
       exit_bonus.c\
       file_processor_bonus.c\
       get_next_line_bonus.c\
       get_next_line_utils_bonus.c\
       initializer_bonus.c\
       intersect_closest_bonus.c\
       intersect_cone_bonus.c\
       intersect_cylinder_bonus.c\
       intersect_plane_bonus.c\
       intersect_sphere_bonus.c\
       intersect_world_bonus.c\
       lighting_bonus.c\
       linked_list_bonus.c\
       main_bonus.c\
       matrix_inverse_bonus.c\
       matrix_multiplication_bonus.c\
       matrix_rotation_bonus.c\
       matrix_transformation_bonus.c\
       matrix_transpose_bonus.c\
       normal_transformation_bonus.c\
       object_color_bonus.c\
       object_pattern_bonus.c\
       parser_util_split_bonus.c\
       ray_bonus.c\
       set_additional_bonus.c\
       set_essential_bonus.c\
       set_world_bonus.c\
       shadow_bonus.c\
       specular_tangent_bonus.c\
       string_utils_bonus.c\
       uv_mapper_bonus.c\
       vec4_operations_bonus.c\
       vector_operation_1_bonus.c\
       vector_operation_2_bonus.c\
       viewport_bonus.c
BONUS_DIR = ./bonus/
BONUS_SRCS = ${addprefix $(BONUS_DIR), $(BONUS_FILES)}
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -f

%.o : %.c
	$(CC) $(CFLAGS) -Imlx -g -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C mlx 2> /dev/null
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(BONUS_NAME) : $(BONUS_OBJS)
	@make -C mlx 2> /dev/null
	$(CC) $(BONUS_OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(BONUS_NAME)

clean :
	@make clean -C mlx
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) $(BONUS_OBJS)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)

bonus : $(BONUS_NAME)

re : fclean all

.PHONY : all clean fclean re bonus
