#ifndef EXIT_H
# define EXIT_H
# include "structure.h"

void	destroy_world(t_world *world);
void	destroy_mlx(t_vars *vars);
void	exit_minirt(char *msg, t_world *world, t_vars *vars, t_thread_param *param);
#endif