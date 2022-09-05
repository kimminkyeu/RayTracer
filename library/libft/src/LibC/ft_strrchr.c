/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:52:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/03/17 01:04:34 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		s++;
		size++;
	}
	if (size == 0 && c == 0)
		return ((char *)s);
	while (size > 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
		size--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
