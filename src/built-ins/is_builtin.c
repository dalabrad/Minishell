/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:02:44 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/21 19:45:11 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

bool	is_builtin(char *cmd_name, t_data *data)
{
	int		i;
	char	*current;

	if (!data || !cmd_name)
		return (false);
	i = 0;
	while (data->g_builtin[i].name)
	{
		current = data->g_builtin[i].name;
		if (!ft_strncmp(current, cmd_name, ft_strlen(cmd_name) + 1))
			return (true);
		i++;
	}
	return (false);
}
