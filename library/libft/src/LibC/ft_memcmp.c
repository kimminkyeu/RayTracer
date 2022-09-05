/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:32:23 by minkyeki          #+#    #+#             */
/*   Updated: 2022/03/16 17:19:01 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_uchar;
	const unsigned char	*s2_uchar;

	s1_uchar = (const unsigned char *)s1;
	s2_uchar = (const unsigned char *)s2;
	while ((n > 0) && (*s1_uchar == *s2_uchar))
	{
		++s1_uchar;
		++s2_uchar;
		--n;
	}
	if (n == 0)
		return (0);
	else
		return ((int)*s1_uchar - (int)*s2_uchar);
}
