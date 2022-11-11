#ifndef VIEWPORT_H
# define VIEWPORT_H
# include "structure.h"

t_vec	get_viewport_vec(t_camera c, t_vec4 axis);
t_viewport	generate_viewport(t_camera c);
#endif