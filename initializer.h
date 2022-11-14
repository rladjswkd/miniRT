/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:29 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 20:03:41 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZER_H
# define INITIALIZER_H
# include "structure.h"

void	init_param(t_world *world, t_vars *vars, t_thread_param *param);
void	init_world(t_world *world);
int		init_mlx_pointers(t_vars *vars);
#endif
