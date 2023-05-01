/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:18:48 by abouassi          #+#    #+#             */
/*   Updated: 2023/04/17 02:25:02 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"
void execution_mini(t_global *all,char **env)
{
    t_cmd *cmds;
    cmds = all->all_cmd;
    if( cmds && !cmds->next )
    {
        set_her_doc(cmds);
        set_red(cmds);
        if (cheackis_buil(all->all_cmd->cmd))
            exucute_builtine(all,all->all_cmd);
        if (cmds->cmd && cheackis_buil(all->all_cmd->cmd) != 1) // cheackis_buil(all->all_cmd->cmd) != 1 had chi bash matexutch fi child
            cmd_excution(all,env);
    }
    else 
    {
        while (cmds)
        {
            set_her_doc(cmds);
            cmds = cmds->next;
        }
        cmds = all->all_cmd;
        while (cmds)
        {
            set_red(cmds);
            cmds = cmds->next;
        }
        cmd_excution(all,env);
    }
}