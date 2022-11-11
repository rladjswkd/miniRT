#ifndef MATRIX_ROTATION_H
# define MATRIX_ROTATION_H
# include "structure.h"

t_mat	mat_rx(double cosine, double sine);
t_mat	mat_ry(double cosine, double sine);
t_mat	mat_rz(double cosine, double sine);
#endif