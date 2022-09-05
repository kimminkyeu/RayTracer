/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 10:49:28 by minkyeki          #+#    #+#             */
/*   Updated: 2022/03/22 23:47:12 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

extern size_t	ft_strlen(const char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*pa_str;
	char	*tmp;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	pa_str = malloc(sizeof(*pa_str) * (total_len + 1));
	if (!pa_str)
		return (NULL);
	tmp = pa_str;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (pa_str);
}
