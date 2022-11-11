#ifndef SET_ESSENTIAL_H
# define SET_ESSENTIAL_H
# include "structure.h"

int	set_rgb(char *rgb_str, t_rgb *rgb);
int	set_coordinate(char *coord_str, t_coord *coord);
int	set_ambient(char **info, int cnt, t_world *world);
int	set_light(char **info, int cnt, t_world *world);
int	set_camera(char **info, int cnt, t_world *world);
#endif