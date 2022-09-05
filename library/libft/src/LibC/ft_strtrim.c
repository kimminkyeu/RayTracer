/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:10:06 by minkyeki          #+#    #+#             */
/*   Updated: 2022/03/22 23:48:54 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

extern size_t	ft_strlen(const char *str);
extern size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
extern char		*ft_strchr(const char *s, int c);
extern char		*ft_strrchr(const char *s, int c);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*pa_str;
	size_t	start_idx;
	size_t	end_idx;

	start_idx = 0;
	end_idx = ft_strlen(s1);
	while (s1[start_idx] && ft_strchr(set, s1[start_idx]))
		++start_idx;
	while (ft_strrchr(set, s1[end_idx]) && start_idx < end_idx)
		--end_idx;
	pa_str = malloc(sizeof(*pa_str) * (end_idx - start_idx + 2));
	if (!pa_str)
		return (NULL);
	ft_strlcpy(pa_str, &s1[start_idx], end_idx - start_idx + 2);
	return (pa_str);
}
