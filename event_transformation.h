/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_transformation.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:16 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:17 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_TRANSFORMATION_H
# define EVENT_TRANSFORMATION_H
# include "structure.h"
# include "constant.h"

void	rotate_object(t_thread_param *param, int keycode);
void	translate_object(t_thread_param *param, int keycode);
void	resize_diameter(t_thread_param *param, int code);
void	resize_height(t_thread_param *param, int code);
void	select_non_selectable(t_thread_param *param, int code);
#endif
