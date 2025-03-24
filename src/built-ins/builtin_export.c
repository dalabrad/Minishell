/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/24 16:44:10 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_export(char **args, t_env **shell_envp)
{
	int			name_len;
	t_env		*tmp;

	if (!args || !args[0] || !args[1] || !ft_strchr(args[1], '='))
		return (EXIT_FAILURE);
	name_len = ft_strchr(args[1], '=') - &args[1][0];
	tmp = *shell_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, args[1], name_len))
		{
			free(tmp->value);
			tmp->value = get_envp_value(args[1]);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	tmp = new_shell_envp(args[1], true);
	if (!tmp)
		return (error_msg(MALLOC_ERROR));
	add_shell_envp(shell_envp, tmp);
	return (EXIT_SUCCESS);
}
