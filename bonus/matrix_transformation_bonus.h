/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation_bonus.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:05 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:07 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_TRANSFORMATION_BONUS_H
# define MATRIX_TRANSFORMATION_BONUS_H
# include "structure_bonus.h"

t_mat	get_rx_to_z(t_vec forward);
t_mat	get_ry_to_z(t_vec forward);
t_mat	mat_translation(double dx, double dy, double dz);
t_mat	rotate_latitude(int angle);
t_mat	rotate_longitude(int angle);
#endif
