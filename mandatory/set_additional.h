/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_additional.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:25 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:25 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_ADDITIONAL_H
# define SET_ADDITIONAL_H
# include "structure.h"

int	set_plane(char **info, int cnt, t_world *world);
int	set_sphere(char **info, int cnt, t_world *world);
int	set_cylinder(char **info, int cnt, t_world *world);
#endif
