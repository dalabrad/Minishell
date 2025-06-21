/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/21 19:09:29 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static char	*extract_name(char *arg)
{
	size_t	len = 0;

	while (arg[len] && arg[len] != '=')
		len++;
	return (ft_substr(arg, 0, len));
}

int	shell_export(char **args, t_data *data)
{
	t_env	*tmp;
	t_env	*new;
	t_env	**shell_envp;
	char	*name;
	char	*with_equal;

	if (!args || !args[0])
		return (EXIT_FAILURE);

	// Si no contiene '=', lo añadimos como 'VAR=' con valor vacío
	if (!ft_strchr(args[0], '='))
	{
		with_equal = ft_strjoin(args[0], "=");
		if (!with_equal)
			return (error_msg(MALLOC_ERROR));
	}
	else
	{
		with_equal = ft_strdup(args[0]);
		if (!with_equal)
			return (error_msg(MALLOC_ERROR));
	}

	shell_envp = &(data->shell_envp);
	name = extract_name(with_equal);
	if (!name)
	{
		free(with_equal);
		return (EXIT_FAILURE);
	}

	tmp = *shell_envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = get_envp_value(with_equal);
			free(name);
			free(with_equal);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}

	free(name);
	new = new_shell_envp(with_equal, true);
	free(with_equal);
	if (!new)
		return (error_msg(MALLOC_ERROR));
	add_shell_envp(shell_envp, new);
	return (EXIT_SUCCESS);
}

