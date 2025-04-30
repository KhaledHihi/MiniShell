/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:13:35 by khhihi            #+#    #+#             */
/*   Updated: 2025/04/28 19:13:35 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *int_env(char **env)
{
    t_env   *new_env;
    t_env   *lst;
    t_env   *tmp;
    int     i;
    int     j;
    char *equal_address;
    
    i =     0;
    while (env[i])
    {
        j = 0;
        new_env = malloc(sizeof(t_env));
        if (!new_env)
            return (NULL);
        equal_address = ft_strchr(env[i], '=');
        if (equal_address)
        {  
            while (env[i][j] && env[i][j] != '=')
                j++;
            new_env->key = ft_substr(env[i], 0, j);
            new_env->value = ft_strdup(equal_address + 1);
        }
        else
        {
            new_env->key = ft_strdup(env[i]);
            new_env->value = NULL;
        }
        if (!lst)
        {
            lst = new_env;
            new_env->next = NULL;
        }
        else
        {
            tmp = lst;
            while(tmp->next)
                tmp = tmp->next;
            tmp->next = new_env;
            new_env->next = NULL;
        }
        i++;
    }
    return (lst);
}