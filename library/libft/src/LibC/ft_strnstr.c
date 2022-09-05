/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:39:26 by minkyeki          #+#    #+#             */
/*   Updated: 2022/03/22 16:02:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

extern size_t	ft_strlen(const char *str);

static bool	is_same(const char *s1, const char *tofind)
{
	while (*s1 && *tofind && (*s1 == *tofind))
	{
		s1++;
		tofind++;
	}
	if (*tofind == '\0')
		return (true);
	return (false);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_size;
	size_t	haystack_size;

	if (*needle == '\0')
		return ((char *)haystack);
	needle_size = ft_strlen(needle);
	haystack_size = ft_strlen(haystack);
	while (*haystack && (len >= needle_size) && (haystack_size >= needle_size))
	{
		if (is_same(haystack, needle))
			return ((char *)haystack);
		++haystack;
		--len;
	}
	return (NULL);
}
