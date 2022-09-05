/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_modify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:42:10 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/02 14:45:49 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	str_push_back(t_string *str, char c)
{
	if (str->text_len >= str->capacity - 1)
	{
		if (str_reserve(str, str->capacity * 2) != SUCCESS)
			return (NO_ACTION);
	}
	str->text[str->text_len] = c;
	str->text_len++;
	return (SUCCESS);
}

int	str_pop_back(t_string *str)
{
	if (str->text_len > 0)
	{
		str->text[str->text_len - 1] = '\0';
		str->text_len--;
		return (SUCCESS);
	}
	return (NO_ACTION);
}

int	str_append(t_string *str, const char *str2)
{
	size_t	str2_len;

	if (str2 == NULL)
		return (NO_ACTION);
	str2_len = ft_strlen(str2);
	if (str2_len == 0)
		return (NO_ACTION);
	if (str->capacity - 1 < (str->text_len + str2_len))
	{
		if (str_reserve(str, (str->capacity * 2) + str2_len) != SUCCESS)
			return (ERROR);
	}
	ft_memmove(&(str->text[str->text_len]), str2, str2_len);
	str->text_len += str2_len;
	return (SUCCESS);
}

int	str_insert(t_string *str, size_t pos, const char *str_to_insert)
{
	char	*backup;
	size_t	i;

	backup = NULL;
	if (str_to_insert == NULL || pos > str->text_len - 1)
		return (NO_ACTION);
	backup = ft_strdup(&(str->text[pos]));
	i = str->text_len;
	while (i-- > pos)
		str_pop_back(str);
	str_append(str, str_to_insert);
	str_append(str, backup);
	if (backup != NULL)
		free(backup);
	return (SUCCESS);
}
