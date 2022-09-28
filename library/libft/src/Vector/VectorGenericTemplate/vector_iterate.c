/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:46:20 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/09 16:35:15 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_GENERIC.h"

void	vector_GENERIC_iterate(t_vector_GENERIC *vec, t_GENERIC (*f)(t_GENERIC itr_val))
{
	size_t		i;

	i = 0;
	while (i < vec->size)
	{
		vec->data[i] = f(vec->data[i]);
		i++;
	}
}

t_vector_GENERIC	*vector_GENERIC_map_malloc(t_vector_GENERIC *vec, t_GENERIC (*f)(t_GENERIC itr_val))
{
	size_t		i;
	t_vector_GENERIC	*new_vec;

	new_vec = new_vector_GENERIC(vec->size);
	if (new_vec != NULL)
	{
		i = 0;
		while (i < vec->size)
		{
			vector_GENERIC_push_back(new_vec, f(vec->data[i]));
			i++;
		}
	}
	return (new_vec);
}

int	vector_GENERIC_is_empty(t_vector_GENERIC *vec)
{
	if (vec->size == 0)
		return (true);
	else
		return (false);
}

t_GENERIC	*vector_GENERIC_get_last(t_vector_GENERIC *vec)
{
	if (vec->size == 0)
		return (NULL);
	return (&vec->data[vec->size - 1]);
}
