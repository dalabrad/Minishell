/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_attribute_getters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:14:01 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/12 13:05:36 by dalabrad         ###   ########.fr       */
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

/*
 * This function checks in the envp list of minishell for name parameter 
 * and returns the value string if exists. If parameter dosen`t exist or malloc 
 * error occurs NULL is returned.
*/
char	*get_shell_envp_value(t_env *shell_envp, const char *name)
{
	char	*value;

	if (!shell_envp || !name)
		return (NULL);
	value = NULL;
	while (shell_envp)
	{
		if (!strncmp(shell_envp->name, name, strlen(name))
			&& !strncmp(shell_envp->name, name, strlen(shell_envp->name)))
		{
			value = ft_strdup(shell_envp->value);
			if (!value)
			{
				error_msg(MALLOC_ERROR);
				return (NULL);
			}
			return (value);
		}
		shell_envp = shell_envp->next;
	}
	return (NULL);
}

char	*get_shell_envp_str(t_env *shell_envp)
{
	char	*str;
	size_t	name_len;
	size_t	value_len;
	size_t	total_len;
	
	if (!shell_envp)
		return (NULL);
	name_len = ft_strlen(shell_envp->name);
	value_len = ft_strlen(shell_envp->value);
	total_len = name_len + value_len + 2;
	str = (char *)malloc(sizeof(char) * total_len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, shell_envp->name, total_len);
	ft_strlcat(str, "=", total_len);
	if (shell_envp->value)
		ft_strlcat(str, shell_envp->value, total_len);
	return (str);
}