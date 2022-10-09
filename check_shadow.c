int	check_shadow_sp(t_ray ray, t_node *sp)
{
	double	cur;

	cur = 2;
	if (!sp)
		return (0);
	while (sp->data)
	{
		if (intersect_sphere(ray, *((t_sp *)(sp->data)), &cur) && cur < 2)
			return (1);
	}
	return (0);
}

int	check_shadow_cy(t_ray ray, t_node *cy)
{
	double	cur;

	cur = 2;
	if (!cy)
		return (0);
	while (cy->data)
	{
		if (intersect_cylinder(ray, *((t_cy *)(cy->data)), &cur) && cur < 2)
			return (1);
	}
	return (0);
}

int	check_shadow_pl(t_ray ray, t_node *pl)
{
	double	cur;

	cur = 2;
	if (!pl)
		return (0);
	while (pl->data)
	{
		if (intersect_plane(ray, *((t_pl *)(pl->data)), &cur) && cur < 2)
			return (1);
	}
	return (0);
}

t_ray	get_l_ray(t_light l, t_ray ray, t_obj	obj)
{
	t_ray	l_ray;
	t_vec	t_pos;

	t_pos = vec_add(vec_scale(ray.dir, obj.t), ray.pos);
	l_ray.dir = vec_sub(l.coord, ray.pos);
	l_ray.pos = vec_sub(t_pos, l_ray.dir);
	return (l_ray);
}

int	check_shadow(t_rt_info info, t_ray l_ray)
{
	if (check_shadow_sp(l_ray, info.sp))
		return (1);
	if (check_shadow_cy(l_ray, info.cy))
		return (1);
	if (check_shadow_pl(l_ray, info.pl))
		return (1);
	return (0);
}