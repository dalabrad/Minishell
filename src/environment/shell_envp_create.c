/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_envp_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:38 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/22 15:22:12 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

void	print_shell_envp(t_env *shell_envp)
{
	while (shell_envp)
	{
		printf("%s=%s\n", shell_envp->name, shell_envp->value);
		shell_envp = shell_envp->next;
	}
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
			//free_shell_envp(envp); //TO DO!!
			//str_error(MALLOC_ERROR); //TO DO!!
			return (MALLOC_ERROR);
		}
		add_shell_envp(shell_envp, tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
