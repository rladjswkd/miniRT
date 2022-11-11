/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_essential.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:29 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:30 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_ESSENTIAL_H
# define SET_ESSENTIAL_H
# include "structure.h"

int	set_rgb(char *rgb_str, t_rgb *rgb);
int	set_coordinate(char *coord_str, t_coord *coord);
int	set_ambient(char **info, int cnt, t_world *world);
int	set_light(char **info, int cnt, t_world *world);
int	set_camera(char **info, int cnt, t_world *world);
#endif
