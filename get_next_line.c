/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:49:15 by gyepark           #+#    #+#             */
/*   Updated: 2021/12/08 13:40:33 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
static char	*free_builder_data(t_builder *builder)
{
	free(builder->data);
	builder->data = 0;
	return (0);
}

static int	read_file(int fd, t_builder *builder)
{
	int		count;
	char	buffer[42];
	char	*temp_data;

	while (builder->index == -1)
	{
		count = read(fd, buffer, 42);
		if (count < 1)
			return (count);
		temp_data = concat_data(builder->data, buffer, builder->len, count);
		if (!temp_data)
			return (-1);
		builder->data = temp_data;
		builder->index = find_new_line(builder->data, builder->len, count);
		builder->len += count;
	}
	return (1);
}

static char	*build_line(t_builder *b)
{
	char	*line;
	char	*temp_data;

	if (b->index == -1)
	{
		if (b->len == 0)
			return (0);
		line = (char *)malloc(sizeof(char) * (b->len + 1));
		if (!line)
			return (0);
		copy_data(line, b->data, b->len + 1, 1);
		b->len = 0;
		return (line);
	}
	line = get_part(b->data, 0, b->index, 1);
	if (!line)
		return (0);
	temp_data = get_part(b->data, b->index + 1, b->len - (b->index + 1), 0);
	if (!temp_data)
		return (0);
	free(b->data);
	b->data = temp_data;
	b->len -= (b->index + 1);
	b->index = find_new_line(b->data, 0, b->len);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_builder	builder = {0, 0, -1};
	int					read_status;
	char				*line;

	if (fd < 0)
		return (0);
	read_status = read_file(fd, &builder);
	if (read_status == -1)
		return (free_builder_data(&builder));
	line = build_line(&builder);
	if (line == 0)
		return (free_builder_data(&builder));
	return (line);
}
