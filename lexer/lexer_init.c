/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:24:40 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/03 18:39:09 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int check_operator(t_list *token,char *str,int i,enum t_state *state)
{
    int j;

    j = i;
    if (str[i] == '<')
    {
        if (str[i + 1] == '<')
            add_link(token,new_elem(str + (i++), 2,LESS_RED, *state));
        else
            add_link(token,new_elem(str + (i++), 1,IN_RED, *state));
    }
    else if (str[i] == '>')
    {
        if (str[i + 1] == '>')
            add_link(token,new_elem(str + (i++), 2,MORE_RED, *state));
        else
            add_link(token,new_elem(str + (i++), 1,OUT_RED, *state));
    }
    return (i - j);
}

int	toke_init(t_list *token,char *line,int i,enum t_state *state)
{
	if (!is_char(line[i]))
		i += ft_word(token,line + i,*state);
	else if (line[i] == '\'')
		quotes(token, line + (i++), state, 1);
	else if (line[i] == '\"')
		quotes(token, line + (i++), state, 2);
	else if (line[i] == '|')
		add_link(token, new_elem(line + (i++), 1, PIPE_LINE, *state));
	else if (line[i] == ' ')
		add_link(token, new_elem(line + (i++), 1, WHITE_SPACE, *state));
	else if (line[i] == '<' || line[i] == '>')
        i+=check_operator(token, line, i, state);
	else if (line[i] == '$'  && line[i + 1] != '?')
	{
		if (line[i + 1] == ' ')
		{
			i+=env_white(token, line + i, state);
		}
		else
			i += get_env_var(token, line + i, *state);
	}
	else if(line[i] == '$'  && line[i + 1] == '?')
	{
		i+=env_signe(token, &line[i] ,state);
	}
	return (i);
}

t_list *lexer(char *line)
{
	int i;
	t_list *token;
	enum t_state state;

	i = 0;
	state = GENERAL;
	token = in_list(); // Pass any required arguments here
	if (token)
	{
		while (line[i])
		{
			i = toke_init(token,line,i,&state);
		}
	}
	return (token);
}
