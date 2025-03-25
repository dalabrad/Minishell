/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:08:15 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/25 18:19:30 by dalabrad         ###   ########.fr       */
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

static size_t	array_size(char **array)
{
	size_t	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

static int	export_pwd(t_env **shell_envp, char *pwd_path, char *pwd_type)
{
	char	**tmp;

	tmp = (char **)malloc(2 * sizeof(char *));
	if (!tmp)
		return (error_msg(MALLOC_ERROR));
	tmp[0] = ft_strjoin(pwd_type, pwd_path);
	if (!tmp[0])
	{
		free(tmp);
		return (error_msg(MALLOC_ERROR));
	}
	tmp[1] = NULL;
	shell_export(tmp, shell_envp);
	free_array(array_size(tmp), tmp);
	return (EXIT_SUCCESS);
}

int	shell_cd(char **args, t_env **shell_envp)
{
	char	*old_pwd;
	char	*pwd;
	int		status;

	if (!args || !args[0])
		return (EXIT_FAILURE);
	if (array_size(args) != 1)
		return (error_msg(CD_ERROR));
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (error_msg(MALLOC_ERROR));
	if (chdir(args[0]))
		return (printf("minishell: couldn`t access %s directory", args[0]));
	status = 0;
	status += export_pwd(shell_envp, old_pwd, "OLDPWD=");
	free(old_pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_msg(MALLOC_ERROR));
	status += export_pwd(shell_envp, pwd, "PWD=");
	free(pwd);
	return (status);
}
