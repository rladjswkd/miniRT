/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:26 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:26 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler_bonus.h"
#include "exit_bonus.h"
#include "initializer_bonus.h"
#include "file_processor_bonus.h"
#include "draw_bonus.h"
#include "mlx.h"
#include "matrix_transformation_bonus.h"
#include "matrix_multiplication_bonus.h"
#include "matrix_transpose_bonus.h"
#include "vec4_operations_bonus.h"
#include "matrix_rotation_bonus.h"
#include <math.h>

static t_mat	get_matrix_c_to_z(t_world *world)
{
	t_vec	c_dir;
	t_mat	rx;
	t_mat	ry;
	t_mat	r_opposite;

	c_dir = world->c.norm_const;
	rx = get_rx_to_z(c_dir);
	c_dir = vec4_to_vec(mat_mul_vec4(rx, vec_to_vec4(c_dir)));
	ry = get_ry_to_z(c_dir);
	c_dir = vec4_to_vec(mat_mul_vec4(ry, vec_to_vec4(c_dir)));
	r_opposite = (t_mat){
		{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}, 4};
	if (c_dir.z < 0)
		r_opposite = mat_rx(cos(M_PI), sin(M_PI));
	c_dir = vec4_to_vec(mat_mul_vec4(r_opposite, vec_to_vec4(c_dir)));
	return (mat_mul(r_opposite, mat_mul(ry, rx)));
}

static void rotate_coord(t_node *sp_node, t_node *l_node, t_mat op)
{
	t_sp	*sp;
	t_light	*l;

	while (sp_node)
	{
		sp = (t_sp *)(sp_node->data);
		sp->coord = vec4_to_vec(mat_mul_vec4(op, vec_to_vec4(sp->coord)));
		sp_node = sp_node->next;
	}
	while (l_node)
	{
		l = (t_light *)(l_node->data);
		l->coord = vec4_to_vec(mat_mul_vec4(op, vec_to_vec4(l->coord)));
		l_node = l_node->next;
	}	
}

static void	rotate_coord_and_norm(t_node *node, t_mat op)
{
	t_obj_info	*info;

	while (node)
	{
		info = (t_obj_info *)(node->data);
		info->coord = vec4_to_vec(mat_mul_vec4(op, vec_to_vec4(info->coord)));
		info->norm_const = vec4_to_vec(mat_mul_vec4(op, vec_to_vec4(info->norm_const)));
		info->norm = info->norm_const;
		node = node->next;
	}
}

static void	rotate_world(t_world *world)
{
	t_mat		op;
	t_node		c_node;

	op = get_matrix_c_to_z(world);
	c_node.data = &(world->c);
	c_node.next = 0;
	rotate_coord_and_norm(&c_node, op);
	rotate_coord_and_norm(world->cn, op);
	rotate_coord_and_norm(world->cy, op);
	rotate_coord_and_norm(world->pl, op);
	rotate_coord(world->sp, world->l, op);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_vars			vars;
	t_world			world;
	t_thread_param	*param;

	if (argc != 2)
		exit_minirt(ERROR_MSG, 0, 0, 0);
	fd = open_file(argv[1]);
	if (fd < 0)
		exit_minirt(ERROR_MSG, 0, 0, 0);
	init_world(&world);
	if (!read_file(fd, &world))
		exit_minirt(ERROR_MSG, &world, 0, 0);
	rotate_world(&world);
	if (!init_mlx_pointers(&vars))
		exit_minirt(ERROR_MSG, &world, &vars, 0);
	if (!create_thread_param(&world, &vars, &param) || !draw_img(param))
		exit_minirt(ERROR_MSG, &world, &vars, param);
	select_non_selectable(param, K);
	mlx_key_hook(vars.win, key_press_handler, param);
	mlx_mouse_hook(vars.win, mouse_handler, param);
	mlx_hook(vars.win, 17, 0, exit_handler, param);
	mlx_loop(vars.mlx);
	return (0);
}
