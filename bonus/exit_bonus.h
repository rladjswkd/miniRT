/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:18 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:19 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_BONUS_H
# define EXIT_BONUS_H
# include "structure_bonus.h"

void	destroy_world(t_world *world);
void	destroy_mlx(t_vars *vars);
void	exit_minirt(char *msg, t_world *world, t_vars *vars,
			t_thread_param *param);
#endif
