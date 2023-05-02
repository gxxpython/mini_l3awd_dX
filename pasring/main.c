/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 08:48:57 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/02 17:34:33 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../Includes/minishell.h"

int	redir_error_2(t_elm *ptr)
{
	t_elm	*next;

	printf("%s",ptr->content);
	next = skip_spaces(ptr->next);
	if (!next || (next->type != WORD && !is_redir(next->type)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int check_redir(t_elm *elem)
{
	if (elem->type == LESS_RED || elem->type == MORE_RED)
	{
		elem = elem->next->next;
		if(!elem)
			return (1);
	}
	else
		elem = elem->next;
	if(elem)
	{
		while (elem && elem->type == WHITE_SPACE )
			elem = elem->next;

		if(!elem)
			return(1);
		if(is_redir(elem->type) || elem->type == PIPE_LINE)
			return (1);
	}
	else
		return (1);
	return (0);
}

t_elm *fix_empty(t_elm *ptr)
{
	ptr->content = ft_strdup("");
	ptr->len = 1;
	ptr->state = GENERAL;
	ptr->type = WORD;
	return (ptr);
}



int	syntax_errors(t_list *list)
{
	t_elm	*ptr;
	ptr = list->head;
	while (ptr)
	{
		if (is_redir(ptr->type))
		{
			if (check_redir(ptr))
				return (write(2,"minishell: syntax error\n",25));
		}
		if (ptr->type == PIPE_LINE)
		{
			if (pipe_error(ptr))
				return (write(2,"minishell: syntax error\n",25));	
		}
		if (ptr->type == DOUBLE_QUOTE || ptr->type == QOUTE)
		{
			if (!check_unclosed_quotes(&ptr, ptr->type))
				return (EXIT_FAILURE);
		}
		if ((ptr->type == DOUBLE_QUOTE && !ptr->next) || (ptr->type == QOUTE && !ptr->next))
		{
			ptr = fix_empty(ptr);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}


int	lunch_shell(char *line,t_global *all)
{
	int error;
	error = 0;
    // while (1)
    // {
	// 	line = readline("\e[1;34m$MINISHELL => \e[1;37m");
	// 	if (ft_strncmp(line, "exit", 4) == 0)
	// 	{
	// 		printf("exit\n");
	// 		exit(1);
	// 	}
	// 	if (ft_strlen(line) > 0)
	// 		add_history(line);
		g_data.lex = lexer(line);
		error =syntax_errors(g_data.lex);
		if (!error)
		{
			parse1(g_data.lex->head,all);
		}
		return (error);
}
// int main(int argc,char **argv,char **envp)
// {
// 	(void)argc;
// 	(void)argv;
//     lunch_shell(envp);
// }