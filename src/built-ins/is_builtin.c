/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:02:44 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/24 15:00:24 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

bool	is_builtin(char *cmd_name, t_data *data)
{
	char	*current;
	int		i;

	if (!data || !cmd_name)
		return (false);
	current = NULL;
	i = 0;
	while (data->g_builtin[i].name)
	{
		current = data->g_builtin[i].name;
		if (!ft_strncmp(current, cmd_name, ft_strlen(cmd_name)))
			return (true);
		i++;
	}
	return (false);
}
