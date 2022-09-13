/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:46:20 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/12 14:14:12 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_uchar.h"

void	vector_uchar_iterate(t_vector_uchar *vec, unsigned char (*f)(unsigned char itr_val))
{
	size_t		i;

	i = 0;
	while (i < vec->size)
	{
		vec->data[i] = f(vec->data[i]);
		i++;
	}
}

t_vector_uchar	*vector_uchar_map_malloc(t_vector_uchar *vec, unsigned char (*f)(unsigned char itr_val))
{
	size_t		i;
	t_vector_uchar	*new_vec;

	new_vec = new_vector_uchar(vec->size);
	if (new_vec != NULL)
	{
		i = 0;
		while (i < vec->size)
		{
			vector_uchar_push_back(new_vec, f(vec->data[i]));
			i++;
		}
	}
	return (new_vec);
}

int	vector_uchar_is_empty(t_vector_uchar *vec)
{
	if (vec->size == 0)
		return (true);
	else
		return (false);
}

unsigned char	*vector_uchar_get_last(t_vector_uchar *vec)
{
	if (vec->size == 0)
		return (NULL);
	return (&vec->data[vec->size - 1]);
}
