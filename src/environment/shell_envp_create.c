/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_envp_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:38 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/22 13:00:07 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

char	*get_envp_name(char	*envp)
{
	int	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	return (ft_substr(envp, 0, len));
}

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

t_env	*new_shell_envp(char *envp, bool was_added)
{
	t_env	*new_shell_envp;

	new_shell_envp = (t_env *)malloc(sizeof(t_env));
	if (!shell_env)
		return (NULL);
	new_shell_envp->was_added = was_added;
	new_shell_envp->name = get_envp_name(envp);
	if (!new_shell_envp->name)
	{
		free(new_shell_envp);
		return (NULL);
	}
	new_shell_envp->value = get_envp_value(envp);
	if (!new_shell_envp->value)
	{
		free(new_shell_envp->name);
		free(new_shell_envp);
		return (NULL);
	}
	new_shell_envp->next = NULL;
	return (new_shell_envp);
}

t_env	*last_shell_envp(t_env *shell_envp)
{
	while (shell_envp)
	{
		if (!shell_envp->next)
			return (shell_envp);
		shell_envp = shell_envp->next;
	}
	return (shell_envp);
}

void	add_shell_envp(t_env **shell_envp, t_env *new_shell_envp)
{
	t_env	*last_envp;

	if (!new_shell_envp)
		return ;
	if (!*shell_envp)
	{
		*shell_envp = new_shell_envp;
		return ;
	}
	last_envp = last_shell_envp(*shell_envp);
	last_envp->next = new_shell_envp;
}

int	shell_envp_create(char **envp, t_env **shell_envp)
{
	t_env	*tmp;
	int		i;

	if (!envp || !envp[0])
		return (EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		tmp = new_shell_envp(envp[i], false);
		if (!tmp && i != 0)
		{
			free_shell_envp(envp); //TO DO!!
			str_error(MALLOC_ERROR); //TO DO!!
			return (MALLOC_ERROR);
		}
		add_shell_envp(shell_envp, tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
