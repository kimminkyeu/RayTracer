/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:43:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 19:38:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "objects.h"
#include "texture.h"
#include "gl_engine.h"

void	print_error_and_exit(t_device *device, char *str)
{
	ft_putstr_fd(str, 2);
	engine_exit(device, EXIT_FAILURE);
}

int	clamp_int(int i, int min, int max)
{
	if (i < min)
		return (min);
	else if (i > max)
		return (max);
	else
		return (i);
}

size_t	get_strs_count(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	free_split_char(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
	}
	free(split);
}
