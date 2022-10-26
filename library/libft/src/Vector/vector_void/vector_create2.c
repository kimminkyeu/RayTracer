/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:01:27 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:30:29 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

void	set_vector_func_ptr(t_vector *pa_vec)
{
	pa_vec->_deallocator_func = NULL;
	pa_vec->get_last = vector_get_last;
	pa_vec->is_empty = vector_is_empty;
	pa_vec->iterate = vector_iterate;
	pa_vec->map_malloc = vector_map_malloc;
	pa_vec->pop_back = vector_pop_back;
	pa_vec->push_back = vector_push_back;
	pa_vec->reserve = vector_reserve;
	pa_vec->reset = vector_reset;
	pa_vec->shrink_to_fit = vector_shrink_to_fit;
}

void	vector_reset(t_vector *vec)
{
	size_t	idx;

	idx = 0;
	while (idx < vec->size)
	{
		vector_set_data(vec, idx, NULL);
		++idx;
	}
	vec->size = 0;
}

/** WARN:  if there is malloc-allocated data,
 * then use _deallocator() to free each data component.  */
void	vector_set_data(t_vector *vec, size_t index, void *data)
{
	if (vec->data[index] != NULL)
	{
		if (vec->_deallocator_func != NULL)
			vec->_deallocator_func(vec->data[index]);
		free(vec->data[index]);
	}
	vec->data[index] = data;
}

void	*new_data_malloc(size_t init_capacity)
{
	void	*data;

	data = ft_calloc(init_capacity, sizeof(size_t));
	return (data);
}
