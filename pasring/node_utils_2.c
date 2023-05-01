/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:18:32 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/01 23:23:11 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	lstadd_back_red2( t_redirect  **lst,  t_redirect  *new)
{
	t_redirect 	*ptr;

	if (lst && new)
	{
		if (*lst)
		{
			ptr = *lst;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

void	lstadd_back_red( t_redir **lst,  t_redir *new)
{
	t_redir	*ptr;

	if (lst && new)
	{
		if (*lst)
		{
			ptr = *lst;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new;
		}
		else
			*lst = new;
	}
}
t_redir	*lstnew_red(t_elm *ptr,int type)
{
	 t_redir	*node;

	node = (t_redir *)malloc(sizeof( t_redir));
	if (!node)
		return (NULL);
	node->arg = ptr->content;
	node->type = type;
	node->next = NULL;
	return (node);
}