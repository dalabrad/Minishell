/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:32:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/13 13:39:12 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "../libft/inc/libft.h"
# include "minishell_parsing.h"
# include <stdio.h>

typedef struct s_builtin
{
	char	*builtin_name;
	int		(*foo)(char **args);
}	t_builtin;

//	src/minishell_builtins.c
void	shell_exec(char **args);

#endif