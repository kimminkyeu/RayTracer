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

#include "gl_std_vector_vec4.h"

void	vector_vec4_iterate(t_vector_vec4 *vec, t_vec4 (*f)(t_vec4 itr_val))
{
	size_t		i;

	i = 0;
	while (i < vec->size)
	{
		vec->data[i] = f(vec->data[i]);
		i++;
	}
}

t_vector_vec4	*vector_vec4_map_malloc(t_vector_vec4 *vec, t_vec4 (*f)(t_vec4 itr_val))
{
	size_t		i;
	t_vector_vec4	*new_vec;

	new_vec = new_vector_vec4(vec->size);
	if (new_vec != NULL)
	{
		i = 0;
		while (i < vec->size)
		{
			vector_vec4_push_back(new_vec, f(vec->data[i]));
			i++;
		}
	}
	return (new_vec);
}

int	vector_vec4_is_empty(t_vector_vec4 *vec)
{
	if (vec->size == 0)
		return (true);
	else
		return (false);
}

t_vec4	*vector_vec4_get_last(t_vector_vec4 *vec)
{
	if (vec->size == 0)
		return (NULL);
	return (&vec->data[vec->size - 1]);
}
