/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:08 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:12 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_BONUS_H
# define EVENT_HANDLER_BONUS_H
# include "event_transformation_bonus.h"
# include "exit_bonus.h"
# include "intersect_world_bonus.h"
# include "ray_bonus.h"
# include "viewport_bonus.h"

int	exit_handler(t_thread_param *param);
int	key_press_handler(int code, t_thread_param *param);
int	mouse_handler(int button, int x, int y, t_thread_param *param);
#endif
