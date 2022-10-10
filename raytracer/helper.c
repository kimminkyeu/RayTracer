/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:43:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 17:03:53 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>


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
