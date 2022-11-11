#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include "structure.h"

int		alloc_new_node(t_node **node, int index);
void	append_node(t_node **lst, t_node *new);
t_node	*get_last_node(t_node *list);
void	clear_list(t_node **lst);
#endif