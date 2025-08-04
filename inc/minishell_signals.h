/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:02:44 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/04 21:41:40 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

# include "minishell_exec.h"
# include "minishell_parsing.h"
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_tokens	t_tokens;

void					setup_signal_handlers(void);
void					restore_stdio(int in, int out);

#endif