/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_segments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:36:10 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/07/28 21:50:16 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "minishell_exec.h"

void process_single_segment(char *segment, t_tokens **token_ptr, t_cmd **cmd_ptr, size_t index)
{
    size_t words = 0;

    printf("::::::PROCESS SINGLE SEGMENT");

    token_ptr[index] = check_args_fixed(segment, &words);
    if (!token_ptr[index])
    {
        printf("Error tokenizing segment.\n");
        return;
    }

    printf("PIPE[%zu]: %s\n", index, segment);
    print_tokens(token_ptr[index]);

    cmd_ptr[index] = tokens_to_cmd(token_ptr[index]);
    if (!cmd_ptr[index])
    {
        printf("Error converting tokens to cmd.\n");
        free_tokens_list(token_ptr[index]);
        token_ptr[index] = NULL;
        return;
    }
}



// PROCESS ALL PIPES
void process_segments(char **segments, t_tokens **tokens, size_t n, t_data *data)
{
    size_t i;
    t_cmd *current_cmd;
    t_cmd *last;
    
    printf(":::PROCESS SEGMENTS");
    
    data->first_cmd = NULL;
    i = 0;
    while (i < n)
    {
        size_t word_count = 0;
        tokens[i] = check_args_fixed(segments[i], &word_count);
        printf("::::NUM of TOKENS %li\n\n", i);
        if (!tokens[i])
        {
            i++;
            continue;
        }
        // Expande variables en tokens
        expand_tokens(tokens[i], data->shell_envp, data->last_status);
         printf(":::::TOKEN %lu\n\n", n);
        current_cmd = tokens_to_cmd(tokens[i]);
        
        if (!current_cmd)
        {
            free_tokens_list(tokens[i]);
            i++;
            continue;
        }
        //process_single_segment(segments[i], tokens, &current_cmd, i);
        if (!data->first_cmd)
            data->first_cmd = current_cmd;
        else
        {
            last = last_cmd(data->first_cmd);
            last->next = current_cmd;
        }
        i++;
    }
    data->nbr_cmds = number_of_cmds(data->first_cmd);
}
