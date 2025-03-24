/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_envp_list_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:30:57 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/24 18:31:55 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void	free_shell_envp_node(t_env *shell_envp_node)
{
	free(shell_envp_node->name);
	free(shell_envp_node->value);
	free(shell_envp_node);
}

/*
 * This function frees all the memory allocated for shell_envp list.
*/
void	free_shell_envp_list(t_env **shell_envp)
{
	t_env	*tmp;

	if (!shell_envp || !*shell_envp)
		return ;
	while (*shell_envp)
	{
		tmp = (*shell_envp)->next;
		free_shell_envp_node(*shell_envp);
		*shell_envp = tmp;
	}
}

void	delete_shell_envp_node(t_env **shell_envp, char *VAR_NAME)
{
	t_env	*tmp;
	t_env	*prev_tmp;

	if (!shell_envp || !*shell_envp)
		return ;
	tmp = *shell_envp;
	if (!ft_strncmp(tmp->name, VAR_NAME, ft_strlen(VAR_NAME)))
	{
		*shell_envp = (*shell_envp)->next;
		free_shell_envp_node(tmp);
		return ;
	}
	prev_tmp = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, VAR_NAME, ft_strlen(VAR_NAME)))
		{
			prev_tmp->next = tmp->next;
			free_shell_envp_node(tmp);
			return ;
		}
		prev_tmp = tmp;
		tmp = tmp->next;
	}
}
