#ifndef INITIALIZER_H
# define INITIALIZER_H
# include "structure.h"

void	convert_color_to_grayscale(t_img *img);
int		get_new_xpm_image(void *mlx, t_img *img, char *file);
int		create_thread_param(t_world *world, t_vars *vars,
	t_thread_param **param);
void	init_world(t_world *world);
int		init_mlx_pointers(t_vars *vars);
#endif