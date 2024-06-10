/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:50 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:51 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_BONUS_H
# define LINKED_LIST_BONUS_H
# include "structure_bonus.h"

int		alloc_new_node(t_node **node, int index);
void	append_node(t_node **lst, t_node *new);
t_node	*get_last_node(t_node *list);
void	clear_list(t_node **lst);
#endif
