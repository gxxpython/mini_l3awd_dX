/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:32:35 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/01 23:23:47 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int ft_check_emp(t_list *list)
{
    if (list->head == NULL)
        return 1;
    else
        return 0;
}

void    quotes(t_list *tokens, char *str, enum t_state *state, int flag)
{
	enum t_state    e_state;
	enum t_token    e_type;

	if (flag == 1)
	{
		e_state = IN_QUOTE;
		e_type = QOUTE;
	}
    else
	{
		e_state = IN_DQUOTE;
		e_type = DOUBLE_QUOTE;
	}
	if (*state == GENERAL)
	{
		add_link(tokens, new_elem(str, 1, e_type, *state));
		*state = e_state;
	}
	else if (*state == e_state)
	{	
		*state = GENERAL;
		add_link(tokens, new_elem(str, 1, e_type, *state));
	}
	else
        add_link(tokens, new_elem(str, 1, e_type, *state));
}

int	is_char(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '$' || is_space(c) || c == '\n' || c == '\0');
}

int	is_alpha(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
