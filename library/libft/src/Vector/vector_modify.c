/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_modify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:27:38 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 22:50:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vector.h"

static void	ft_memcpy(void *dest, const void *src, size_t nbyte)
{
	size_t				i;
	unsigned char		*u_dest;
	const unsigned char	*u_src;

	u_dest = dest;
	u_src = src;
	i = 0;
	while (i < nbyte)
	{
		u_dest[i] = u_src[i];
		++i;
	}
}

void	*vector_reserve(t_vector *vec, size_t new_capacity)
{
	void	*new_data;

	new_data = NULL;
	if (vec->capacity < new_capacity)
	{
		new_data = new_data_malloc(new_capacity);
		if (new_data != NULL)
		{
			ft_memcpy(new_data, vec->data, (vec->size * sizeof(size_t)));
			free(vec->data);
			vec->data = new_data;
			vec->capacity = new_capacity;
		}
	}
	return ((void *)(new_data));
}

void	*vector_shrink_to_fit(t_vector *vec)
{
	void	*shrinked_data;

	shrinked_data = NULL;
	if (vec->size < vec->capacity)
	{
		shrinked_data = new_data_malloc(vec->size);
		if (shrinked_data != NULL)
		{
			ft_memcpy(shrinked_data, vec->data, (vec->size * sizeof(size_t)));
			free(vec->data);
			vec->data = shrinked_data;
			vec->capacity = vec->size;
		}
	}
	return (shrinked_data);
}

void	vector_push_back(t_vector *vec, void *data_in)
{
	void	*status;

	if (vec == NULL || data_in == NULL)
		return ;
	if (vec->size >= vec->capacity)
	{
		status = vector_reserve(vec, vec->capacity * 2);
		if (status == NULL)
			return ;
	}
	vector_set_data(vec, vec->size, data_in);
	(vec->size)++;
}

void	vector_pop_back(t_vector *vec)
{
	if (vec->size > 0)
	{
		vector_set_data(vec, vec->size - 1, NULL);
		(vec->size)--;
	}
}
