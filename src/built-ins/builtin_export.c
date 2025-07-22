/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/22 19:17:31 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_export(char **args, t_data *data)
{
	int			name_len;
	t_env		*tmp;
	t_env		**shell_envp;
	int			i;

	if (!args || !args[0])
		return (EXIT_FAILURE);
	shell_envp = &(data->shell_envp);
	i = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
		{
			printf("'=' not found in argument!!\n");
			i++;
			continue ;
		}
		name_len = ft_strchr(args[i], '=') - &args[i][0];
		tmp = *shell_envp;
		while (tmp)
		{
			if (!ft_strncmp(tmp->name, args[i], name_len) && !ft_strncmp(tmp->name, args[i], ft_strlen(tmp->name)))
			{
				free(tmp->value);
				tmp->value = get_envp_value(args[i]);
				break ;
			}
			tmp = tmp->next;
		}
		if (tmp)
		{
			i++;
			continue ;
		}
		tmp = new_shell_envp(args[i], true);
		if (!tmp)
			return (error_msg(MALLOC_ERROR));
		add_shell_envp(shell_envp, tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
