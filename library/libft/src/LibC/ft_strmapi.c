/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:14:05 by minkyeki          #+#    #+#             */
/*   Updated: 2022/03/22 23:47:55 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

extern size_t	ft_strlen(const char *str);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*pa_result;
	size_t			len;
	unsigned int	i;

	len = ft_strlen(s);
	pa_result = malloc(sizeof(*pa_result) * (len + 1));
	if (!pa_result)
		return (NULL);
	i = 0;
	while ((size_t)i < len)
	{
		pa_result[i] = f(i, s[i]);
		i++;
	}
	pa_result[len] = '\0';
	return (pa_result);
}
