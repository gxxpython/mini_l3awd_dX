/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 08:27:13 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/01 23:23:39 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_redirect *my_red(t_redir *red)
{
	t_redirect *ptr;
	ptr  = NULL;
	while (red)
	{
		if ( red->type == LESS_RED)
		{
			lstadd_back_red2(&ptr,new_nodered(HEREDOC,red->arg,0,NULL));
		}
		else if ( red->type == IN_RED)
		{
			lstadd_back_red2(&ptr,new_nodered(LESS,NULL,0,red->arg));
		}
		else if ( red->type == OUT_RED)
		{
			lstadd_back_red2(&ptr,new_nodered(GREAT,NULL,0,red->arg));
		}
		else if ( red->type == MORE_RED)
		{
			lstadd_back_red2(&ptr,new_nodered(EXPAND,NULL,0,red->arg));
		}

		red = red->next;
	}
	return ptr;
}

t_redir *red_list(t_elm *ptr)
{
	int temp;
	temp = 0;
	t_redir *list_red;
	list_red = NULL;
	while (ptr && ptr->type != PIPE_LINE)
	{
		if(ptr->type == LESS_RED)
        {
			while (ptr->type != LIMIT)
				ptr = ptr->next;
			lstadd_back_red(&list_red,lstnew_red(ptr,LESS_RED));
		}
		else if (ptr->type == IN_RED || ptr->type == MORE_RED|| ptr->type == OUT_RED )
		{
			temp = ptr->type;
			while (ptr->type != FILE_NAME)
				ptr = ptr->next;
			lstadd_back_red(&list_red,lstnew_red(ptr,temp));
		}
		ptr = ptr->next;
	}
	return list_red;
}