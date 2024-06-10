/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:43 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:44 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "structure.h"
#include "get_next_line.h"
#include "set_world.h"
#include "string_utils.h"

int	open_file(char *path)
{
	int	fd;
	int	len;

	fd = -1;
	len = ft_strlen(path);
	if (path[len - 3] == '.' && path[len - 2] == 'r' && path[len - 1] == 't')
		fd = open(path, O_RDONLY);
	return (fd);
}

int	read_file(int fd, t_world *world)
{
	char		*line;
	int			flag;
	static int	mask = 0;

	flag = 1;
	while (flag)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		if (line[0] != '\0')
			flag = set_world(line, world, &mask);
		free(line);
	}
	if (!flag || !(mask & 1 << 0 && mask & 1 << 1 && mask & 1 << 2))
		return (0);
	return (1);
}
