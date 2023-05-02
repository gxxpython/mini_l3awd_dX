/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:10:07 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/02 23:10:06 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"
void set_red(t_cmd *cmd)
{
	t_redirect *red;
	cmd->in_fd = 0;
	cmd->out_fd = 1;
	red = cmd->list_of_red;
	while (red)
	{
		if (red->my_redirect == 9)
		{
			cmd->out_fd = open(red->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		if (red->my_redirect == 10)
		{
			cmd->out_fd = open(red->filename, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
		if (red->my_redirect == 8)
		{
			cmd->in_fd = open(red->filename, O_RDONLY);
		}
		if (red->my_redirect == 7)
		{
			
			cmd->in_fd =cmd->here_doc;
		}
		red = red->next;
	}

}
void set_her_doc(t_cmd *cmds)
{
	t_redirect *red;
	red = cmds->list_of_red;
	while (red)
	{
		if (red->my_redirect == 7)
		{
			printf("%s\n",red->here_lim);
			cmds->here_doc = her_doc(red);
		}
		red = red->next;
	}
}
int her_doc(t_redirect *red)
{
	char *input;
	int fd_pipe[2];
	
	if (pipe(fd_pipe) == -1)
		exit(1);
	int pid;
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			input = readline(">");
			if (ft_strcmp(input, red->here_lim) == 0)
				break;
			close(fd_pipe[0]);
			ft_putendl_fd(input,fd_pipe[1]);
		}
	close(fd_pipe[1]);

	exit(1);
	}
	waitpid(pid,NULL,0);
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}
