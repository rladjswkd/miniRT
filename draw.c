/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:23 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:25 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "constant.h"
#include "ray.h"
#include "viewport.h"
#include "mlx.h"

void	draw_img(t_world *world, t_vars *vars)
{
	t_viewport	viewport;
	t_ray		ray;
	int			i;
	int			j;

	viewport = generate_viewport(world->c);
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			ray = generate_ray(world->c.coord, viewport, i, j);
			trace_ray(vars, world, ray, j * WIDTH + i);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
}
