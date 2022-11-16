/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:54 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:56 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "constant_bonus.h"
#include <stdlib.h>
#include "mlx.h"

void	convert_color_to_grayscale(t_img *img)
{
	int				i;
	int				j;
	unsigned char	color;
	int				pixel;

	j = -1;
	while (++j < img->height)
	{
		i = -1;
		while (++i < img->width)
		{
			pixel = (i + j * img->width) * 4;
			color = 0.11 * (unsigned char)img->addr[pixel]
				+ 0.59 * (unsigned char)img->addr[pixel + 1]
				+ 0.3 * (unsigned char)img->addr[pixel + 2];
			img->addr[pixel] = color;
			img->addr[pixel + 1] = color;
			img->addr[pixel + 2] = color;
		}
	}
}

int	get_new_xpm_image(void *mlx, t_img *img, char *file)
{
	img->ptr = mlx_xpm_file_to_image(mlx, file,
			&img->width, &img->height);
	if (!img->ptr)
		return (0);
	img->addr = mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		return (0);
	return (1);
}

int	create_thread_param(t_world *world, t_vars *vars, t_thread_param **param)
{
	t_thread_param	*ret;
	int				i;

	ret = (t_thread_param *)malloc(sizeof(t_thread_param) * THREAD);
	if (ret == NULL)
		return (0);
	i = -1;
	while (++i < THREAD)
	{
		ret[i].vars = vars;
		ret[i].world = world;
		ret[i].index = i;
	}
	*param = ret;
	return (1);
}

void	init_world(t_world *world)
{
	world->l = 0;
	world->sp = 0;
	world->pl = 0;
	world->cy = 0;
	world->cn = 0;
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
	if (!get_new_xpm_image(vars->mlx, &vars->c_img, COLOR_IMG))
		return (0);
	if (!get_new_xpm_image(vars->mlx, &vars->b_img, BUMP_IMG))
		return (0);
	convert_color_to_grayscale(&vars->b_img);
	vars->obj.type = NONE;
	vars->obj.object = 0;
	vars->obj.t = 0;
	return (1);
}
