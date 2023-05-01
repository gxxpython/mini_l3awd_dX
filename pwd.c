/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:11:27 by abouassi          #+#    #+#             */
/*   Updated: 2023/04/15 12:33:23 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"
int cheak_n(char *cmd)
{
   int i;
   i = 0;
   if (cmd[i] == '-' && cmd[i + 1] == 'n')
   {
        i++;
        while (cmd[i] == 'n' && cmd[i])
            i++;
        if (!cmd[i])
            return(1);
   }
   return(0);
}
void cmd_echo(char **cmd,int fd)
{
    int i;
    i = 0;
    if (!cmd[i])
        ft_putchar_fd('\n',fd);
    if (cmd[i] && !cheak_n(cmd[i]))
    {
        while (cmd[i])
        {
            ft_putstr_fd(cmd[i],fd);
            i++;
            if (cmd[i])
                ft_putchar_fd(' ',fd);
        }
        ft_putchar_fd('\n',fd);;
    }
    else
    {
        i = 0;
        while (cmd[i] && cheak_n(cmd[i]))
            i++;
        while (cmd[i])
        {
            ft_putstr_fd(cmd[i],fd);
            i++;
            if (cmd[i])
                ft_putchar_fd(' ',fd);
        }
    }
}

char *cmd_pwd(int fd,int k)
{
    char *cwd;
    int i;
    cwd = malloc(10000);
    i = 0;
    // if(str[i] == '-' && str[i + 1] != '\0')
    //     p_error("no option for this command\n"); 
    if (!getcwd(cwd, 10000))
        perror("");
    if (k)
    {
        ft_putendl_fd(cwd,fd);
        free(cwd);   
    }
    else
        return (cwd);
    return NULL;
}