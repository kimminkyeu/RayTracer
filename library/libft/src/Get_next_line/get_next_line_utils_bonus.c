/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:03:00 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/04 16:20:01 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

void	*memcpy_gnl(void *dst, const void *src, size_t n)
{
	unsigned char		*u_dst;
	const unsigned char	*u_src;
	size_t				i;

	u_dst = (unsigned char *)dst;
	u_src = (const unsigned char *)src;
	if (dst == src)
		return (dst);
	i = 0;
	while (i < n)
	{
		u_dst[i] = u_src[i];
		++i;
	}
	return (dst);
}

t_array	*new_array_malloc(t_array **new_array, size_t init_capacity)
{
	*new_array = malloc(sizeof(**new_array));
	if (*new_array)
	{
		(*new_array)->size = 0;
		(*new_array)->capacity = init_capacity;
		new_str_malloc(&((*new_array)->data), (*new_array)->capacity);
		if (!(*new_array)->data)
		{
			free((*new_array)->data);
			free(*new_array);
			*new_array = NULL;
		}
		(*new_array)->last_data = '\0';
	}
	return (*new_array);
}

char	*new_str_malloc(char **new_str, size_t init_size)
{
	size_t	i;

	i = 0;
	*new_str = malloc(sizeof(**new_str) * (init_size));
	if (*new_str)
	{
		while (i < init_size)
		{
			(*new_str)[i] = '\0';
			++i;
		}
	}
	return (*new_str);
}

void	push_back_array(t_array *const array, int c)
{
	unsigned char	*data_tmp;

	if (array->size >= array->capacity)
		reserve_array(array, (array->capacity) * 2);
	data_tmp = (unsigned char *)array->data;
	data_tmp[array->size] = (unsigned char)c;
	array->last_data = (unsigned char)c;
	(array->size)++;
}

void	reserve_array(t_array *const array, size_t new_capacity)
{
	char	*tmp;

	if (new_capacity <= (array->capacity))
		return ;
	new_str_malloc(&tmp, new_capacity);
	if (tmp)
	{
		memcpy_gnl(tmp, array->data, array->size);
		free(array->data);
		array->data = tmp;
		array->capacity = new_capacity;
	}
}
