/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:10:07 by abouassi          #+#    #+#             */
/*   Updated: 2023/04/16 02:17:05 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"



void	child1(int *pipefd, char *cmd1, char **env ,int fd_her)
{
	char	*path;
	char	**cmdop;
	//int		fd1;

	//fd1 = open(file1, O_RDONLY);
	//check_error(file1, fd1);
	check_error("ERR_DUP 1", dup2(fd_her, STDIN_FILENO));
	close(fd_her);
	check_error("error :", dup2(pipefd[1], STDOUT_FILENO));
	close(pipefd[0]);
	close(pipefd[1]);
	cmdop = ft_split(cmd1, ' ');
	path = my_path(cmdop[0], env);
	if (!path)
	{
		check_error2(cmdop[0]);
		free_all(cmdop, NULL);
		exit(1);
	}
	if (execve(path, cmdop, env) == -1)
	{
		perror("ERR_EXECVE CMD 1:");
		free_all(cmdop, path);
		exit(1);
	}
}

void	child2(int fd_out, int *pipefd, char *cmd2, char **env)
{
	char	*path;
	char	**cmdop;
	//int		fd2;

	// fd2 = open(file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	// check_error(file2, fd2);
	check_error("ERR_DUP 2", dup2(fd_out, STDOUT_FILENO));
	check_error("error :", dup2(pipefd[0], STDIN_FILENO));
	close(pipefd[0]);
	cmdop = ft_split(cmd2, ' ');
	path = my_path(cmdop[0], env);
	if (!path)
	{
		check_error2(cmdop[0]);
		free_all(cmdop, NULL);
		exit(1);
	}
	if (execve(path, cmdop, env) == -1)
	{
		perror("ERR_EXECVE CMD 2 :");
		free_all(cmdop, path);
		exit(1);
	}
}

void	pipex( t_cmd *cmds, char **env,int fd_her)
{
	int	pid;
	int	p;
	int	pipefd[2];
	
	
	
		
	check_error("ERR_PIPE :", pipe(pipefd));
	pid = fork();
	check_error("fork 1", pid);
	if (pid == 0)
	{
		
		child1( pipefd, cmds->cmd, env,fd_her);
	}
	close(fd_her);
	close(pipefd[1]);
	p = fork();
	check_error("fork 2", p);
	if (p == 0)
	{
		child2( cmds->out_fd,pipefd, cmds->cmd, env);
	}
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
	waitpid(p, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	char *input;
	int fd_pipe[2];
	(void)env;
	(void)argc;

	if (pipe(fd_pipe) == -1)
		return (1);
	int pid;
	pid = fork();
	if (pid == 0)
	{
	
		if (!ft_strcmp(argv[1],"here_doc"))
		{
			while (1)
			{
				input = readline("heredoc>");
				if (ft_strcmp(input, argv[2]) == 0)
					break;
				close(fd_pipe[0]);
				ft_putstr_fd(input,fd_pipe[1]);
			}
			close(fd_pipe[1]);
		}
		exit(1);
	}
	waitpid(pid,NULL,0);
	close(fd_pipe[1]);
	pipex(argv,env,fd_pipe[0]);
}
