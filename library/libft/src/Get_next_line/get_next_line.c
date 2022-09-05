/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:57:42 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/04 16:22:16 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "get_next_line.h"

static bool	is_mem_empty(const void *data, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (((const unsigned char *)data)[i] != '\0')
			return (false);
		++i;
	}
	return (true);
}

static char	*my_substr(char const *s, unsigned int start, size_t len)
{
	char	*pa_str;

	pa_str = malloc(sizeof(*pa_str) * (len + 1));
	if (!pa_str)
		return (NULL);
	memcpy_gnl(pa_str, s + start, len);
	pa_str[len] = '\0';
	return (pa_str);
}

static void	delete_array(t_array *array)
{
	if (!array)
		return ;
	if (array->data != NULL)
	{
		free(array->data);
		array->data = NULL;
	}
	free(array);
}

static void	cpy_to_array_until(t_array *stage, char *buffer, char stopper)
{
	size_t	i;

	i = 0;
	while ((stage->last_data != stopper) && (i < BUFFER_SIZE))
	{
		if (buffer[i] != '\0')
		{
			push_back_array(stage, buffer[i]);
			buffer[i] = '\0';
		}
		++i;
	}
}

char	*get_next_line(int fd)
{
	static char	s_buffer[BUFFER_SIZE];
	t_array		*stage;
	ssize_t		rd_size;
	char		*single_line;

	rd_size = 1;
	if (new_array_malloc(&stage, BUFFER_SIZE) == NULL)
		return (NULL);
	while (rd_size > 0 && (stage->last_data != '\n'))
	{
		if (is_mem_empty(s_buffer, BUFFER_SIZE))
			rd_size = read(fd, s_buffer, BUFFER_SIZE);
		if (rd_size <= 0 && is_mem_empty(stage->data, stage->size))
		{
			delete_array(stage);
			stage = NULL;
			return (NULL);
		}
		cpy_to_array_until(stage, s_buffer, '\n');
	}
	single_line = my_substr(stage->data, 0, stage->size);
	delete_array(stage);
	stage = NULL;
	return (single_line);
}
