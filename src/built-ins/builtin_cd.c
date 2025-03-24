/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:08:15 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/24 12:28:56 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static int	export_changes(t_env *shell_envp, char *old_pwd)
{
	char	**tmp;
	char	*pwd;

	tmp = (char **)malloc(3 * sizeof(char *));
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("OLDPWD=", old_pwd);
	tmp[2] = NULL;
	shell_export(tmp, shell_envp);
	free(tmp[2]);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_msg(MALLOC_ERROR));
	tmp[2] = ft_strjoin("PWD=", pwd);
	shell_export(tmp, shell_envp);
	free_array(3, tmp);
	free(pwd);
	return (EXIT_SUCCESS);
}

int	shell_cd(char **args, t_env *shell_envp)
{
	char	*old_pwd;
	int		status;

	if (!args || !args[0] || !args[1])
		return (EXIT_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (error_msg(MALLOC_ERROR));
	if (chdir(args[1]))
		return (printf("Minishell: couldn`t access %s directory", args[1]));
	status = export_changes(shell_envp, old_pwd);
	free(old_pwd);
	return (status);
}
