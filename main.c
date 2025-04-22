/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:10:17 by khhihi            #+#    #+#             */
/*   Updated: 2025/04/21 20:23:17 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parsing_cmd(char *input)
{
    t_token *tokens;

    //split the command into tokens
    tokens = tokenize(input);
}
int main(int ac, char *av[], char **env)
{
    char *input;
    (void)env;
    (void)av;
    (void)ac;
    input = NULL;
    while (1)
    {
        input = readline("minishell> ");
        if (input == NULL)
            break;
        if (*input)
            add_history(input);
        parsing_cmd(input);
        printf("You entered: %s\n", input);
        free(input);
    }
}

