/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:28:13 by minkyeki          #+#    #+#             */
/*   Updated: 2022/03/22 23:46:34 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

extern size_t	ft_strlen(const char *str);

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*tmp;

	size = ft_strlen(s1);
	tmp = malloc(sizeof(*tmp) * (size + 1));
	if (!tmp)
		return (NULL);
	while (size > 0)
	{
		tmp[size] = s1[size];
		--size;
	}
	tmp[0] = s1[0];
	return (tmp);
}
