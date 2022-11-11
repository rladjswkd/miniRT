/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_essential.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:55 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:56 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "linked_list.h"
#include "checker.h"
#include "converter.h"
#include "parser_util_split.h"
#include "set_world.h"

int	set_rgb(char *rgb_str, t_rgb *rgb)
{
	char	**rgb_info;
	int		rgb_info_cnt;

	if (!check_comma_cnt(rgb_str))
		return (0);
	rgb_info = split_line(rgb_str, ',', &rgb_info_cnt);
	if (!rgb_info)
		return (0);
	if (rgb_info_cnt != 3
		|| !get_int(rgb_info[0], &(rgb->r))
		|| !get_int(rgb_info[1], &(rgb->g))
		|| !get_int(rgb_info[2], &(rgb->b)))
		return (free_splitted(rgb_info, 0));
	if (!check_rgb(*rgb))
		return (free_splitted(rgb_info, 0));
	return (free_splitted(rgb_info, 1));
}

int	set_coordinate(char *coord_str, t_coord *coord)
{
	char	**coord_info;
	int		coord_info_cnt;

	if (!check_comma_cnt(coord_str))
		return (0);
	coord_info = split_line(coord_str, ',', &coord_info_cnt);
	if (!coord_info)
		return (0);
	if (coord_info_cnt != 3
		|| !get_double(coord_info[0], &(coord->x))
		|| !get_double(coord_info[1], &(coord->y))
		|| !get_double(coord_info[2], &(coord->z)))
		return (free_splitted(coord_info, 0));
	return (free_splitted(coord_info, 1));
}

int	set_ambient(char **info, int cnt, t_world *world)
{
	double		intensity;
	t_ambient	*a;

	if (cnt != 3)
		return (0);
	a = &(world->a);
	if (!get_double(info[1], &intensity) || intensity < 0 || 1 < intensity)
		return (0);
	if (!set_rgb(info[2], &(a->rgb)))
		return (0);
	a->intensity = intensity;
	return (1);
}

int	set_light(char **info, int cnt, t_world *world)
{
	double	intensitiy;
	t_light	*l;

	if (cnt != 4)
		return (0);
	l = (t_light *)(get_last_node(world->l)->data);
	if (!set_coordinate(info[1], &(l->coord)))
		return (0);
	if (!get_double(info[2], &intensitiy) || intensitiy < 0 || 1 < intensitiy)
		return (0);
	if (!set_rgb(info[3], &(l->rgb)))
		return (0);
	l->intensity = intensitiy;
	return (1);
}

int	set_camera(char **info, int cnt, t_world *world)
{
	int			fov;
	t_camera	*c;

	if (cnt != 4)
		return (0);
	c = &(world->c);
	if (!set_coordinate(info[1], &(c->coord)))
		return (0);
	if (!set_coordinate(info[2], &(c->norm))
		|| !check_normal(c->norm))
		return (0);
	if (!get_int(info[3], &fov) || fov < 0 || 180 < fov)
		return (0);
	c->lati = 0;
	c->longi = 0;
	c->norm_const = c->norm;
	c->fov = fov;
	return (1);
}
