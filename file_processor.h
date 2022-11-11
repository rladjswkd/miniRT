#ifndef FILE_PROCESSOR_H
# define FILE_PROCESSOR_H
# include "structure.h"

int	open_file(char *path);
int	read_file(int fd, t_world *world);
#endif