/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:18:58 by minkyeki          #+#    #+#             */
/*   Updated: 2022/03/16 17:55:20 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_uchar;

	s_uchar = (unsigned char *)s;
	while (n > 0)
	{
		if (*s_uchar == (unsigned char)c)
			return ((void *)s_uchar);
		--n;
		++s_uchar;
	}
	return (0);
}
