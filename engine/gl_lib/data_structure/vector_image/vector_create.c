/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:18:56 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/12 15:36:45 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gl_std_vector_image.h"

extern void	ft_bzero(void *s, size_t n);
extern void	*ft_calloc(size_t nmemb, size_t bytes);
extern void	set_vector_image_func_ptr(t_vector_image *pa_vec);
extern void	*new_image_data_malloc(size_t init_capacity);

t_vector_image	*new_vector_image(size_t init_capacity)
{
	t_vector_image	*vec;

	if (init_capacity == 0)
		return (NULL);
	vec = malloc(sizeof(*vec));
	if (vec != NULL)
	{
		vec->size = 0;
		vec->capacity = init_capacity;
		vec->data = new_image_data_malloc(init_capacity);
		if (vec->data == NULL)
		{
			free(vec);
			return (NULL);
		}
	}
	set_vector_image_func_ptr(vec);
	return (vec);
}

void	delete_vector_image(t_vector_image **vec)
{
	vector_image_reset(*vec);
	free((*vec)->data);
	(*vec)->data = NULL;
	free(*vec);
	*vec = NULL;
}

void	vector_image_reset(t_vector_image *vec)
{
	ft_bzero(vec->data, vec->size);
	vec->size = 0;
}

void	vector_image_set_data(t_vector_image *vec, size_t index, t_image data)
{
	if (vec->data != NULL)
		vec->data[index] = data;
}

void	*new_image_data_malloc(size_t init_capacity)
{
	void	*data;

	data = ft_calloc(init_capacity, sizeof(t_image));
	return (data);
}
