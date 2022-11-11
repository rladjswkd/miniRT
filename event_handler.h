/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:08 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:12 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_H
# define EVENT_HANDLER_H
# include "event_handler.h"
# include "event_transformation.h"
# include "exit.h"
# include "intersect_world.h"
# include "ray.h"
# include "viewport.h"

int	exit_handler(t_thread_param *param);
int	key_press_handler(int code, t_thread_param *param);
int	mouse_handler(int button, int x, int y, t_thread_param *param);
#endif
