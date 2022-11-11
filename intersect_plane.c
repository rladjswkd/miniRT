#include "structure.h"
#include "vector_operation.h"
#include <math.h>

int	intersect_plane(t_ray ray, t_pl pl, double *t)
{
	double	ray_pl_dot;

	ray_pl_dot = vec_dot(ray.dir, pl.norm);
	if (fabs(ray_pl_dot) <= 1e-6)
		return (0);
	*t = vec_dot(vec_sub(pl.coord, ray.pos), pl.norm) / ray_pl_dot;
	return (*t > 1);
}