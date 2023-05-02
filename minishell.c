/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:09:33 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/02 17:36:09 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"
void signal_handler(int signum)
{
   printf("Received signal %d\n", signum);
}
int  cheackis_buil(char *cmd)
{
        if (!ft_strcmp(cmd,"env"))
            return (1);
        if (!ft_strcmp(cmd,"unset"))
            return (1);
        if (!ft_strcmp(cmd,"export"))
            return (1);
        if (!ft_strcmp(cmd,"cd"))
            return (1);
        if (!ft_strcmp(cmd,"pwd"))
            return (1); 
        if (!ft_strcmp(cmd,"exit"))
            return (1);
        if (!ft_strcmp(cmd,"echo"))
            return (1);
        return (0);
}
void exucute_builtine(t_global *all,t_cmd *cmds)
{
      if (!ft_strcmp(cmds->cmd,"env"))
            cmd_env(all->env_list,cmds->out_fd);
        if (!ft_strcmp(cmds->cmd,"unset"))
            cmd_unset(cmds->args,&all->env_list);
        if (!ft_strcmp(cmds->cmd,"export"))
            cmd_export(&all->env_list,cmds->args,cmds->out_fd);
        if (!ft_strcmp(cmds->cmd,"cd"))
            cmd_cd(cmds->args,&all->env_list); 
        if (!ft_strcmp(cmds->cmd,"pwd"))
            cmd_pwd(cmds->out_fd,1);  
        if (!ft_strcmp(cmds->cmd,"exit"))
            cmd_exit(cmds->args);
        if (!ft_strcmp(cmds->cmd,"echo"))
            cmd_echo(cmds->args,cmds->out_fd);
}
void copy_to(char *env,char **dst,size_t i)
{
    int j;
    j = 0;
    while (env[i] != '=' && env[i] != '+' && env[i])
    {
        dst[0][i] = env[i];
        i++;
    }
    dst[0][i++] = '\0';
    if (!env[i - 1])
    {
        dst[1] = NULL;
        return ;
    }
    if (env[i] == '=')
        i++;
    if (!env[i - 1])
        i--;
    while (env[i])
    {
        dst[1][j] = env[i];
        i++;
        j++;
    }
    dst[1][j] = '\0';
}
char **var_val(char *env)
{
    size_t i;
    i = 0;
    char **dst;
    while (env[i] && env[i] != '=' && env[i] != '+')
        i++;
    dst = malloc(sizeof(char*) * 2);
    dst[0] =  malloc(i + 1);
    dst[1] = malloc((ft_strlen(env) - i) + 1);
    i = 0;
    copy_to(env,dst,i);
    return dst;
}
void store_env(t_env **envi,char **env)
{
    int i;
    t_env *ptr;
    ptr = *envi;
    i = 0;
    while (env[i])
    {
        ft_lstadd_back_mini(envi,ft_lstnew_mini(env[i])); 
        i++;
    }
    
    if (!get_env(*envi,"OLDPWD",NULL))
    {
        ft_lstadd_back_mini(envi,ft_lstnew_mini("OLDPWD"));
    }
    else
    {
        del_node(envi,"OLDPWD");
        ft_lstadd_back_mini(envi,ft_lstnew_mini("OLDPWD"));
    }
}

int main(int ac, char **av,char **env)
{
    (void)ac;
    (void)av;
    t_global	all;
    char* input;
    int i = 0;

    
    glob_exit = EXIT_SUCCESS;
    store_env(&all.env_list,env);
    while ((input = readline("minishell>")) != NULL) 
    {
        all.all_cmd = NULL;
        add_history(input);
        if(!lunch_shell(input, &all))
         {
             execution_mini(&all,env);
         }
//------------------------------khasnin awal haja hol ga3 rederiction w outfile 
        
        free(input);
        i++;
    }
}