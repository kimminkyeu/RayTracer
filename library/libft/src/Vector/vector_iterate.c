/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:46:20 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 22:49:33 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_iterate(t_vector *vec, void (*f)(void *))
{
	size_t	i;

	i = 0;
	while (i < vec->size)
	{
		f(vec->data[i]);
		i++;
	}
}

t_vector	*vector_map_malloc(t_vector *vec, void *(*f)(void *))
{
	size_t		i;
	t_vector	*new_vec;

	new_vec = new_vector(vec->size);
	if (new_vec != NULL)
	{
		i = 0;
		while (i < vec->size)
		{
			vector_push_back(new_vec, f(vec->data[i]));
			i++;
		}
	}
	return (new_vec);
}

int	vector_is_empty(t_vector *vec)
{
	size_t	i;

	i = 0;
	while (i < vec->size)
	{
		if (vec->data[i] != NULL)
			return (0);
		++i;
	}
	return (1);
}

void	*vector_get_last(t_vector *vec)
{
	if (vec->size == 0)
		return (NULL);
	return (vec->data[vec->size - 1]);
}
