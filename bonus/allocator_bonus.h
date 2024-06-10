/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:57:40 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:57:40 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_BONUS_H
# define ALLOCATOR_BONUS_H

int	alloc_light(void **ptr);
int	alloc_sphere(void **ptr);
int	alloc_plane(void **ptr);
int	alloc_cylinder(void **ptr);
int	alloc_cone(void **ptr);
#endif
