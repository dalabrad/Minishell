/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:25:14 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/27 19:24:26 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_UTILS_H
# define ARRAY_UTILS_H

# include "minishell_signals.h"
# include "minishell_exec.h"
# include "minishell_parsing.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

////////////////////////////////////////////////
//------ARRAY-UTILS-----------------------------
////////////////////////////////////////////////

//  src/array_utils/array_utils.c

void	free_array(char **array);
size_t	array_size(char **array);
void	print_array(char **array);void restore_stdio(int in, int out);

////////////////////////////////////////////////
//------MAIN-UTILS------------------------------
////////////////////////////////////////////////

//  src/main_utils.c

void restore_stdio(int in, int out);
void reset_cmd_state(t_data *data, char *line, char **segments, t_tokens **tokens);int     main_exit(t_data *data);


////////////////////////////////////////////////
//------MAIN-------------------------------
////////////////////////////////////////////////

//  main.c

int main_exit(t_data *data);

#endif