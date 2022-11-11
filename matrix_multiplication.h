#ifndef MATRIX_MULTIPLICATION_H
# define MATRIX_MULTIPLICATION_H
# include "structure.h"

t_vec4	mat_mul_vec4(t_mat mat, t_vec4 v);
t_mat	mat_mul(t_mat mat1, t_mat mat2);
#endif