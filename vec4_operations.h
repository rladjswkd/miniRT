#ifndef VEC4_OPERATIONS_H
# define VEC4_OPERATIONS_H
# include "structure.h"

double	vec4_dot(t_vec4 v1, t_vec4 v2);
t_vec	vec4_to_vec(t_vec4 v);
t_vec4	vec_to_vec4(t_vec v);
t_vec4	arr_to_vec4(double arr[4]);
#endif