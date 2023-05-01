/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:28 by abouassi          #+#    #+#             */
/*   Updated: 2023/04/14 17:10:26 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./Includes/minishell.h"
int	ft_lstsize_mini(t_cmd *lst)
{
	int		i;
	t_cmd	*ptr;

	i = 0;
	ptr = lst;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}
t_env	*ft_lstnew_mini(char *content)
{
	t_env	*newnode;
	char **val_key;
	newnode = malloc(sizeof(t_env));
	if (!newnode)
		return (NULL);
	val_key = var_val(content);
	newnode->content = content;
	newnode->key = val_key[0];
	newnode->value = val_key[1];
	newnode->cheak = 1;
	newnode->next = NULL;
	free(val_key);

	return (newnode);
}

void	ft_lstadd_back_mini(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (lst && new)
	{
		if (*lst)
		{
			ptr = *lst;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

void	del_node(t_env **head,char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	if (temp && !ft_strcmp(temp->key,key))
	{
		*head = (*head)->next;
	}	
	while (temp && ft_strcmp(temp->key,key))
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	free(temp->key);
	free(temp->value);
	free(temp);
}