/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:53:07 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/06/29 13:04:38 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

#include "minishell_exec.h"
#include "minishell_parsing.h"

//Conviertimos lista variables entorno t_env-> a array **envp tipo "VAR=VALUE"
char **shell_envp_to_array(t_env *env_list)
{
    size_t  count = 0;
    t_env   *tmp = env_list;
    char    **array;
    char    *tmp_str;

    //Cuenta las variables visibles
    while (tmp)
    {
        if (tmp->visible)
            count++;
        tmp = tmp->next;
    }

    //Reserva memoria pa array de strings
    array = ft_calloc(count + 1, sizeof(char *));
    if (!array)
        return (NULL);

    tmp = env_list;
    size_t i = 0;
    while (tmp)
    {
        if (tmp->visible)
        {
            tmp_str = ft_strjoin(tmp->name, "=");
            if (!tmp_str)
                return (free_array(array), NULL);

            array[i] = ft_strjoin(tmp_str, tmp->value);
            free(tmp_str);

            if (!array[i])
                return (free_array(array), NULL);
            i++;
        }
        tmp = tmp->next;
    }
    array[i] = NULL;
    return (array);
}
