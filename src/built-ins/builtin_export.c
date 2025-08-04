/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/28 16:57:28 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void	export_one(char	*arg, t_env **shell_envp, size_t name_len)
{
	t_env	*tmp;

	tmp = *shell_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, arg, name_len)
			&& !ft_strncmp(tmp->name, arg, ft_strlen(tmp->name)))
		{
			free(tmp->value);
			tmp->value = get_envp_value(arg);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = new_shell_envp(arg, true);
	if (!tmp)
	{
		error_msg(MALLOC_ERROR);
		return ;
	}
	add_shell_envp(shell_envp, tmp);
}

int	shell_export(char **args, t_data *data)
{
	size_t		name_len;
	t_env		**shell_envp;
	int			i;

	if (!args || !args[0])
		return (EXIT_SUCCESS);
	shell_envp = &(data->shell_envp);
	i = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
		{
			i++;
			continue ;
		}
		name_len = ft_strchr(args[i], '=') - &args[i][0];
		export_one(args[i], shell_envp, name_len);
		i++;
	}
	return (EXIT_SUCCESS);
}
