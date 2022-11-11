#ifndef RAY_H
# define RAY_H
# include "structure.h"

t_ray	get_l_ray(t_light l, t_vec p);
int		trace_ray(t_vars *vars, t_world *world, t_ray ray, int i);
t_ray	generate_ray(t_coord pos, t_viewport viewport, int i, int j);
#endif