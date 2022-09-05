/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nputstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:33:21 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/13 10:11:07 by kyeu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_nputstr_fd(const char *string, int fd, size_t n)
{
	size_t	idx;
	ssize_t	writed_bytes;
	size_t	len;

	len = ft_strlen(string);
	if (n > len)
		n = len;
	idx = 0;
	while (idx < n)
	{
		writed_bytes = write(fd, &string[idx], n);
		if (writed_bytes < 0)
			return ;
		idx += writed_bytes;
	}
}
