#include "structure.h"

t_mat	mat_rx(double cosine, double sine)
{
	return ((t_mat){{
		{1, 0, 0, 0},
		{0, cosine, -sine, 0},
		{0, sine, cosine, 0},
		{0, 0, 0, 1}}, 4});
}

t_mat	mat_ry(double cosine, double sine)
{
	return ((t_mat){{
		{cosine, 0, sine, 0},
		{0, 1, 0, 0},
		{-sine, 0, cosine, 0},
		{0, 0, 0, 1}}, 4});	
}

t_mat	mat_rz(double cosine, double sine)
{
	return ((t_mat){{
		{cosine, -sine, 0, 0},
		{sine, cosine, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}}, 4});
}