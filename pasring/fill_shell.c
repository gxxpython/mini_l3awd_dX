/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:48:22 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/01 23:22:50 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char **fill_arg(char **src) 
{
   int i = 1;
	int j = 0;
	char **dst;
	if(!src[0])
		return NULL;
	while (src[i])
		i++;
	dst = malloc(i * (sizeof(char *) + 1));
	i = 1;
    while (src[i] != NULL) {
		
		dst[j] = ft_strdup(src[i]);
        i++;
		j++;
    }
    dst[j] = NULL;
	return dst;
}

void fille_cmd(t_cmd **fcmd,cmd_pipe *full_cmd)
{
	*fcmd = NULL;
	while (full_cmd)
	{
		lstadd_back_cmd(fcmd,lstnew_cmd(full_cmd));
		full_cmd = full_cmd->next;
	}
}