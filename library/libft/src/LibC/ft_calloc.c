/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:26:04 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/03 10:57:09 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

/* NOTE : code below is an overflow-safe version of ft_calloc */

extern void		ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;

	if (size == 0 || nmemb == 0)
		return (NULL);
	if (nmemb > SIZE_MAX / size)
	{
		errno = EOVERFLOW;
		return (NULL);
	}
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, nmemb * size);
	return (tmp);
}
