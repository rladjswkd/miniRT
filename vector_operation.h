#ifndef VECTOR_OPERATION_H
# define VECTOR_OPERATION_H
# include "structure.h"
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_scale(t_vec vec, double scalar);
t_vec	vec_neg(t_vec vec);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_cross(t_vec v1, t_vec v2);
double	vec_len(t_vec vec);
t_vec	vec_normalize(t_vec vec);
t_vec	vec_proj(t_vec v1, t_vec v2);
#endif