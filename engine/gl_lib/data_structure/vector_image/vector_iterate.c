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

#include "gl_std_vector_image.h"

void	vector_image_iterate(t_vector_image *vec, t_image (*f)(t_image itr_val))
{
	size_t		i;

	i = 0;
	while (i < vec->size)
	{
		vec->data[i] = f(vec->data[i]);
		i++;
	}
}

t_vector_image	*vector_image_map_malloc(t_vector_image *vec, t_image (*f)(t_image itr_val))
{
	size_t		i;
	t_vector_image	*new_vec;

	new_vec = new_vector_image(vec->size);
	if (new_vec != NULL)
	{
		i = 0;
		while (i < vec->size)
		{
			vector_image_push_back(new_vec, f(vec->data[i]));
			i++;
		}
	}
	return (new_vec);
}

int	vector_image_is_empty(t_vector_image *vec)
{
	if (vec->size == 0)
		return (true);
	else
		return (false);
}

t_image	*vector_image_get_last(t_vector_image *vec)
{
	if (vec->size == 0)
		return (NULL);
	return (&vec->data[vec->size - 1]);
}
