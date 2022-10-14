/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:43:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 14:17:51 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/** helper function. (min) */
float min_float(float f1, float f2)
{
	if (f1 >= f2)
		return (f2);
	else
		return (f1);
}

/** helper function. (max) */
float max_float(float f1, float f2)
{
	if (f1 >= f2)
		return (f1);
	else
		return (f2);
}

/** helper function. (abs) */
float abs_float(float f)
{
	if (f >= 0.0f)
		return (f);
	else
		return (-f);
}

int clamp_int(int i, int min, int max)
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
	size_t i;

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
