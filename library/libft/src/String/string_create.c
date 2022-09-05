/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:40:50 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 22:22:39 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string.h"

static void	set_funtion_ptr(t_string *str)
{
	str->f_append = str_append;
	str->f_clear = str_clear;
	str->f_is_empty = str_is_empty;
	str->f_pop_back = str_pop_back;
	str->f_push_back = str_push_back;
	str->f_reserve = str_reserve;
	str->f_shrink_to_fit = str_shrink_to_fit;
	str->f_replace = str_replace;
	str->f_replace_all = str_replace_all;
	str->f_insert = str_insert;
}

t_string	*new_string(size_t init_capacity)
{
	t_string	*str;

	if (init_capacity <= 0)
		return (NULL);
	str = ft_calloc(1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	str->text = ft_calloc(init_capacity, sizeof(*(str->text)));
	if (str->text == NULL)
		return (NULL);
	str->text_len = 0;
	str->capacity = init_capacity;
	set_funtion_ptr(str);
	return (str);
}

void	delete_string(t_string **address_of_string)
{
	if (*address_of_string != NULL)
		free((*address_of_string)->text);
	free(*address_of_string);
	address_of_string = NULL;
}

int	str_reserve(t_string *str, size_t new_capacity)
{
	char	*new_text;

	if (str->text_len > new_capacity - 1)
		return (NO_ACTION);
	new_text = ft_calloc(new_capacity, sizeof(*new_text));
	if (new_text == NULL)
		return (ERROR);
	ft_memmove(new_text, str->text, str->text_len);
	free(str->text);
	str->text = new_text;
	str->capacity = new_capacity;
	return (SUCCESS);
}
