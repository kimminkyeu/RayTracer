/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:18:56 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/13 15:28:42 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vector.h"

extern void		*ft_calloc(size_t nmemb, size_t bytes);

t_vector	*new_vector(size_t init_capacity)
{
	t_vector	*vec;

	if (init_capacity == 0)
		return (NULL);
	vec = malloc(sizeof(*vec));
	if (vec != NULL)
	{
		vec->size = 0;
		vec->capacity = init_capacity;
		vec->data = new_data_malloc(init_capacity);
		if (vec->data == NULL)
		{
			free(vec);
			vec = NULL;
		}
	}
	set_vector_func_ptr(vec);
	return (vec);
}

t_vector	*new_vector_with_custom_deallocator(size_t init_capacity, void (*custom_deallocator)(void* data))
{
	t_vector	*vec;

	vec = new_vector(init_capacity);
	vec->_deallocator_func = custom_deallocator;
	return (vec);
}

void	delete_vector(t_vector **vec)
{
	vector_reset(*vec);
	free((*vec)->data);
	(*vec)->data = NULL;
	free(*vec);
	*vec = NULL;
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
