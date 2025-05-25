/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:02:44 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/05/26 00:42:00 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

# include <signal.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include "minishell_exec.h"
# include "minishell_parsing.h"

typedef struct s_data t_data;
typedef struct s_tokens t_tokens;

void	setup_signal_handlers(void);
void	restore_stdio(int in, int out);
void	reset_cmd_state(t_data *data, char *line, char **segments, t_tokens **tokens);

#endif