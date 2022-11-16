/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_world.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:34 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:35 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_WORLD_H
# define SET_WORLD_H
# include "structure.h"

int	set_world(char *line, t_world *rt, int *mask);
int	free_splitted(char **splitted, int ret);
#endif
