/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:29 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:30 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"
#include "event_pattern.h"
#include "event_transformation.h"
#include "exit.h"
#include "intersect_world.h"
#include "draw.h"

int	exit_handler(t_thread_param *param)
{
	exit_minirt(0, param->world, param->vars, param);
	return (0);
}

int	key_press_handler(int code, t_thread_param *param)
{
	t_vars	*vars;

	if (code == ESC)
		return (exit_handler(param));
	vars = param->vars;
	if (code == ONE || code == TWO || code == THREE || code == FOUR)
		rotate_object(param, code);
	else if (code == W || code == A || code == S || code == D
		|| code == Q || code == E)
		translate_object(param, code);
	else if (code == K || code == L)
		select_non_selectable(param, code);
	else if (code == UP || code == DOWN)
		resize_diameter(param, code);
	else if (code == LEFT || code == RIGHT)
		resize_height(param, code);
	else if (code == C)
		apply_checker(vars->obj);
	else if (code == B)
		apply_bump(vars->obj);
	else if (code == I)
		apply_img(vars->obj);
	draw_img(param);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_thread_param *param)
{
	t_ray		ray;
	t_camera	c;

	if (MOUSE_LEFT != button)
		return (0);
	c = param->world->c;
	ray = generate_ray(c.coord, generate_viewport(c), x, y);
	intersect(ray, *(param->world), &(param->vars->obj));
	return (0);
}
