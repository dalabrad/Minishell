/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/12 17:49:31 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static char	*extract_name(char *arg)
{
	size_t	len = 0;

	while (arg[len] && arg[len] != '=')
		len++;
	return (ft_substr(arg, 0, len)); // Devuelve un string nuevo
}

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_export(char **args, t_data *data)
{
	t_env	*tmp;
	t_env	*new;
	t_env	**shell_envp;
	char	*name;

	if (!args || !args[0] || !ft_strchr(args[0], '='))
		return (EXIT_FAILURE);

	shell_envp = &(data->shell_envp);
	name = extract_name(args[0]);
	if (!name)
		return (EXIT_FAILURE);

	tmp = *shell_envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = get_envp_value(args[0]);
			free(name);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}

	free(name); // ya no es necesaria tras la búsqueda
	new = new_shell_envp(args[0], true); // usamos esta
	if (!new)
		return (error_msg(MALLOC_ERROR));

	add_shell_envp(shell_envp, new);
	return (EXIT_SUCCESS);
}
