/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:54 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:56 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "constant.h"
#include <stdlib.h>
#include "mlx.h"

void	init_param(t_world *world, t_vars *vars, t_thread_param *param)
{
	param->vars = vars;
	param->world = world;
}

void	init_world(t_world *world)
{
	world->sp = 0;
	world->pl = 0;
	world->cy = 0;
}

int	init_mlx_pointers(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (0);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "miniRT");
	if (!vars->win)
		return (0);
	vars->img.ptr = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img.ptr)
		return (0);
	vars->img.addr = mlx_get_data_addr(vars->img.ptr, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (!vars->img.addr)
		return (0);
	vars->obj.type = NONE;
	vars->obj.object = 0;
	vars->obj.t = 0;
	return (1);
}
