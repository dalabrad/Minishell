/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:25:14 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/15 18:29:16 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_UTILS_H
 #define ARRAY_UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

////////////////////////////////////////////////
//------ARRAY-UTILS-----------------------------
////////////////////////////////////////////////

//  src/array_utils/array_utils.c

void	free_array(char **array);
size_t	array_size(char **array);
void	print_array(char **array);

#endif