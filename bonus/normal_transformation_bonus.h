/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_transformation_bonus.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:12 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:13 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMAL_TRANSFORMATION_BONUS_H
# define NORMAL_TRANSFORMATION_BONUS_H
# include "structure_bonus.h"

t_vec	rotate_normal(t_vec vec, t_mat op);
t_vec	get_bump_norm(t_vars *vars, t_obj obj, t_vec p, t_vec n);
#endif
