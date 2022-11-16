/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_processor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:21 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:21 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_PROCESSOR_H
# define FILE_PROCESSOR_H
# include "structure.h"

int	open_file(char *path);
int	read_file(int fd, t_world *world);
#endif
