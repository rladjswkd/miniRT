/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:23 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:25 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "constant_bonus.h"
#include "ray_bonus.h"
#include "viewport_bonus.h"
#include "mlx.h"

void	*drawing(void *b_param)
{
	t_thread_param	param;
	t_ray			ray;
	int				i;
	int				j;

	param = *(t_thread_param *)b_param;
	j = param.index * (HEIGHT / THREAD) - 1;
	while (++j < (param.index + 1) * (HEIGHT / THREAD))
	{
		i = -1;
		while (++i < WIDTH)
		{
			ray = generate_ray(param.world->c.coord, param.viewport, i, j);
			trace_ray(param.vars, param.world, ray, j * WIDTH + i);
		}
	}
	return (0);
}

int	draw_img(t_thread_param *param)
{
	t_viewport	viewport;
	t_vars		*vars;
	void		*tmp;
	int			i;

	vars = param->vars;
	viewport = generate_viewport(param->world->c);
	i = -1;
	while (++i < THREAD)
	{
		param[i].viewport = viewport;
		if (pthread_create(&(param[i].thread_id), NULL, drawing, param + i))
			return (0);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(param[i].thread_id, &tmp);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (1);
}
