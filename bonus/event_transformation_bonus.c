/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_transformation_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:37 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:39 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "constant_bonus.h"
#include "normal_transformation_bonus.h"
#include "matrix_multiplication_bonus.h"
#include "matrix_transformation_bonus.h"
#include "vector_operation_bonus.h"
#include "viewport_bonus.h"

void	rotate_object(t_thread_param *param, int keycode)
{
	t_obj		obj;
	t_obj_info	*current_object;
	int			latitude;
	int			longitude;
	int			type;

	obj = param->vars->obj;
	type = obj.type;
	if (type == NONE || type == LIGHT || type == SPHERE)
		return ;
	current_object = (t_obj_info *)(obj.object);
	latitude = current_object->lati;
	longitude = current_object->longi;
	latitude += (keycode == ONE) * ANGLE + (keycode == TWO) * -ANGLE;
	latitude %= 360;
	longitude += (keycode == THREE) * ANGLE + (keycode == FOUR) * -ANGLE;
	longitude %= 360;
	current_object->lati = latitude;
	current_object->longi = longitude;
	current_object->norm = rotate_normal(
			current_object->norm_const,
			mat_mul(rotate_longitude(longitude), rotate_latitude(latitude)));
}

void	translate_object(t_thread_param *param, int keycode)
{
	t_obj_info	*current_object;
	t_camera	camera;
	t_vec		d_vec;
	t_vec		vec_x;
	t_vec		vec_y;

	if (param->vars->obj.type == NONE)
		return ;
	current_object = (t_obj_info *)(param->vars->obj.object);
	camera = param->world->c;
	vec_x = get_viewport_vec(camera, (t_vec4){-1, 0, 0, 1});
	vec_y = get_viewport_vec(camera, (t_vec4){0, -1, 0, 1});
	d_vec = vec_add(
			vec_add(
				vec_scale(vec_x, 10 * ((keycode == E) - (keycode == Q))),
				vec_scale(vec_y, 10 * ((keycode == D) - (keycode == A)))
				),
			vec_scale(camera.norm, 10 * ((keycode == W) - (keycode == S))));
	current_object->coord = vec_add(current_object->coord, d_vec);
}

void	resize_diameter(t_thread_param *param, int code)
{
	t_obj	obj;
	int		type;
	double	*diameter;

	obj = param->vars->obj;
	type = obj.type;
	if (type == SPHERE)
		diameter = &(((t_sp *)(obj.object))->diameter);
	else if (type == CYLINDER)
		diameter = &(((t_cy *)(obj.object))->diameter);
	else if (type == CONE)
		diameter = &(((t_cn *)(obj.object))->diameter);
	else
		return ;
	*diameter += (code == UP) - (code == DOWN);
	if (*diameter < 1e-6)
		*diameter = 1.0;
}

void	resize_height(t_thread_param *param, int code)
{
	t_obj	obj;
	int		type;
	double	*height;

	obj = param->vars->obj;
	type = obj.type;
	if (type == CYLINDER)
		height = &(((t_cy *)(obj.object))->height);
	else if (type == CONE)
		height = &(((t_cn *)(obj.object))->height);
	else
		return ;
	*height += (code == RIGHT) - (code == LEFT);
	if (*height < 1e-6)
		*height = 1.0;
}

void	select_non_selectable(t_thread_param *param, int code)
{
	t_obj			*obj;
	static t_node	*light;

	obj = &(param->vars->obj);
	if (code == K)
	{
		obj->type = CAMERA;
		obj->object = &(param->world->c);
		return ;
	}
	if (light == NULL || light->next == NULL)
		light = param->world->l;
	else
		light = light->next;
	obj->type = LIGHT;
	obj->object = light->data;
}
