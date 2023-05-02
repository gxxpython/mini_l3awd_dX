/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:24 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/02 00:46:11 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	parse_word(t_elm **ptr, char **args, int *i)
{
	//printf()
	args[*i] = ft_strndup((*ptr)->content, (*ptr)->len);
	(*i)++;
	(*ptr) = (*ptr)->next;
}

int	parse_cmd_act(t_elm *ptr,cmd_pipe **cmds)
{
	cmd_pipe *full_cmd;
	t_elm *ptr1;
	int i;
	i = 0;
	ptr1 = ptr;
	while (ptr1)
	{
		if (ptr1->type == LESS_RED)
			{
				ptr1 = ptr1->next;
				if (ptr1->next)
				{
					ptr1 = ptr1->next;
					while (ptr1->type == WHITE_SPACE)
						ptr1 = ptr1->next;
					if (ptr1->type == DOUBLE_QUOTE || ptr1->type == QOUTE)
					{
						if (ptr1->prev && ptr1->prev->type == WORD)
							ptr1->prev->type = TEMP;
						if (!ptr1->next->next || ptr1->next->type == WHITE_SPACE)
							ptr1->prev->type = WORD;
						ptr1->content = parse_quotes2(ptr1,ptr1->type,LIMIT);
						//printf("%s\n", ptr1->content);
						ptr1->type  = LIMIT;
					}
					else
						ptr1->type  = LIMIT;
					if (!ptr1)
						break;
				}
			}
			else if(ptr1->type == IN_RED || ptr1->type == MORE_RED|| ptr1->type == OUT_RED )
			{
				if (ptr1->type == MORE_RED)
					ptr1 = ptr1->next;
				if (ptr1->next)
				{
					ptr1 = ptr1->next;
					while (ptr1->type == WHITE_SPACE)
						ptr1 = ptr1->next;
					if (ptr1->next && ptr1->type == WORD &&( ptr1->next->type == DOUBLE_QUOTE || ptr1->next->type == QOUTE) )
					{
						ptr1 = ptr1->next;
					}
					
					if (ptr1->type == DOUBLE_QUOTE || ptr1->type == QOUTE)
					{
						printf("jhjhhh\n");
						if (ptr1->prev && ptr1->prev->type == WORD)
							ptr1->prev->type = TEMP;
						if (!ptr1->next->next || ptr1->next->type == WHITE_SPACE)
							ptr1->prev->type = WORD;
						ptr1->content = parse_quotes2(ptr1,ptr1->type,FILE_NAME);
						printf("%s\n", ptr1->content);
						ptr1->type  = FILE_NAME;
					}
					else
						ptr1->type  = FILE_NAME;
					if (!ptr1)
						break;
				}
			}
			// else if (ptr1->type == DOUBLE_QUOTE || ptr1->type == QOUTE)
			// {
			// 	if (ptr1->prev && ptr1->prev->type == WORD)
			// 		ptr1->prev->type = TEMP;
			// 	if (!ptr1->next->next || ptr1->next->type == WHITE_SPACE)
			// 		ptr1->prev->type = WORD;
			// }
			ptr1 = ptr1->next;
	}
	full_cmd = *cmds;
	int size =  count_args(ptr);
	full_cmd->args = malloc((sizeof(char *)) * (size + 1));
	full_cmd->reder = red_list(ptr);
	while (ptr)
	{
		if (ptr->type == PIPE_LINE)
		{
			full_cmd->args[i] = NULL;
			full_cmd->next = cmd_new();
			full_cmd = full_cmd->next;
 			i = 0;
			ptr = ptr->next;
			size =  count_args(ptr);
			full_cmd->args = malloc(sizeof(char *) * (size + 1));
			full_cmd->reder = red_list(ptr);
			if (full_cmd->next)
			{
				full_cmd = full_cmd->next;
				full_cmd->args = malloc(sizeof(char *) * (size + 1));
				full_cmd->reder = red_list(ptr);
				ft_lstadd_back1(cmds,full_cmd);
			}
		}
		
		else if (ptr->type == WORD)
		{
			//printf("------%s\n\n\n",ptr->content);
			parse_word(&ptr, full_cmd->args, &i);
		}
		else if (ptr->type == DOUBLE_QUOTE || ptr->type == QOUTE)
		{
			full_cmd->args[i] = parse_quotes(&ptr, ptr->type);
			//printf("{%s}\n",full_cmd->args[i]);
			if (full_cmd->args[i])
				(i)++;
		}
		else 
		{
			(ptr) = (ptr)->next;
		}
	}
	//printf("i :%d\n",i);
	//printf("i :%p\n",full_cmd->args);
	//printf("i :%d\n");
	full_cmd->args[i] = NULL;
	return (EXIT_SUCCESS);
}

void parse_cmd(t_elm **ptr,t_cmd **fcmd)
{
	int				size;
	cmd_pipe		*full_cmd;
	//cmd_pipe *ptr1;
	
	//fcmd->list_of_red = malloc(sizeof(t_redirect));
	full_cmd = malloc(sizeof(cmd_pipe));
	full_cmd->next = NULL;
	size = count_args((*ptr));
	//printf("==%d\n",size);
	if (parse_cmd_act(*ptr, &full_cmd) == EXIT_FAILURE)
		return ;
	fille_cmd(fcmd,full_cmd);
	// t_cmd		*ptrr = *fcmd;
	// while (ptrr)
	// {
	// 	printf("cmd == %s\n",ptrr->cmd);
	// 	printf("arg == %s\n",ptrr->args[0]);
	// 	while (ptrr->list_of_red)
	// 	{
	// 		printf("red == %d\n",ptrr->list_of_red->my_redirect);
	// 		printf("file == %s\n",ptrr->list_of_red->filename);
	// 		printf("lim == %s\n",ptrr->list_of_red->here_lim);
	// 		printf("exp == %d\n",ptrr->list_of_red->here_doc_expand);
	// 		ptrr->list_of_red = ptrr->list_of_red->next;
	// 	}
	// 	ptrr = ptrr->next;
	// }
	
}

void parse1(t_elm *ptr,t_global *all)
{
    // cmd_pipe *con;
    // con = NULL;
	all->all_cmd = malloc(sizeof(t_cmd));
	parse_cmd(&ptr,&all->all_cmd);
	// if (!con)
	// 	return (EXIT_FAILURE);
    // return(EXIT_SUCCESS);
}