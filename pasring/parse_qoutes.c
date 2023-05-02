/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:09:24 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/02 23:18:21 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
void	del_node2(t_elm **head)
{
	t_elm	*temp;

	if (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}
char	*parse_quotes2(t_elm *ptr1, enum t_token type,enum t_token type2)
{
	char *str;
	str = ft_strdup("");
	t_elm *ptr;
	ptr = ptr1;
	if (ptr->prev && ptr->prev->type == TEMP)
	{
		str = ft_strjoin(str,ptr->prev->content);
		//del_node2(&(*ptr)->prev);
	}

	ptr = ptr->next;
	ptr->type = type2;
	while (ptr && ptr->type != WHITE_SPACE)
	{
		while(ptr->type == type )
			ptr = ptr->next;
		if (!ptr || ptr->type == WHITE_SPACE)
			break;
		str = ft_strjoin(str,ptr->content);
		ptr->type = type2;
		ptr = ptr->next;
	}

	// if (ptr)
	// {
	// 	ptr->type = type2;
	// 	ptr = ptr->next;
	// }
	
	return (str);
}

char	*parse_quotes(t_elm **ptr, enum t_token type)
{
	char *str;
	str = ft_strdup("");
	if ((*ptr)->prev && (*ptr)->prev->type == TEMP)
	{
		str = ft_strjoin(str,(*ptr)->prev->content);
		//del_node2(&(*ptr)->prev);
	}
	// printf("%s\n",(*ptr)->prev->content);
	*ptr = (*ptr)->next;
	while (*ptr &&   (*ptr)->type != WHITE_SPACE)
	{
		while((*ptr)->type == type )
			*ptr = (*ptr)->next;
		if (!*ptr || (*ptr)->type == WHITE_SPACE)
			break;
		str = ft_strjoin(str,(*ptr)->content);
		*ptr = (*ptr)->next;
	}
	return (str);
}

void	count_quotes_redir_args(t_elm **elem, enum t_token type, int *i)
{
	if (type == DOUBLE_QUOTE || type == QOUTE)
	{
		(*elem) = (*elem)->next;
		while ((*elem) && (*elem)->type != type)
			(*elem) = (*elem)->next;
		(*i)++;
	}
	else if (is_redir(type))
	{
		while ((*elem)->type != WORD && (*elem)->type != ENV)
			(*elem) = (*elem)->next;
		(*elem) = (*elem)->next;
	}
}