#ifndef EVENT_HANDLER_H
# define EVENT_HANDLER_H
#include "event_handler.h"
#include "event_transformation.h"
#include "exit.h"
#include "intersect_world.h"
#include "ray.h"
#include "viewport.h"

int	exit_handler(t_thread_param *param);
int	key_press_handler(int code, t_thread_param *param);
int	mouse_handler(int button, int x, int y, t_thread_param *param);
#endif