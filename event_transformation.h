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