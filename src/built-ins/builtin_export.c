/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/03 21:36:47 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

/*
 * Imprime la lista del entorno exportado en formato:
 * declare -x VAR="valor"
 */
int	print_export_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->visible)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env_list->name, STDOUT_FILENO);
			if (env_list->value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(env_list->value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		env_list = env_list->next;
	}
	return (0);
}

void	add_or_update_env(t_env *env_list, const char *name, const char *value,
		bool overwrite)
{
	t_env	*current;
	t_env	*new;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (overwrite)
			{
				free(current->value);
				current->value = value ? ft_strdup(value) : NULL;
			}
			return ;
		}
		current = current->next;
	}
	// No encontrada: añadir al final
	new = malloc(sizeof(t_env));
	if (!new)
	{
		error_msg(MALLOC_ERROR);
		return ;
	}
	new->name = ft_strdup(name);
	new->value = value ? ft_strdup(value) : NULL;
		// si existe haz strdup y sobreescribe, sino iguala a NULL
	new->visible = true;
	new->next = NULL;
	// Insertar al final
	current = env_list;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	builtin_export(char **args, t_data *data)
{
	int		i;
	char	*var;
	char	*name;
	char	*value;

	i = 0;
	if (!args || !args[0])
		return (print_export_env(data->shell_envp));
	while (args[i])
	{
		var = args[i];
		if (!ft_strchr(var, '='))
		{
			add_or_update_env(data->shell_envp, NULL, var, false);
		}
		else
		{
			name = ft_substr(var, 0, ft_strchr(var, '=') - var);
			value = ft_strdup(ft_strchr(var, '=') + 1);
			if (!name || !value)
			{
				free(name);
				free(value);
				return (error_msg(MALLOC_ERROR));
			}
			add_or_update_env(data->shell_envp, name, value, true);
			free(name);
			free(value);
		}
		i++;
	}
	return (0);
}
