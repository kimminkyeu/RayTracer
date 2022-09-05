/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:35:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/05/13 17:22:45 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../include/libft.h"

/* Allocate and return joined strings passed as argument.
 * - Str_num is a total number of strings.
 * - Returns NULL on error.
 * - ex. ft_strjoin_all(3, str1, str2, str3) */

static void	copy(char *pa_str, va_list argp, size_t str_num)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*tmp;

	i = 0;
	j = 0;
	while (i < str_num)
	{
		tmp = va_arg(argp, char *);
		k = 0;
		while (tmp[k] != '\0')
		{
			pa_str[j] = tmp[k];
			++k;
			++j;
		}
		++i;
	}
	pa_str[j] = '\0';
}

char	*ft_strjoin_all(size_t str_num, ...)
{
	va_list	argp;
	size_t	total_len;
	size_t	i;
	char	*pa_str;
	char	*s;

	i = 0;
	pa_str = NULL;
	total_len = 0;
	va_start(argp, str_num);
	while (i < str_num)
	{
		s = va_arg(argp, char *);
		total_len += ft_strlen(s);
		i++;
	}
	va_end(argp);
	va_start(argp, str_num);
	if (total_len != 0)
		pa_str = malloc(sizeof(*pa_str) * (total_len + 1));
	if (!pa_str)
		return (NULL);
	copy(pa_str, argp, str_num);
	va_end(argp);
	return (pa_str);
}
