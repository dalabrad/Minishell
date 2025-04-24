/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/24 14:58:40 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_export(char **args, t_data *data)
{
	int			name_len;
	t_env		*tmp;
	t_env		**shell_envp;

	if (!args || !args[0] || !ft_strchr(args[0], '='))
		return (EXIT_FAILURE);
	shell_envp = &(data->shell_envp);
	name_len = ft_strchr(args[0], '=') - &args[0][0];
	tmp = *shell_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, args[0], name_len))
		{
			free(tmp->value);
			tmp->value = get_envp_value(args[0]);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	tmp = new_shell_envp(args[0], true);
	if (!tmp)
		return (error_msg(MALLOC_ERROR));
	add_shell_envp(shell_envp, tmp);
	return (EXIT_SUCCESS);
}
