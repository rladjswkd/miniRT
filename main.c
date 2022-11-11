/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:26 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:26 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"
#include "exit.h"
#include "initializer.h"
#include "file_processor.h"
#include "draw.h"
#include "mlx.h"

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
