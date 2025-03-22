/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_envp_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:14:57 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/22 15:19:56 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

t_env	*new_shell_envp(char *envp, bool was_added)
{
	t_env	*new_shell_envp;

	new_shell_envp = (t_env *)malloc(sizeof(t_env));
	if (!new_shell_envp)
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
