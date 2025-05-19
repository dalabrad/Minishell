/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/19 17:58:50 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void	export_parameter(t_env	**shell_envp, char *parameter, int name_len)
{
	t_env		*tmp;

	if (name_len <= 0)
		return ;
	tmp = *shell_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, parameter, name_len))
		{
			free(tmp->value);
			tmp->value = get_envp_value(parameter);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = new_shell_envp(parameter, true);
	if (!tmp)
	{
		error_msg(MALLOC_ERROR);
		return ;
	}
	add_shell_envp(shell_envp, tmp);
}

int	shell_export(char **args, t_data *data)
{
	size_t		i;
	int			name_len;

	if (!args || !args[0] || !ft_strchr(args[0], '='))
		return (EXIT_FAILURE);
	i = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
		{
			i++;
			continue ;
		}
		name_len = ft_strchr(args[i], '=') - &args[i][0];
		if (name_len <= 0)
		{
			error_msg_arg(EXPORT_ERROR, args[i]);
			i++;
			continue ;
		}
		export_parameter(&(data->shell_envp), args[i], name_len);
		i++;
	}
	return (EXIT_SUCCESS);
}
