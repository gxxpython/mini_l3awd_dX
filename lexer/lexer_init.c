/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:24:40 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/01 23:23:52 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int env_check(t_list *token,char *str,enum t_state *state)
{
    int i = 1;
    while (is_alpha(str[i]) && str[i] != '\n' && str[i] != '\0')
        i++;
    add_link(token,new_elem(str,i,ENV,*state));
    return i;
}

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
    else if (line[i] == '$')
        i+=env_check(token, line ,state);
	else if (line[i] == '<' || line[i] == '>')
        i+=check_operator(token, line, i, state);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// void print_tokens(t_list *token)
// {
//     const char *token_names[] = {
//     "WORD",
//     "WHITE_SPACE",
//     "QOUTE",
//     "DOUBLE_QUOTE",
//     "ENV",
//     "PIPE_LINE",
// 	"IN_RED",
// 	"OUT_RED",
// 	"MORE_RED",
// 	"LESS_RED",};
//     const char *token_state[] = {
// 	    "GENERAL",
//         "IN_QUOTE",
//         "IN_DQUOTE",
//     };
//     enum t_state state;
//     t_elm *curr = token->head;
//     while (curr)
//     {
//         printf("%d %d\n", curr->type, curr->state);
//         printf("content %s | type %s | state = %s\n",curr->content,token_names[curr->type + 1],token_state[curr->state]);
//         curr = curr->next;
//     }
// }

// int main(void)
// {
//     char *line;
//     t_list *token;

//     rl_bind_key('\t', rl_complete);
//     while ((line = readline("> ")))
//     {
//         token = lexer(line);
//         if (token)
//         {
//             print_tokens(token);
//             free(token);
//         }
//         free(line);
//     }
//     return (0);
// }