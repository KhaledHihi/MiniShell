/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:09:54 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/01 22:38:07 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd   *create_new_cmd()
{
    t_cmd   *new;
    
    new = malloc(sizeof(t_cmd));
    if(!new)
        return (NULL);
    ft_bzero(new, sizeof(t_cmd));
    return (new);
}
void   add_cmd_to_lst(t_cmd **lst, t_cmd *new)
{
    t_cmd *tmp;
    
    if (!(*lst))
    {
        *lst = new;
        return ;
    }
    
    tmp = *lst;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

char **prs_cmd(t_token *tokens)
{
    t_cmd   *cmd_lst = NULL;
    t_cmd   *curr_cmd = NULL;
    
    while (tokens)
    {
        if (!curr_cmd || tokens->token_type == PIPE)
        {
            curr_cmd = create_new_cmd();
            if (!curr_cmd)
                return (NULL);
            add_cmd_to_lst(cmd_lst, curr_cmd);
        }
        else if (tokens->token_type == WORD)
            curr_cmd->arg = realoc_arr(curr_cmd->arg, tokens->value);
        tokens = tokens->next;
    }
}