/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_excution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:52:34 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/02 17:47:18 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"
void	check_error(char *str, int n)
{
	if (n == -1)
	{
		perror(str);
		exit(1);
	}
}
char **join_op(char *cmd,char **op)
{
	int i;
	int j;
	char **cmdop;
	j = 1;
	i = 0;
	while (op[i])
		i++;
	cmdop = malloc(sizeof(char *) * (i + 2));
	i = 0;
	cmdop[0] = ft_strdup(cmd);
	while (op[i])
	{
		cmdop[j] = ft_strdup(op[i]);
		i++;
		j++;
	}
	cmdop[j] = NULL;
	return cmdop;
}
// void	last_child(t_cmd cmds, char **env,int last_fd)
// {
// 	char	*path;
// 	char	**cmdop;
// 	int		fd2;
// 	int pid ;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(last_fd,0);
// 		close(last_fd);
// 		fd2 = open(file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		dup2(fd2,1);
// 		check_error(file2, fd2);
// 		cmdop = ft_split(cmd2, ' ');
		
// 		path = my_path(cmdop[0], env);
// 		if (!path)
// 		{
// 			check_error2(cmdop[0]);
// 			free_all(cmdop, NULL);
// 			exit(1);
// 		}
// 		if (execve(path, cmdop, env) == -1)
// 		{
// 			perror("ERR_EXECVE CMD 2 :");
// 			free_all(cmdop, path);
// 			exit(1);
// 		}
// 	}
// }
void	first_child(t_global *all,t_cmd *cmds, char **env,int *fd)
{
	char	*path;
	char	**cmdop;
	int		pid;
	pid = fork();
	if(pid == 0)
	{
		if (!cmds->cmd)
		{
			exit(0);
		}
		
		if (cmds->out_fd == 1 && cmds->next)
			dup2(fd[1],1);
		else
			dup2(cmds->out_fd,1);
		close(fd[1]);
		close(fd[0]);
		check_error("ERR_DUP 1", dup2(cmds->in_fd, STDIN_FILENO));
		if (cheackis_buil(cmds->cmd))
		{
			exucute_builtine(all,cmds);
			exit(0);
		}
		
		cmdop = join_op(cmds->cmd,cmds->args);
		path = my_path(cmds->cmd, env);
		if (!path)
		{
			check_error2(cmds->cmd);
			free_all(cmdop, NULL);
			exit(1);
		}
		if (execve(path, cmdop, env) == -1)
		{
			check_error2(cmds->cmd);
			free_all(cmdop, path);
			exit(1);
		}
	}
}
void call_childs( t_global *all,t_cmd *cmds, char **env,int *fd, int last_fd)
{
	char	*path;
	char	**cmdop;
	if (!cmds->cmd)
	{
		exit(0);
	}
	if (cmds->in_fd == 0)
		dup2(last_fd,0);
	else
		dup2(cmds->in_fd,0);
	close(last_fd);
	
	if (cmds->out_fd == 1 && cmds->next)
		dup2(fd[1],1);
	else
		dup2(cmds->out_fd,1);
	close(fd[1]);
	close(fd[0]);
	if (cheackis_buil(cmds->cmd))
	{
		exucute_builtine(all,cmds);
		exit(0);
	}
	cmdop = join_op(cmds->cmd,cmds->args);;
	path = my_path(cmdop[0], env);
	if (!path)
	{
		check_error2(cmds->cmd);
		free_all(cmdop, NULL);
		exit(1);
	}
	if (execve(path, cmdop, env) == -1)
	{
		check_error2(cmds->cmd);
		free_all(cmdop, path);
		exit(1);
	}
}
void cmd_excution(t_global *all, char **env)
{
	int i ;
	int fd[2];
	int pid;
	int	last_fd;
	i = 0;
	t_cmd *cmds;
	last_fd = 0;
	pipe(fd);
	last_fd = fd[0];
	first_child(all,all->all_cmd,env,fd);
	cmds = all->all_cmd->next;
	close(fd[1]);
	while (cmds)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			call_childs(all,cmds,env,fd, last_fd);
		}
		close(last_fd);
		last_fd = fd[0];
		close(fd[1]);
		i++;
		cmds = cmds->next;
	}
	//last_child(cmds, env,last_fd);
	//close(last_fd);
	 while (wait(NULL) != -1);
}