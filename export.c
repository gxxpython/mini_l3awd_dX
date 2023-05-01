/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:38:13 by abouassi          #+#    #+#             */
/*   Updated: 2023/04/14 18:03:29 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"
int ch_join(char *str)
{
    int i;
    i = 0;
    while (str[i] != '+' && str[i] != '=' && str[i])
    {
        i++;
        if (str[i] == '+' && str[i + 1] == '=')
            return (1);
    }
    return(0);
}
int cheak_add(t_env **env,char *str)
{
    t_env *ptr;
    char **va;

    va = var_val(str);
    ptr = *env;
    while (ptr)
    {
        if (!ft_strcmp(ptr->key,va[0]))
        {
            if (ch_join(str))
            {
                ptr->value= ft_strjoin(ptr->value,va[1]); 
            }
            else if(va[1])
                ptr->value = va[1];
            ptr->content = str;
            return(0);
        }
        ptr = ptr->next;
    }
    return (1);
}

int check_key(char *env)
{
    int i;
    i = 0;
    if ((env[i] >= 'a' && env[i] <= 'z') || (env[i] >= 'A' && env[i] <= 'Z') || env[i] == '_')
    {
        while (env[i] != '+' && env[i] != '=' && env[i])
        {
            if ((env[i] >= 'a' && env[i] <= 'z') || (env[i] >= 'A' && env[i] <= 'Z') || (env[i] >= '0' && env[i] <= '9') || env[i] == '_')
            {
                i++; 
                if (env[i] == '+' && env[i + 1] != '=')
                    return(1);
            }
            else
                return(1);
        }
        
        return(0);
    }
    return (1);
    
}
void print_export(t_env *env,int fd)
{
    t_val val;
    t_env *ptr1;
    t_env *ptr2;
    t_env *ptr3;
    ptr1 = env;
    ptr2 = env;
    ptr3 = env;
    val.fd = fd;
    while (ptr1)
    {
        print_order(env,&val,ptr2,ptr3);    
        ptr1 = ptr1->next;
    }
    ptr1 = env;
    while (ptr1)
    {
        ptr1->cheak = 1;
        ptr1 = ptr1->next;
    }
         
}
void cmd_export(t_env **env,char **arg,int fd)
{
    int i;
    int k;
    k = 1;
    i = 0;
    if (!arg[i])
        print_export(*env,fd);
    while (arg[i])
    {
        if(check_key(arg[i]))
        {
            p_error("export: '");
            p_error(arg[i]);
            p_error("': not a valid identifier\n");
            k = 0;
        }
        if (cheak_add(env,arg[i]) && k)
        {
            ft_lstadd_back_mini(env,ft_lstnew_mini(arg[i]));
        }
        k = 1;
        i++ ;
    }
}