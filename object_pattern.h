#ifndef OBJECT_PATTERN_H
# define OBJECT_PATTERN_H
# include "structure.h"

char	uv_pattern_at(t_uv uv, int w, int h);
t_rgb	get_img_rgb(t_img img, t_uv uv);
t_vec	get_basis_vec(t_vec v);
#endif