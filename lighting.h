#ifndef LIGHTING_H
# define LIGHTING_H
# include "structure.h"

t_vec	compute_diffuse(t_vec inter, t_vec n, t_light light);
t_vec	compute_specular(t_vec inter, t_vec n, t_vec v, t_light light);
t_vec	compute_lighting(t_vec inter, t_vec n, t_vec v, t_world world);
#endif