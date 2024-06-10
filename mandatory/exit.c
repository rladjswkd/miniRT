/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:41 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:41 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "exit.h"
#include "linked_list.h"
#include "mlx.h"

void	destroy_world(t_world *world)
{
	clear_list(&(world->sp));
	clear_list(&(world->pl));
	clear_list(&(world->cy));
}

void	destroy_mlx(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy(vars->mlx);
}

void	exit_minirt(
	char *msg, t_world *world, t_vars *vars)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
	if (msg)
	{
		printf("%s\n", msg);
		exit_status = EXIT_SUCCESS;
	}
	if (world)
		destroy_world(world);
	if (vars)
		destroy_mlx(vars);
	exit(exit_status);
}
