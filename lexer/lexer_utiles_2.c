/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utiles_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:34:31 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/03 18:34:46 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	get_env_var(t_list *tokens, char *str, enum t_state state)
{
	int	i;

	i = 1;
	if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	else
		while (is_alpha(str[i]) && str[i] != '\n' && str[i] != '\0')
			i++;
	add_link(tokens, new_elem(str, i, ENV, state));
	return (i);
}

int env_check(t_list *token,char *str,enum t_state *state)
{
    int i = 1;
	while (is_alpha(str[i]) && str[i] != '\n' && str[i] != '\0')
        i++;
	add_link(token,new_elem(str,i,ENV,*state));
	return i;
}

int env_white(t_list *token,char *str,enum t_state *state)
{
    int i = 1;
	while (is_alpha(str[i]) && str[i] != '\n' && str[i] != '\0')
        i++;
	add_link(token,new_elem(str,i,WORD,*state));
	return i;
}

int env_signe(t_list *token,char *str,enum t_state *state)
{
    int i = 1;
	while (!ft_isalpha(str[i]) && str[i] != ' ' && str[i] != '$')
		i++;
	add_link(token, new_elem(str, i, ENV, *state));
	return i;
}