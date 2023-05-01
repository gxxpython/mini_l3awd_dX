/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 00:30:41 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/01 23:23:33 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	count_args(t_elm *elem)
{
	t_elm	*tmp;
	int		i;

	i = 0;
	tmp = elem;
	while (tmp && tmp->type != PIPE_LINE)
	{
		if (tmp->type == WORD || tmp->type == ENV)
			i++;
		if (tmp)
			tmp = tmp->next;
	}
    return (i);
}

int	is_redir(enum t_token type)
{
	return (type == IN_RED || type == OUT_RED
		|| type == MORE_RED || type == LESS_RED);
}

t_elm	*skip_spaces(t_elm *ptr)
{
	while (ptr && ptr->type == WHITE_SPACE)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

int	pipe_error(t_elm *ptr)
{
	t_elm	*next;

	next = skip_spaces(ptr->next);
	if (!next || (next->type != WORD && !is_redir(next->type)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	redir_error(t_elm *ptr)
{
	t_elm	*next;
	
	next = ptr;
	if (next->type == MORE_RED || next->type == LESS_RED)
	{
		next = next->next;
	}
	next = skip_spaces(ptr->next);
	if (!next || (next->type != WORD && !is_redir(next->type)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
