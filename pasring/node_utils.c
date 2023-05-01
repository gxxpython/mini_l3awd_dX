/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:12:21 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/01 23:23:14 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_cmd	*lstnew_cmd(cmd_pipe *cmds)
{
	 t_cmd	*s1;

	s1 = (t_cmd *)malloc(sizeof( t_cmd));
	if (!s1)
		return (NULL);
	s1->cmd = cmds->args[0];
	s1->args = fill_arg(cmds->args);
	s1->list_of_red = my_red(cmds->reder);
	s1->next = NULL;
	return (s1);
}
void	lstadd_back_cmd( t_cmd **lst,  t_cmd *new)
{
	t_cmd	*ptr;

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

void	ft_lstadd_back1(cmd_pipe **lst, cmd_pipe *newnode)
{
	cmd_pipe	*start;

	start = *lst;
	if (*lst)
	{
		while (start->next)
			start = start->next;
		start->next = newnode;
	}
	else
		*lst = newnode;
}

cmd_pipe* cmd_new()
{
	cmd_pipe *cmd = (cmd_pipe*)malloc(sizeof(cmd_pipe));
	cmd->next = NULL;
	cmd->args = NULL;
	cmd->reder = NULL;
	return (cmd);
}

t_redirect  *new_nodered(int red, char *lim ,int her_ex ,char *file)
{
    t_redirect *node;
    node = malloc(sizeof(t_redirect));
    node->my_redirect = red;
	node->here_lim =  lim;
	node->here_doc_expand = her_ex;
	node->filename = file;
    node->next = NULL;
	return node;
}