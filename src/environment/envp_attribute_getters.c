/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_attribute_getters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:14:01 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/23 23:01:00 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

/*
 * This function returns the string of the name of the given envp. Allocates the 
 * memory for it, so it needs to be freed in case you want to destroy a node
 * of shell envp list.
*/
char	*get_envp_name(char	*envp)
{
	int	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	return (ft_substr(envp, 0, len));
}

/*
 * This function returns the string of the value of the given envp. Allocates 
 * the memory for it, so it needs to be freed in case you want to destroy a 
 * node of shell envp list.
*/
char	*get_envp_value(char *envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			return (ft_substr(envp, i + 1, ft_strlen(envp + i + 1)));
		i++;
	}
	return (NULL);
}
