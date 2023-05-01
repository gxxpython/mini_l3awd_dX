/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:12:50 by abouassi          #+#    #+#             */
/*   Updated: 2023/04/14 17:41:45 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"
char *cheak_key(t_env *env,char *key,int k)
{
    t_env *ptr;
    ptr = env;
    while (ptr)
    {
        if (!ft_strcmp(key,ptr->key))
        {
            if(k)
                ptr->value = NULL;
            return ptr->key;
        }
        ptr = ptr->next;
    }
    return NULL;
}
char *get_env(t_env *env,char *s,char *s2)
{
    t_env *ptr;
    ptr = env;
    while (ptr)
    {
        if (!ft_strcmp(ptr->key,s))
        {
            if (s2)
            {
                ptr->value = s2;
                break;
            }
            return(ptr->value); 
        }
        ptr = ptr->next;
    }
    return (NULL);
}
char *go_to_home(t_env *env)
{
    t_env *ptr;
    ptr = env;
    while (ptr)
    {
        if (!ft_strcmp(ptr->key,"HOME"))
            return ptr->value;
        ptr = ptr->next;
    }
    return NULL;
}
void back_old(t_env **env)
{
    char *temp;
    if (!get_env(*env,"OLDPWD",NULL))
    {
        p_error("cd: ");
        p_error("OLDPWD not set\n");
        return  ; 
    }
    else
    {
        temp = get_env(*env,"PWD",NULL);
        if (!get_env(*env,"OLDPWD",NULL))
        {
            p_error("OLDPWD not set\n");
            return  ;
        }
        if(chdir( get_env(*env,"OLDPWD",NULL))  == -1)
        {
            perror(get_env(*env,"OLDPWD",NULL));
            return ;
        }
        printf("%s\n",get_env(*env,"OLDPWD",NULL));
        get_env(*env,"PWD",get_env(*env,"OLDPWD",NULL));
        get_env(*env,"OLDPWD",temp);
        return  ;
    }
}
void cmd_cd(char **path,t_env **env)
{
    char *join;
    if (!path)
    {
        chdir(go_to_home(*env));
        return ;
    }
   
    if (path[0][0] == '-' && path[0][1] =='\0')
    {
        back_old(env);
        if (!cheak_key(*env,"PWD",0))
        {
            ft_lstadd_back_mini(env,ft_lstnew_mini("PWD"));
            cheak_key(*env,"OLDPWD",1);
        }
        return ;
    }
    if (path[0][0] != '/')
    {
        join = ft_strjoin(cmd_pwd(1,0),"/");
        join = ft_strjoin(join,path[0]);
    }
    else
        join = path[0];
    if (!cheak_key(*env,"OLDPWD",0))
        ft_lstadd_back_mini(env,ft_lstnew_mini("OLDPWD"));
    
    get_env(*env,"OLDPWD",cmd_pwd(1,0));    
    if (chdir(join) != 0)
        perror(path[0]);
    get_env(*env,"PWD",cmd_pwd(1,0));
}
