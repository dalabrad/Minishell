/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/08/05 18:21:01 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static bool	valid_export_arg(char *arg)
{
	int	i;

	if (!ft_strchr(arg, '='))
		return (false);
	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=')
			return (false);
		i++;
	}
	return (true);
}

static void	unvalid_arg_error(char *arg)
{
	ft_putstr_fd("bash: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier \n", 2);
}

static void	export_one(char	*arg, t_env **shell_envp, size_t name_len)
{
	t_env	*tmp;

	tmp = *shell_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, arg, name_len)
			&& !ft_strncmp(tmp->name, arg, ft_strlen(tmp->name)))
		{
			free(tmp->value);
			tmp->value = get_envp_value(arg);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = new_shell_envp(arg, true);
	if (!tmp)
	{
		error_msg(MALLOC_ERROR);
		return ;
	}
	add_shell_envp(shell_envp, tmp);
}

int	shell_export(char **args, t_data *data)
{
	size_t		name_len;
	t_env		**shell_envp;
	int			i;
	int			status;

	if (!args || !args[0])
		return (EXIT_SUCCESS);
	shell_envp = &(data->shell_envp);
	i = 0;
	status = 0;
	while (args[i])
	{
		if (!valid_export_arg(args[i]))
		{
			unvalid_arg_error(args[i]);
			status = 1;
			i++;
			continue ;
		}
		name_len = ft_strchr(args[i], '=') - &args[i][0];
		export_one(args[i], shell_envp, name_len);
		i++;
	}
	return (status);
}
