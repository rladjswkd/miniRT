/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:10 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:11 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include <stdlib.h>

int	alloc_light(void **ptr)
{
	t_light	*l;

	l = (t_light *)malloc(sizeof(t_light));
	if (!l)
		return (0);
	*ptr = (void *)l;
	return (1);
}

int	alloc_sphere(void **ptr)
{
	t_sp	*sp;

	sp = (t_sp *)malloc(sizeof(t_sp));
	if (!sp)
		return (0);
	*ptr = (void *)sp;
	return (1);
}

int	alloc_plane(void **ptr)
{
	t_pl	*pl;

	pl = (t_pl *)malloc(sizeof(t_pl));
	if (!pl)
		return (0);
	*ptr = (void *)pl;
	return (1);
}

int	alloc_cylinder(void **ptr)
{
	t_cy	*cy;

	cy = (t_cy *)malloc(sizeof(t_cy));
	if (!cy)
		return (0);
	*ptr = (void *)cy;
	return (1);
}

int	alloc_cone(void **ptr)
{
	t_cn	*cn;

	cn = (t_cn *)malloc(sizeof(t_cn));
	if (!cn)
		return (0);
	*ptr = (void *)cn;
	return (1);
}
