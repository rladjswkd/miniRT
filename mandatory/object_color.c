/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:43 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:43 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "constant.h"
#include "object_pattern.h"

static t_rgb	get_sp_rgb(void *object)
{
	t_sp	*sp;

	sp = object;
	return (sp->rgb);
}

static t_rgb	get_pl_rgb(void *object)
{
	t_pl	*pl;

	pl = object;
	return (pl->rgb);
}

static t_rgb	get_cy_rgb(void *object)
{
	t_cy	*cy;

	cy = object;
	return (cy->rgb);
}

t_rgb	get_obj_rgb(t_obj obj, t_vec lighting)
{
	t_rgb			ret;
	static t_rgb	(*fp[3])(void *) = {
		get_sp_rgb, get_cy_rgb, get_pl_rgb};

	ret = (*fp[obj.type - 1])(obj.object);
	return ((t_rgb){
		(int)(lighting.x * ret.r),
		(int)(lighting.y * ret.g),
		(int)(lighting.z * ret.b)
	});
}
