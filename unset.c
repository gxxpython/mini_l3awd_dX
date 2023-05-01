/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:54:12 by abouassi          #+#    #+#             */
/*   Updated: 2023/04/17 02:28:30 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

int check_key2(char *env)
{
    int i;
    i = 0;
    if ((env[i] >= 'a' && env[i] <= 'z') || (env[i] >= 'A' && env[i] <= 'Z') || env[i] == '_')
    {
        while (env[i])
        {
            if ((env[i] >= 'a' && env[i] <= 'z') || (env[i] >= 'A' && env[i] <= 'Z') || (env[i] >= '0' && env[i] <= '9') || env[i] == '_')
            {
                i++; 
            }
            else
                return(1);
        }
        
        return(0);
    }
    return (1);
    
}
void cmd_exit(char **str)
{
    printf("exit\n");
    if (!str[0])
        exit(0);
    if(str[0] && !str[1])
    {
    //    p_error("exit: ");
    //    p_error(str[0]);
    //    p_error(": numeric argument required\n");
       exit(ft_atoi(str[0]));
    }
    else
    {
       p_error("exit");
       p_error(": too many arguments\n");
    }
}
void cmd_unset(char** arg,t_env **env)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if(check_key2(arg[i]))
        {
            p_error("unset: '");
            p_error(arg[i]);
            p_error("': not a valid identifier\n");
        }
        else
            del_node(env,arg[i]);
        i++;
    } 
}