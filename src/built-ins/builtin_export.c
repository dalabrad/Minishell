/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/21 16:21:58 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static char *extract_name(char *arg)
{
    size_t len = 0;

    while (arg[len] && arg[len] != '=')
        len++;
    return (ft_substr(arg, 0, len));
}

int shell_export(char **args, t_data *data)
{
    t_env *tmp;
    t_env *new;
    t_env **shell_envp;
    char *name;

    if (!args || !*args || !ft_strchr(*args, '='))
        return (EXIT_FAILURE);
// Temporal
	if (args)
		printf("args[0] = %s\n", args[0]);
	else
		printf("args is NULL\n");
	
    shell_envp = &(data->shell_envp);
    name = extract_name(*args);
    if (!name)
        return (EXIT_FAILURE);

    tmp = *shell_envp;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, name) == 0)
        {
            free(tmp->value);
            tmp->value = get_envp_value(*args);
            free(name);
            return (EXIT_SUCCESS);
        }
        tmp = tmp->next;
    }

    free(name);
    new = new_shell_envp(*args, true);
    if (!new)
        return (error_msg(MALLOC_ERROR));

    add_shell_envp(shell_envp, new);
    return (EXIT_SUCCESS);
}
